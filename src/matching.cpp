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
#include "err.h"
#include <signal.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define bozorthPath "/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3"
#define TRUE 1
#define FALSE 0

//MATCHING COM BOZORTH
void matching()
{
	char *my_env[] = {NULL};
	char *newargv_bozorth[] = {"bozorth3", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};

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
	}
}
