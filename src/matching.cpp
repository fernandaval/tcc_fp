/*
 * matching.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#include "matching.hpp"

#define bozorthPath "/home/priscila/Rel_4.2.0/bozorth3/bin/bozorth3"


//MATCHING COM BOZORTH
bool matching()
{
	char *my_env[] = {NULL};
	//char *newargv_bozorth[] = {"bozorth3", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};
	char *newargv_bozorth[] = {"bozorth3", "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt", "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt", NULL};

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
		return 1;
	}
	return FALSE;
}
