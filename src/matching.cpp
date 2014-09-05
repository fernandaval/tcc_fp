/*
 * matching.cpp
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
#include <iostream>
#include <stdio.h>
#include "err.h"
#include <signal.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define bozorthPath "/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3"
#define TRUE 1
#define FALSE 0
#define MINIMUMSCORE 60

using namespace std;

//MATCHING COM BOZORTH
bool matching()
{
	char *my_env[] = {NULL};
	char *newargv_bozorth[] = {"bozorth3", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};

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
		if(execve("/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3", newargv_bozorth, my_env) == -1){
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
