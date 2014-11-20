/*
 * minutiaeExtraction.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */


#include "minutiaeExtraction.hpp"
#include "constants.hpp"

#define TRUE 1
#define FALSE 0

using namespace std;

void minutiaePlot(int row, int col, int N, Mat minutiaeImage, int idSystem, VInterfaceDTO vinterface) {
	 vector <minutia*> minutiae;
	 ifstream myReadFile;
	 char output[100];
	 int count = 0;
	 int aux = 0;
	 float totalQuality = 0;

	 myReadFile.open(xytPath);

	 minutiae.resize(col*row);
	 for (int i = 0; i < col*row; i++) {
		 minutiae[i] = new minutia();
	 }

	 if (myReadFile.is_open()) {
		 while (!myReadFile.eof()) {

			 count ++;
			 myReadFile >> output;

			 if (count == 1) {
				 minutiae[aux]->setX(atoi(output));
			 }
			 else if (count == 2) {
				 minutiae[aux]->setY(atoi(output));
			 }
			 else if (count == 3) {
				 minutiae[aux]->setTheta(atoi(output));
			 }
			 else if (count == 4) {
				 minutiae[aux]->setQuality(atoi(output));
				 totalQuality = totalQuality + atof(output);
				 count = 0;
				 aux ++;
			 }
		 }
	}
	myReadFile.close();

	if (idSystem == 1) {
		vinterface.setMinutiaeQuantity1(aux - 1);
		vinterface.setMinutiaeQuality1(totalQuality/(aux - 1));
	}
	else if (idSystem == 2) {
		vinterface.setMinutiaeQuantity2(aux - 1);
		vinterface.setMinutiaeQuality2(totalQuality/(aux - 1));
	}
	else {
		vinterface.setMinutiaeQuantity3(aux - 1);
		vinterface.setMinutiaeQuality3(totalQuality/(aux - 1));
	}

	for (int i = 0; i < aux; i++) {
		//FOI NECESSÁRIO INVERTER X E Y PARA QUE AS MINÚCIAS FOSSEM EXIBIDAS ADEQUADAMENTE
		//ALÉM DISSO, USA  AFUNÇÃO "CIRCLE" PARA QUE SEJAM BEM VISÍVEIS AS MINÚCIAS EXTRAÍDAS
		circle(minutiaeImage, Point(minutiae[i]->getX(), row - minutiae[i]->getY()), 3, Scalar( 0, 0, 255 ), -1, 8, 0);
	}
	//imshow("Minúcias extraídas", minutiaeImage);
	imwrite(outputPath, minutiaeImage);

	return;
}

void printType(Mat &mat) {
         if(mat.depth() == CV_8U)  printf("unsigned char(%d)", mat.channels());
    else if(mat.depth() == CV_8S)  printf("signed char(%d)", mat.channels());
    else if(mat.depth() == CV_16U) printf("unsigned short(%d)", mat.channels());
    else if(mat.depth() == CV_16S) printf("signed short(%d)", mat.channels());
    else if(mat.depth() == CV_32S) printf("signed int(%d)", mat.channels());
    else if(mat.depth() == CV_32F) printf("float(%d)", mat.channels());
    else if(mat.depth() == CV_64F) printf("double(%d)", mat.channels());
    else                           printf("unknown(%d)", mat.channels());
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   }
   //printf("\n");
   return 0;
}

//salva minucias recem-extraidas no BD
void saveMinutiae2(int idUsuario)
{
	 vector <minutia*> minutiae;
	 ifstream myReadFile;
	 char output[100];
	 int count = 0;
	 int aux = 0;

	 minutiae.resize(aux+1);
	 minutiae[aux] = new minutia();

	 myReadFile.open(xytPath);

	 if (myReadFile.is_open()) {

		 while (!myReadFile.eof()) {

			 count ++;
			 myReadFile >> output;

			 if (count == 1) {
				 minutiae[aux]->setX(atoi(output));
			 }
			 else if (count == 2) {
				 minutiae[aux]->setY(atoi(output));
			 }
			 else if (count == 3) {
				 minutiae[aux]->setTheta(atoi(output));
			 }
			 else if (count == 4) {
				 minutiae[aux]->setQuality(atoi(output));
				 count = 0;
				 aux ++;
				 minutiae.resize(aux+1);
				 minutiae[aux] = new minutia();
			 }
		 }
	}

	myReadFile.close();

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sqlstr;

	/* Open database */
	rc = sqlite3_open(bdPath, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    exit(0);
	}

	sqlstr = "INSERT INTO template (idUser,registerDate,quality,type) VALUES (";
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idUsuario) )->str());
	sqlstr.append(",'");
	sqlstr.append(__DATE__);
	sqlstr.append("','','');");
	const char * sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	int idTemplate = (int) sqlite3_last_insert_rowid(db);

	int totalQualityTemplate = 0;

	for (int i = 0; i < aux; i++) {
		sqlstr = "INSERT INTO minutia (idTemplate,x,y,theta,quality) VALUES (";
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idTemplate) )->str());
		sqlstr.append(",");
		int x = minutiae[i]->getX();
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << x) )->str());
		sqlstr.append(",");
		int y = minutiae[i]->getY();
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << y) )->str());
		sqlstr.append(",");
		int theta = minutiae[i]->getTheta();
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << theta) )->str());
		sqlstr.append(",");
		int quality = minutiae[i]->getQuality();
		totalQualityTemplate = totalQualityTemplate + quality;
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << quality) )->str());
		sqlstr.append(");");

		sql = sqlstr.c_str();

		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	    if( rc != SQLITE_OK ){
		  fprintf(stderr, "SQL error: %s\n", zErrMsg);
		  sqlite3_free(zErrMsg);
	    }
	}

	int averageQualityTemplate = totalQualityTemplate/aux;
	sqlstr = "UPDATE template SET quality = ";
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << averageQualityTemplate) )->str());
	sqlstr.append(" WHERE id=");
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idTemplate) )->str());
	sqlstr.append(";");

	sql = sqlstr.c_str();

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

}

//salva minucias recem-extraidas no BD
void saveMinutiae(int idSystem, int idUser)
{
	 ifstream myReadFile;
	 char output[100];
	 int count = 0;
	 int aux = 0;
	 string minutiae;

	 myReadFile.open(xytPath);

	 int totalQualityTemplate = 0;

	 ifstream file(xytPath);
	 string str;
	 while (getline(file, str))
	 {
	   aux++;

	   //extraindo a qualidade da minucia e salvando em strquality
	   istringstream iss(str);
	   string strquality;
	   while (getline( iss, strquality, ' ' ) ) {
	   }

	   //convertendo strquality para int
	   istringstream temp(strquality);
	   int quality;
	   temp >> quality;

	   //somando a qualidade de todas as minucias do template
	   totalQualityTemplate += quality;

	   minutiae += str;
	   minutiae.push_back('\n');
	 }

	float averageQualityTemplate = totalQualityTemplate/aux;
	ostringstream convert;
	convert << averageQualityTemplate;
	string strquality = convert.str();

	myReadFile.close();

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sqlstr;

	/* Open database */
	rc = sqlite3_open(bdPath, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	    exit(0);
	}

	sqlstr = "INSERT INTO template (idUser,idSystem,registerDate,quality,type,minutiae) VALUES (";
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idUser) )->str());
	sqlstr.append(",");
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << idSystem) )->str());
	sqlstr.append(",'");
	sqlstr.append(__DATE__);
	sqlstr.append("',");
	sqlstr.append(strquality);
	sqlstr.append(",'','");
	sqlstr.append(minutiae);
	sqlstr.append("');");
	const char * sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

}

void minutiaeExtract(Mat image, int idSystem, int option, int idUsuario)
{
	//EXTRAÇÃO DE MINÚCIAS COM MINDTCT
	char *my_env[] = {NULL};

	string input = imagePathME;
	imwrite(input.append("/image.jpg"), image);

	string output = imagePathME;
	output.append("/minutiae");

	char * parameter1 = new char[input.length() + 1];
	strcpy(parameter1,input.c_str());

	char * parameter2 = new char[output.length() + 1];
	strcpy(parameter2,output.c_str());

	char *newargv_mindtct[] = {"mindtct", parameter1, parameter2, NULL};

	pid_t pid = fork();

	if(pid == -1){
		fprintf(stderr, "Erro ao executar o fork\n");
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}

	/*
	*	FILHO
	*/
	if(!pid){
		//fprintf(stdout, "Mindtct - FILHO EXECUTANDO!\n");
		if(execve(mindtctPath, newargv_mindtct, my_env) == -1){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		}
	}
	/*
	*	PAI
	*/
	else{
		//fprintf(stdout, "Mindtct - PAI EXECUTANDO\n");
		int status;
		if (waitpid(pid,&status,0) > 0) {
			fprintf(stdout, "minucias extraidas\n");

			if (option == 1) saveMinutiae(idSystem, idUsuario);
		}
	}
}

