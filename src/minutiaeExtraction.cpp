/*
 * minutiaeExtraction.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */



#include "minutiaeExtraction.hpp"


#define mindtctPath "/home/priscila/Rel_4.2.0/mindtct/bin/mindtct"

void minutiaePlot(vector < vector <window*> > *windows, int row, int col, int N, Mat minutiaeImage) {
	//"/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt"
	 vector <minutia*> minutiae;
	 ifstream myReadFile;
	 char output[100];
	 int count = 0;
	 int aux = 0;

	 myReadFile.open("/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1.xyt");

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
				 count = 0;
				 aux ++;
			 }
		 }
	}
	myReadFile.close();

	/*Mat minutiaesImage;
	minutiaesImage.create(row, col, CV_8UC3);//(*windows)[0][0]->getImageWindow().type());
	groupImageWindows(&minutiaesImage, *windows, row, col, N);*/

	for (int i = 0; i < aux; i++) {
		//PREENCHER CONTORNO
		minutiaeImage.at<Vec3b>(minutiae[i]->getX(), minutiae[i]->getY()).val[0] = 0;
		minutiaeImage.at<Vec3b>(minutiae[i]->getX(), minutiae[i]->getY()).val[1] = 0;
		minutiaeImage.at<Vec3b>(minutiae[i]->getX(), minutiae[i]->getY()).val[2] = 255;
		//minutiaesImage.at<uchar>(minutiae[i]->getX(), minutiae[i]->getY()) = 255;
	}
	cout << "aux: " << aux << endl;
	imshow("Minúcias extraídas", minutiaeImage);
	imwrite("/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2000/DB2/minucias.jpg", minutiaeImage);

	return;
}

void minutiaeExtract()
{
	//EXTRAÇÃO DE MINÚCIAS COM MINDTCT
	char *my_env[] = {NULL};
	//char *newargv_mindtct[] = {"mindtct", "/home/priscila/BDs_imagens_de_digitais/2000/DB2/101_1.jpg", "/home/priscila/Rel_4.2.0/mindtct/bin/101_1", NULL};
	char *newargv_mindtct[] = {"mindtct", "/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2000/DB2/101_1.jpg", "/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/101_1", NULL};

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
		//if(execve("/home/priscila/Rel_4.2.0/mindtct/bin/mindtct", newargv_mindtct, my_env) == -1){
		if(execve("/home/fernanda/Documents/tcc/nbis/Rel_4.2.0/mindtct/bin/mindtct", newargv_mindtct, my_env) == -1){
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

