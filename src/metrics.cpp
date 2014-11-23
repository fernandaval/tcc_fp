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

#define bdPath "/home/priscila/tcc_fp/fingerprint.db"

//parametros de teste
#define scoreChange 2
#define minimumTolerant 12
#define minimumRigorous 20

using namespace std;

int score;
int trueAcceptance;
int trueRejection;
int falseAcceptance;
int falseRejection;

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

	//cout << "falseRejectionRate do Tolerante: " << falseRejectionRate << endl;

	if (falseRejectionRate > 0.05) {
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

	//Sistema Rigoroso
	sqlstr = "SELECT * FROM operationMode WHERE id = 3 AND idSystem = 3;";
	sql = sqlstr.c_str();
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", zErrMsg);
	  sqlite3_free(zErrMsg);
	}

	float falseAcceptanceRate = fa/(fa+ta);
	if (falseAcceptanceRate > 0.05) {
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

void metricsUpdate(bool feedback, bool accepted1, bool accepted2, bool accepted31, bool accepted32, bool accepted33) {
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

	sqlite3_close(db);
}




