/*
 * metrics.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: priscila
 */

#include "metrics.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <sys/wait.h>
#include "err.h"
#include <signal.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/time.h>
#include <sqlite3.h>

#include "constants.hpp"
//#define bdPath "/home/priscila/tcc_fp/fingerprint.db"

//parametros de teste
#define scoreChange 2
#define minimumTolerant 14
#define minimumRigorous 20
#define limitFAR 0.05
#define limitFRR 0.05
#define quantityTransitory 3

using namespace std;

int score;
int trueAcceptance;
int trueRejection;
int falseAcceptance;
int falseRejection;
double avgExecutionTime;
int numberOfExecutions;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
		const char * temp = argv[i];
		string column = azColName[i];
		if (column == "trueAcceptance") trueAcceptance = atoi(temp);
		if (column == "trueRejection") trueRejection = atoi(temp);
		if (column == "falseAcceptance") falseAcceptance = atoi(temp);
		if (column == "falseRejection") falseRejection = atoi(temp);
		if (column == "minimumScore") score = atoi(temp);
		if (column == "numberOfExecutions") numberOfExecutions = atoi(temp);
		//if (column == "avgExecutionTime") avgExecutionTime = atof(temp);
		if (column == "avgExecutionTime")
		{
			string strtemp(temp);
			string strtemp2(strtemp.substr(0,strtemp.find(".")));
			string strtemp3(strtemp.substr(strtemp.find(".")+1,strtemp.length()));
			string strtemp4(strtemp2 + "," + strtemp3);
			avgExecutionTime = stof(strtemp4);
			//cout << "callback - avgExecutionTime(stof): " << to_string(stof(strtemp4)) << endl;
		}
   }
   return 0;
}

static int callbackNone(void *NotUsed, int argc, char **argv, char **azColName){
   return 0;
}

void refreshAllMetrics(VInterfaceDTO& vinterface) {
	float fa;
	float ta;
	float tr;
	float fr;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sqlstr;
	const char * sql;

	/* Open database */
	rc = sqlite3_open(bdPath, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	//sistema 1
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	vinterface.setFar1(fa/(fa+ta));
	vinterface.setFrr1(fr/(tr+fr));
	vinterface.setTar1(ta/(fa+ta));
	vinterface.setTrr1(tr/(tr+fr));
	vinterface.setMinimumScore1(score);
	cout << "get Minimum Score1: " << vinterface.getMinimumScore1() << endl;
	vinterface.setAvgTime1(avgExecutionTime);
	cout << "avg time1: " << avgExecutionTime << endl;

	//sistema 2
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	vinterface.setFar2(fa/(fa+ta));
	vinterface.setFrr2(fr/(tr+fr));
	vinterface.setTar2(ta/(fa+ta));
	vinterface.setTrr2(tr/(tr+fr));
	vinterface.setMinimumScore2(score);
	vinterface.setAvgTime2(avgExecutionTime);
	cout << "avg time2: " << avgExecutionTime << endl;

	//sistema 3 modo padrão
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	vinterface.setFar31(fa/(fa+ta));
	vinterface.setFrr31(fr/(tr+fr));
	vinterface.setTar31(ta/(fa+ta));
	vinterface.setTrr31(tr/(tr+fr));
	vinterface.setMinimumScore31(score);
	vinterface.setAvgTime31(avgExecutionTime);
	cout << "avg time31: " << avgExecutionTime << endl;

	//sistema 3 modo tolerante
	sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	vinterface.setFar32(fa/(fa+ta));
	vinterface.setFrr32(fr/(tr+fr));
	vinterface.setTar32(ta/(fa+ta));
	vinterface.setTrr32(tr/(tr+fr));
	vinterface.setMinimumScore32(score);
	vinterface.setAvgTime32(avgExecutionTime);
	cout << "avg time32: " << avgExecutionTime << endl;

	//sistema 3 modo rigoroso
	sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	vinterface.setFar33(fa/(fa+ta));
	vinterface.setFrr33(fr/(tr+fr));
	vinterface.setTar33(ta/(fa+ta));
	vinterface.setTrr33(tr/(tr+fr));
	vinterface.setMinimumScore33(score);
	vinterface.setAvgTime33(avgExecutionTime);
	cout << "avg time33: " << avgExecutionTime << endl;

	return;
}

void minimumScoresUpdate() {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sqlstr;
	const char * sql;

	/* Open database */
	rc = sqlite3_open(bdPath, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	//Sistema Tolerante
	sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	float fa = (float)falseAcceptance;
	float ta = (float)trueAcceptance;
	float tr = (float)trueRejection;
	float fr = (float)falseRejection;
	float falseRejectionRate = fr/(tr+fr);

	if (fa+ta+tr+fr > quantityTransitory) {
		if (falseRejectionRate > limitFRR) {
			sqlstr = "UPDATE operationMode SET minimumScore = ";
			int temp = score - scoreChange;
			if (temp >= minimumTolerant) { //minimumScore não deve ultrapassar esse limite mínimo
				sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
				sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
				const char * sql2 = sqlstr.c_str();
				rc = sqlite3_exec(db, sql2, callbackNone, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
				  fprintf(stderr, "SQL error: %s\n", zErrMsg);
				  sqlite3_free(zErrMsg);
				}
			}
		}
		else {
			sqlstr = "UPDATE operationMode SET minimumScore = ";
			int temp = score + scoreChange;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callbackNone, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}

	//Sistema Rigoroso
	sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	fa = (float)falseAcceptance;
	ta = (float)trueAcceptance;
	tr = (float)trueRejection;
	fr = (float)falseRejection;
	float falseAcceptanceRate = fa/(fa+ta);

	if (fa+ta+tr+fr > quantityTransitory) {
		if (falseAcceptanceRate > limitFAR) {
			sqlstr = "UPDATE operationMode SET minimumScore = ";
			int temp = score + scoreChange;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callbackNone, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else {
			sqlstr = "UPDATE operationMode SET minimumScore = ";
			int temp = score - scoreChange;
			if (temp >= minimumRigorous) { //sistema rigoroso nunca deve ter nota de corte menor do que esse limite
				sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
				sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
				const char * sql2 = sqlstr.c_str();
				rc = sqlite3_exec(db, sql2, callbackNone, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
				  fprintf(stderr, "SQL error: %s\n", zErrMsg);
				  sqlite3_free(zErrMsg);
				}
			}
		}
	}
}

void metricsUpdate(bool feedback, bool accepted1, bool accepted2, bool accepted31, bool accepted32, bool accepted33, float executionTime1, float executionTime2, float executionTime31, float executionTime32, float executionTime33) {
	cout << "feedback recebido: " << feedback << endl;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sqlstr;
	float tempTime;
	int tempNumber;

	/* Open database */
	rc = sqlite3_open(bdPath, &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}

	//Atualizando métricas do sistema 1
	if (accepted1)
	{
		if (feedback)
		{
			//incrementar trueAcceptance do 1

			cout << "trueAcceptance do 1" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueAcceptance = ";
			int temp = trueAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 1;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

		}
		else
		{
			//incrementar falseAcceptance do 1

			cout << "falseAcceptance do 1" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseAcceptance = ";
			int temp = falseAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 1;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

		}
	}
	else
	{
		if (feedback)
		{
			//incrementar falseRejection do 1

			cout << "falseRejection do 1" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseRejection = ";
			int temp = falseRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 1;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar trueRejection do 1

			cout << "trueRejection do 1" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueRejection = ";
			int temp = trueRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 1;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	//atualização do tempo médio de execução e número de execuções
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 1;";
	const char * sql3 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql3, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	sqlstr = "UPDATE operationMode SET avgExecutionTime = ";
	cout << "avgExecutionTime: " << avgExecutionTime << endl;
	cout << "avgExecutionTime*numberOfExecutions: " << avgExecutionTime*numberOfExecutions << endl;
	tempTime = ((avgExecutionTime*(float)numberOfExecutions)+(float)executionTime1)/((float)numberOfExecutions+1);
	cout << "tempTime: " << tempTime << endl;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempTime) )->str());
	sqlstr.append(", numberOfExecutions = ");
	tempNumber = numberOfExecutions + 1;
	cout << "tempNumber: " << tempNumber << endl;
	cout<< "numberOfExeuctions: " << numberOfExecutions <<endl;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempNumber) )->str());
	sqlstr.append(" WHERE id = 1 AND idSystem = 1;");
	const char * sql4 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql4, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}


	//Atualizando métricas do sistema 2
	if (accepted2)
	{
		if (feedback)
		{
			//incrementar trueAcceptance do 2

			cout << "trueAcceptance do 2" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueAcceptance = ";
			int temp = trueAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 2;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar falseAcceptance do 2

			cout << "falseAcceptance do 2" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseAcceptance = ";
			int temp = falseAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 2;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	else
	{
		if (feedback)
		{
			//incrementar falseRejection do 2

			cout << "falseRejection do 2" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseRejection = ";
			int temp = falseRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 2;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar trueRejection do 2

			cout << "trueRejection do 2" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueRejection = ";
			int temp = trueRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 2;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	//atualização do tempo médio de execução e número de execuções
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 2;";
	const char * sql5 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql5, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	sqlstr = "UPDATE operationMode SET avgExecutionTime = ";
	tempTime = ((avgExecutionTime*numberOfExecutions)+executionTime2)/(numberOfExecutions+1);
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempTime) )->str());
	sqlstr.append(", numberOfExecutions = ");
	tempNumber = numberOfExecutions + 1;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempNumber) )->str());
	sqlstr.append(" WHERE id = 1 AND idSystem = 2;");
	const char * sql6 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql6, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	//Atualizando métricas do sistema 3 modo 1
	if (accepted31)
	{
		if (feedback)
		{
			//incrementar trueAcceptance do 31

			cout << "trueAcceptance do 31" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueAcceptance = ";
			int temp = trueAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar falseAcceptance do 31

			cout << "falseAcceptance do 31" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseAcceptance = ";
			int temp = falseAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	else
	{
		if (feedback)
		{
			//incrementar falseRejection do 31

			cout << "falseRejection do 31" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseRejection = ";
			int temp = falseRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar trueRejection do 31

			cout << "trueRejection do 31" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueRejection = ";
			int temp = trueRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 1 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	//atualização do tempo médio de execução e número de execuções
	sqlstr = "SELECT * FROM operationMode WHERE id = 1 AND idSystem = 3;";
	const char * sql7 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql7, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	sqlstr = "UPDATE operationMode SET avgExecutionTime = ";
	tempTime = ((avgExecutionTime*numberOfExecutions)+executionTime31)/(numberOfExecutions+1);
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempTime) )->str());
	sqlstr.append(", numberOfExecutions = ");
	tempNumber = numberOfExecutions + 1;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempNumber) )->str());
	sqlstr.append(" WHERE id = 1 AND idSystem = 3;");
	const char * sql8 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql8, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	//Atualizando métricas do sistema 3 modo 2
	if (accepted32)
	{
		if (feedback)
		{
			//incrementar trueAcceptance do 32

			cout << "trueAcceptance do 32" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueAcceptance = ";
			int temp = trueAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar falseAcceptance do 32

			cout << "falseAcceptance do 32" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseAcceptance = ";
			int temp = falseAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	else
	{
		if (feedback)
		{
			//incrementar falseRejection do 32

			cout << "falseRejection do 32" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseRejection = ";
			int temp = falseRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar trueRejection do 32

			cout << "trueRejection do 32" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueRejection = ";
			int temp = trueRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	//atualização do tempo médio de execução e número de execuções
	sqlstr = "SELECT * FROM operationMode WHERE id = 2 AND idSystem = 3;";
	const char * sql9 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql9, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	sqlstr = "UPDATE operationMode SET avgExecutionTime = ";
	tempTime = ((avgExecutionTime*numberOfExecutions)+executionTime32)/(numberOfExecutions+1);
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempTime) )->str());
	sqlstr.append(", numberOfExecutions = ");
	tempNumber = numberOfExecutions + 1;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempNumber) )->str());
	sqlstr.append(" WHERE id = 2 AND idSystem = 3;");
	const char * sql10 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql10, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	//Atualizando métricas do sistema 3 modo 3
	if (accepted33)
	{
		if (feedback)
		{
			//incrementar trueAcceptance do 33

			cout << "trueAcceptance do 33" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueAcceptance = ";
			int temp = trueAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar falseAcceptance do 33

			cout << "falseAcceptance do 33" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseAcceptance = ";
			int temp = falseAcceptance + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	else
	{
		if (feedback)
		{
			//incrementar falseRejection do 33

			cout << "falseRejection do 33" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET falseRejection = ";
			int temp = falseRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
		else
		{
			//incrementar trueRejection do 33

			cout << "trueRejection do 33" << endl;

			sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
			const char * sql = sqlstr.c_str();
			rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}

			sqlstr = "UPDATE operationMode SET trueRejection = ";
			int temp = trueRejection + 1;
			sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << temp) )->str());
			sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
			const char * sql2 = sqlstr.c_str();
			rc = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
			if( rc != SQLITE_OK ){
			  fprintf(stderr, "SQL error: %s\n", zErrMsg);
			  sqlite3_free(zErrMsg);
			}
		}
	}
	//atualização do tempo médio de execução e número de execuções
	sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
	const char * sql11 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql11, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}
	sqlstr = "UPDATE operationMode SET avgExecutionTime = ";
	tempTime = ((avgExecutionTime*numberOfExecutions)+executionTime33)/(numberOfExecutions+1);
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempTime) )->str());
	sqlstr.append(", numberOfExecutions = ");
	tempNumber = numberOfExecutions + 1;
	sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << tempNumber) )->str());
	sqlstr.append(" WHERE id = 3 AND idSystem = 3;");
	const char * sql12 = sqlstr.c_str();
	rc = sqlite3_exec(db, sql12, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
}




