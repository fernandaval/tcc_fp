/*
 * matching.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#include "matching.hpp"

#define bozorthPath "/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3"
#define bdpath "/home/priscila/tcc_fp/fingerprint.db"
#define xytpath "/home/priscila/tcc_fp/minutiae/minutiae_ref.xyt"
#define TRUE 1
#define FALSE 0
#define MINIMUMSCORE 60

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   ofstream xytfile;
   xytfile.open(xytpath);

   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      //xytfile << argv[i]; TODO
   }

   xytfile.close();
   printf("\n");
   return 0;
}

//converte templates de minucias do BD para arquivos .xyt que serão passados para o Bozorth
void generateXYT()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   rc = sqlite3_open(bdpath, &db);

   if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  exit(0);
   }

   sql = "SELECT * FROM teste";

   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   } else {
       //fprintf(stdout, "Operation done successfully\n");
   }

   sqlite3_close(db);

}

//MATCHING COM BOZORTH
bool matching()
{
	generateXYT();

	char *my_env[] = {NULL};
	//char *newargv_bozorth[] = {"bozorth3", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};
	char *newargv_bozorth[] = {"bozorth3", "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};

	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr, "Não foi possível criar o pipe...");
	}

	pid_t pid = fork();

	if(pid == -1){
		fprintf(stderr, "Erro ao executar o fork");
		exit(1);
	}

	/*
	*	FILHO
	*/
	if(!pid){
		//fprintf(stdout, "Bozorth - FILHO EXECUTANDO!\n");
		dup2(fd[1], 1);
		close(fd[0]);
		fprintf(stdout, "Matching score: \n");
		//if(execve("/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3", newargv_bozorth, my_env) == -1){
		if(execve("/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/bozorth3/bin/bozorth3", newargv_bozorth, my_env) == -1){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		}
	}
	/*
	*	PAI
	*/
	else{
		//fprintf(stdout, "Bozorth - PAI EXECUTANDO\n");
		int status;
		if (waitpid(pid,&status,0) > 0) {
			char line[255];
			dup2(fd[0], 0);
			close(fd[1]);
			read(fd[0], line, 255);
			close(fd[0]);
			char * temp;
			temp = strtok(line," ");
			string digito1, digito2, digito3;
			digito1 = temp[17];
			digito2 = temp[18];
			digito3 = temp[19];
			string resultado = digito1 + digito2 + digito3;
			int score = atoi(resultado.c_str());
			if (score >= MINIMUMSCORE) return true;
			else return false;
		}
	}
	return false;
}
