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

void Main::execute() {
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
	recreateImage(windows, row, col, N, "Gabor");

	//BINARIZATION
	struct timeval binarizationTimeBefore, binarizationTimeAfter;  // removed comma
	gettimeofday (&binarizationTimeBefore, NULL);
	binarization(&windows, row, col, N);
	gettimeofday (&binarizationTimeAfter, NULL);
	float binarizationTime = ((binarizationTimeAfter.tv_sec - binarizationTimeBefore.tv_sec)
	            + (binarizationTimeAfter.tv_usec - binarizationTimeBefore.tv_usec)/(float)1000000);
	cout << "binarizationTime: " << binarizationTime << " segundos" << endl;
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

	//MINUTIAE EXTRACTION
	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
	gettimeofday (&minutiaeExtractionTimeBefore, NULL);
	minutiaeExtract(imageNew);
	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
	            + (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
	cout << "minutiaeExtractionTime: " << minutiaeExtractionTime << " segundos" << endl;
	//Plota as minúcias extraídas em uma nova imagem
	minutiaePlot(&windows, row, col, N, imageNew);

	//MATCHING
	struct timeval matchingTimeBefore, matchingTimeAfter;  // removed comma
	gettimeofday (&matchingTimeBefore, NULL);
	bool resultado = matching();
	gettimeofday (&matchingTimeAfter, NULL);
	float matchingTime = ((matchingTimeAfter.tv_sec - matchingTimeBefore.tv_sec)
	            + (matchingTimeAfter.tv_usec - matchingTimeBefore.tv_usec)/(float)1000000);
	cout << "matchingTime: " << matchingTime << " segundos" << endl;

	if (resultado == true) cout << "Access accepted!" << endl;
	else cout << "Access denied." << endl;

	waitKey(0);

	//TODO fazer o delete das windows

}
