/*
 * minutiaeExtraction.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

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
#include <fcntl.h>

#include "preProcessing.hpp"

#define mindtctPath "/home/priscila/Rel_4.2.0/mindtct/bin/mindtct"
#define TRUE 1
#define FALSE 0

void minutiaePlot(vector < vector <window*> > *windows, int row, int col, int N) {
	//TO DO
}

void minutiaeExtract()
{
	//EXTRAÇÃO DE MINÚCIAS COM MINDTCT
	char *my_env[] = {NULL};
	char *newargv_mindtct[] = {"mindtct", "/home/priscila/BDs_imagens_de_digitais/2000/DB2/101_1.jpg", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1", NULL};

	pid_t pid = fork();

	if(pid == -1){
		fprintf(stderr, "Erro ao executar o fork");
		exit(1);
	}

	/*
	*	FILHO
	*/
	if(!pid){
		//fprintf(stdout, "Mindtct - FILHO EXECUTANDO!\n");
		if(execve("/home/priscila/Rel_4.2.0/mindtct/bin/mindtct", newargv_mindtct, my_env) == -1){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		}
	}
	/*
	*	PAI
	*/
	else{
		//fprintf(stdout, "Mindtct - PAI EXECUTANDO\n");
	}
	fprintf(stdout, "minucias extraidas\n");
}

