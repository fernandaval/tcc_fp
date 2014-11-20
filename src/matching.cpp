/*
 * matching.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#include "matching.hpp"

//PRISCILA
#define bozorthPath "/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3"
#define bdPath "/home/priscila/tcc_fp/fingerprint.db"
#define xytPath "/home/priscila/tcc_fp/minutiae/minutiae_ref.xyt"
#define inputPath "/home/priscila/tcc_fp/minutiae/minutiae.xyt"
//PRISCILA

//FERNANDA
/*
#define bozorthPath "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/bozorth3/bin/bozorth3"
#define bdPath "/home/fernanda/workspace/c/tcc_fp/fingerprint.db"
#define xytPath "/home/fernanda/workspace/c/tcc_fp/minutiae/minutiae_ref.xyt"
#define inputPath "/home/fernanda/workspace/c/tcc_fp/minutiae/minutiae.xyt"
*/
//FERNANDA

//RAFAEL
//#define bozorthPath "/home/rafael/Desktop/nist/Rel_4.2.0/bozorth3/bin/bozorth3"
//#define bdPath "/home/rafael/Desktop/rafael/tcc_fe/core/tcc_fp/fingerprint.db"
//#define xytPath "/home/rafael/Desktop/rafael/tcc_fe/core/tcc_fp/minutiae/minutiae_ref.xyt"
//#define inputPath "/home/rafael/Desktop/rafael/tcc_fe/core/tcc_fp/minutiae/minutiae.xyt"
//RAFAEL

#define TRUE 1
#define FALSE 0
#define MINIMUMSCORE 60

using namespace std;

//vector <char> result_columns;
vector <int> results_id;
vector <int> results_x;
vector <int> results_y;
vector <int> results_theta;
vector <int> results_quality;
string minutiae;
int minimumScore;

static int callback(void *data, int argc, char **argv, char **azColName){
	int i;

	for(i=0; i<argc; i++){
		const char * temp = argv[i];
		string column = azColName[i];
		if (column == "minutiae") minutiae = temp;
	}
	return 0;
}

static int callbackMode(void *data, int argc, char **argv, char **azColName){
	int i;

	for(i=0; i<argc; i++){
		const char * temp = argv[i];
		string column = azColName[i];
		if (column == "minimumScore") minimumScore = atoi(temp);
	}
	return 0;
}

static int callbackTemplate(void *data, int argc, char **argv, char **azColName){
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);

    for(i=0; i<argc; i++){
    	//result_columns.push_back(*azColName[i]);
    	const char * temp = argv[i];
    	string column = azColName[i];
    	if (column == "id") results_id.push_back(atoi(temp));
    }

   return 0;
}

static int callbackMinutia(void *data, int argc, char **argv, char **azColName){
    int i;
    //fprintf(stderr, "%s: ", (const char*)data);

    for(i=0; i<argc; i++){
    	//result_columns.push_back(*azColName[i]);
    	const char * temp = argv[i];
    	string column = azColName[i];
    	if (column == "x") results_x.push_back(atoi(temp));
    	if (column == "y") results_y.push_back(atoi(temp));
    	if (column == "theta") results_theta.push_back(atoi(temp));
    	if (column == "quality") results_quality.push_back(atoi(temp));
    }

   return 0;
}

int bozorth()
{
	char *my_env[] = {NULL};
	char *newargv_bozorth[] = {"bozorth3", inputPath, xytPath, NULL};

	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr, "Não foi possível criar o pipe...");
	}

	pid_t pid = fork();

	if(pid == -1){
		fprintf(stderr, "Erro ao executar o fork");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}

	/*
	*	FILHO
	*/
	if(!pid){

		dup2(fd[1], 1);
		close(fd[0]);
		if(execve(bozorthPath, newargv_bozorth, my_env) == -1){
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

		/*if (wait(NULL) == -1)
		{
			fprintf(stderr, "Erro no wait");
		}
		else
		{*/

		if (waitpid(pid,&status,0) > 0) {
			char line[255];
			dup2(fd[0], 0);
			close(fd[1]);
			read(fd[0], line, 255);
			close(fd[0]);
			char * temp;
			temp = strtok(line,"\n");
			string resultado = temp;
			//cout << "resultado contem: " << resultado << endl;
			int score = atoi(resultado.c_str());

			return score;
		}
	}
	return -1;	// retornará -1 se der algum erro
}

//converte os templates do BD para arquivo .xyt e chama o Bozorth
bool matching2()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* data = "Callback function called";

   rc = sqlite3_open(bdPath, &db);

   if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  exit(0);
   }

   const char * sql = "SELECT id FROM template;";

   rc = sqlite3_exec(db, sql, callbackTemplate, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
   	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }

   string sqlstr;
   bool approval = false;
   for(int k=0; k<results_id.size(); k++){
	   sqlstr = "SELECT * FROM minutia WHERE idTemplate = ";
	   sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << results_id[k]) )->str());
	   sqlstr.append(";");

	   sql = sqlstr.c_str();

	   rc = sqlite3_exec(db, sql, callbackMinutia, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
		   fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   sqlite3_free(zErrMsg);
	   }

	   ofstream myfile;
	   myfile.open(xytPath);
	   if (myfile.is_open()) {
		   for(int a=0; a<results_x.size(); a++){
			   myfile << results_x[a] << " " << results_y[a] << " " << results_theta[a] << " " << results_quality[a] << "\n";
		   }
	   }
	   myfile.close();
	   if (bozorth()==true){
		   //cout << "Matching com template " << results_id[k] << "!\n";
		   approval = true;
	   }
	   else {
		   //cout << "Sem similaridade com template " << results_id[k] << "\n";
	   }
   }

   return approval;

   sqlite3_close(db);

}

//converte os templates do BD para arquivo .xyt e chama o Bozorth
bool matching(int idSystem, int idMode)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* data = "Callback function called";

   results_id.clear();

   rc = sqlite3_open(bdPath, &db);

   if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  exit(0);
   }

   string sqlstring;
   sqlstring = "SELECT id FROM template WHERE idSystem = ";
   sqlstring.append(static_cast<ostringstream*>( &(ostringstream() << idSystem) )->str());
   sqlstring.append(";");
   const char * sql = sqlstring.c_str();

   rc = sqlite3_exec(db, sql, callbackTemplate, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
   	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   }

   string sqlstr;
   bool approval = false;
   int k = 0;
   while (k<results_id.size() and approval==false) {
	   sqlstr = "SELECT minutiae FROM template WHERE id = ";
	   sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << results_id[k]) )->str());
	   sqlstr.append(";");

	   sql = sqlstr.c_str();

	   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
		   fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   sqlite3_free(zErrMsg);
	   }

	   ofstream myfile;
	   myfile.open(xytPath);

	   if (myfile.is_open()) {
		   myfile << minutiae;
	   }
	   myfile.close();

	   sqlstr = "SELECT minimumScore FROM operationMode WHERE id = ";
	   sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idMode) )->str());
	   sqlstr.append(";");

	   sql = sqlstr.c_str();

	   rc = sqlite3_exec(db, sql, callbackMode, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
		   fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   sqlite3_free(zErrMsg);
	   }

	   //cout << "modo: " << idMode << " - note de corte: " << minimumScore << endl;
	   if (bozorth()>=minimumScore){
		   //cout << "Matching com template " << results_id[k] << "!\n";
		   approval = true;
	   }
	   else {
		   //cout << "Sem similaridade com template " << results_id[k] << "\n";
	   }
	   k++;
   }

   sqlite3_close(db);

   return approval;

}
