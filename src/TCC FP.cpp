//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Fingerprint Identification Algorithm
//============================================================================

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

#include "preProcessing.hpp"
#include "minutiaeExtraction.hpp"
#include "matching.hpp"
#include "window.hpp"
#include "TCC FP.hpp"

using namespace cv;
using namespace std;


VInterfaceDTO Main::getVInterfaceDTO(void){
	return this->vInterfaceDTO;
}

void Main::fillBD() {
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	Mat imageWhiteBorder;
	int N, col, row;
	vector < vector <window*> > windows;

	int a,b,c;
	b = 1;
	c = 1;
	a = 0;
	while (a <= 1)
	{
		while (b <= 9)
		{
			while (c<=4)
			{
				stringstream stra;
				stringstream strb;
				stringstream strc;
				stra << a;
				strb << b;
				strc << c;
				imagePath = "/home/priscila/BDs_imagens_de_digitais/2004/DB1/1" + stra.str() + strb.str() + "_" + strc.str() + ".tif";

				originalImage = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
				imageMeasures (originalImage, 500, &N, &col, &row);

				//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
				windows.resize(row/N);
				for (int i = 0; i < row/N; i++){
					windows[i].resize((int)col/N);
				}

				//inicializando a matriz com as janelas (usando a classe window)
				for (int i = 0; i < row/N; i++){
					for (int j = 0; j < col/N;  j++){
						windows[i][j] = new window(N, N, originalImage.type());
					}
				}

				fillWhiteBorderInImage(originalImage, &imageWhiteBorder, N, col - originalImage.cols,
						row - originalImage.rows, originalImage.cols, originalImage.rows);

				createWindows(imageWhiteBorder, N, col, row, &windows);
				equalizeWindows(N, col, row, &windows);
				orientationMap(&windows, row, col, N);
				binarization(&windows, row, col, N);

				Mat imageNew;
				imageNew.create(row, col, CV_8UC3);
				groupImageWindows(&imageNew, windows, row, col, N);

				minutiaeExtract(imageNew,1,(a*10)+b);

				c = c + 1;
			}
			b = b + 1;
			c = 1;
		}
		b = 0;
		a = a + 1;
	}
}


void Main::execute(SystemMode mode,  HasCallbackClass *_clazz) {
	int dpi;			//resolução da imagem em dpi's
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	Mat imageWhiteBorder;
	int N, col, row;
	vector < vector <window*> > windows;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);

	imageMeasures (originalImage, dpi, &N, &col, &row); //retorna coluna e linha da imagem final com borda

	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
	windows.resize(row/N);
	for (int i = 0; i < row/N; i++){
		windows[i].resize((int)col/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windows[i][j] = new window(N, N, originalImage.type());
		}
	}

	//WINDOWING
	struct timeval windowingTimeBefore, windowingTimeAfter;  // removed comma
	gettimeofday (&windowingTimeBefore, NULL);
	fillWhiteBorderInImage(originalImage, &imageWhiteBorder, N, col - originalImage.cols,
			row - originalImage.rows, originalImage.cols, originalImage.rows);
	gettimeofday (&windowingTimeAfter, NULL);
	float windowingTime = ((windowingTimeAfter.tv_sec - windowingTimeBefore.tv_sec)
            + (windowingTimeAfter.tv_usec - windowingTimeBefore.tv_usec)/(float)1000000);
	cout << "windowingTime: " << windowingTime << " segundos" << endl;
	this->vInterfaceDTO.setWindowingTime(windowingTime);
	//cria as janelas após adicionar bordas brancas
	createWindows(imageWhiteBorder, N, col, row, &windows);

	//EQUALIZATION
	struct timeval equalizationTimeBefore, equalizationTimeAfter;  // removed comma
	gettimeofday (&equalizationTimeBefore, NULL);
	equalizeWindows(N, col, row, &windows);
	gettimeofday (&equalizationTimeAfter, NULL);
	float equalizationTime = ((equalizationTimeAfter.tv_sec - equalizationTimeBefore.tv_sec)
	            + (equalizationTimeAfter.tv_usec - equalizationTimeBefore.tv_usec)/(float)1000000);
	cout << "equalizationTime: " << equalizationTime << " segundos" << endl;
	this->vInterfaceDTO.setEqualizationTime(equalizationTime);
	recreateImage(windows, row, col, N, "imagem equalizada");

	//GABOR (including Orientation Map and Frequency Map)
	struct timeval gaborFilterTimeBefore, gaborFilterTimeAfter;  // removed comma
	gettimeofday (&gaborFilterTimeBefore, NULL);
	orientationMap(&windows, row, col, N);
	frequencyMap(&windows, row, col, N);
	gaborFilter (&windows, row, col, N);
	gettimeofday (&gaborFilterTimeAfter, NULL);
	float gaborFilterTime = ((gaborFilterTimeAfter.tv_sec - gaborFilterTimeBefore.tv_sec)
	            + (gaborFilterTimeAfter.tv_usec - gaborFilterTimeBefore.tv_usec)/(float)1000000);
	cout << "gaborFilterTime: " << gaborFilterTime << " segundos" << endl;
	this->vInterfaceDTO.setGaborFilterTime(gaborFilterTime);
	recreateImage(windows, row, col, N, "Gabor");

	//BINARIZATION
	struct timeval binarizationTimeBefore, binarizationTimeAfter;  // removed comma
	gettimeofday (&binarizationTimeBefore, NULL);
	//gaborFilter (&windows, row, col, N);
	//recreateImage(windows, row, col, N, "Gabor");
	binarization(&windows, row, col, N);
	gettimeofday (&binarizationTimeAfter, NULL);
	float binarizationTime = ((binarizationTimeAfter.tv_sec - binarizationTimeBefore.tv_sec)
	            + (binarizationTimeAfter.tv_usec - binarizationTimeBefore.tv_usec)/(float)1000000);
	cout << "binarizationTime: " << binarizationTime << " segundos" << endl;
	this->vInterfaceDTO.setBinarizationTime(binarizationTime);
	recreateImage(windows, row, col, N, "imagem binarizada");

	//THINNING
	/*
	struct timeval thinningTimeBefore, thinningTimeAfter;  // removed comma
	gettimeofday (&thinningTimeBefore, NULL);
	thinningWindows(&windows, row, col, N);
	gettimeofday (&thinningTimeAfter, NULL);
	float thinningTime = ((thinningTimeAfter.tv_sec - thinningTimeBefore.tv_sec)
	            + (thinningTimeAfter.tv_usec - thinningTimeBefore.tv_usec)/(float)1000000);
	cout << "thinningTime: " << thinningTime << " segundos" << endl;
	recreateImage(windows, row, col, N, "imagem afinada");
	*/

	Mat imageNew;
	imageNew.create(row, col, CV_8UC3);
	groupImageWindows(&imageNew, windows, row, col, N);
	imshow("imagem refeita", imageNew);
	/*thinning(imageNew);
	imshow("imagem afinada", imageNew);
	*/

//	//MINUTIAE EXTRACTION
//	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
//	gettimeofday (&minutiaeExtractionTimeBefore, NULL);
//	minutiaeExtract(imageNew);
//	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
//	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
//	            + (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
//	cout << "minutiaeExtractionTime: " << minutiaeExtractionTime << " segundos" << endl;
//	this->vInterfaceDTO.setMinutiaeExtractionTime(minutiaeExtractionTime);
//	//Plota as minúcias extraídas em uma nova imagem
//	minutiaePlot(&windows, row, col, N, imageNew);

//	//MATCHING
//	struct timeval matchingTimeBefore, matchingTimeAfter;  // removed comma
//	gettimeofday (&matchingTimeBefore, NULL);
//	bool resultado = matching();
//	gettimeofday (&matchingTimeAfter, NULL);
//	float matchingTime = ((matchingTimeAfter.tv_sec - matchingTimeBefore.tv_sec)
//	            + (matchingTimeAfter.tv_usec - matchingTimeBefore.tv_usec)/(float)1000000);
//	cout << "matchingTime: " << matchingTime << " segundos" << endl;
//	this->vInterfaceDTO.setMatchingTime(matchingTime);

	int option = 2;
	cout << "O que você deseja fazer com a imagem: 1- cadastrar no BD 2- autenticar no sistema" << endl;
	cin >> option;
	int id = 0;
	if (option == 1) {
		cout << "Para qual usuário você deseja cadastrar essa imagem? Digite a ID" << endl;
		cin >> id;
	}

	//MINUTIA EXTRACTION
	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
	gettimeofday (&minutiaeExtractionTimeBefore, NULL);
	minutiaeExtract(imageNew,option,id);
	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
				+ (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
	cout << "minutiaeExtractionTime: " << minutiaeExtractionTime << " segundos" << endl;
	this->vInterfaceDTO.setMinutiaeExtractionTime(minutiaeExtractionTime);



	minutiaePlot(&windows, row, col, N, imageNew);

	if (option == 2) {
		struct timeval matchingTimeBefore, matchingTimeAfter;  // removed comma
		gettimeofday (&matchingTimeBefore, NULL);
		bool resultado = matching();
		gettimeofday (&matchingTimeAfter, NULL);
		float matchingTime = ((matchingTimeAfter.tv_sec - matchingTimeBefore.tv_sec)
					+ (matchingTimeAfter.tv_usec - matchingTimeBefore.tv_usec)/(float)1000000);
		cout << "matchingTime: " << matchingTime << " segundos" << endl;
		this->vInterfaceDTO.setMatchingTime(matchingTime);


		if (resultado == true) cout << "Usuario aceito!" << endl;
		else cout << "Usuario recusado." << endl;
	}

	_clazz->callback();
	waitKey(0);

	//TODO fazer o delete das windows

}
