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

#include "preProcessing.hpp"
#include "minutiaeExtraction.hpp"
#include "matching.hpp"
#include "window.hpp"

//#define outputPath "/home/fernanda/Documents/tcc/imagens_teste/Output/"
//#define outputPath "/home/priscila/Documents/tcc/imagens_teste/Output/"

using namespace cv;
using namespace std;

int main() {
	int dpi;			//resolução da imagem em dpi's
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	Mat imageWhiteBorder;
	int N, col, row;
	vector < vector <window*> > windows;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);
	cout << "imagem de entrada foi lida" << endl;

	//faz o janelamento da imagem de acordo com a definição em dpis

	imageMeasures (originalImage, dpi, &N, &col, &row);
	cout << "medidas da imagem foram tomadas" << endl;

	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
	windows.resize(row/N);
	for (int i = 0; i < row/N; i++){
		windows[i].resize((int)col/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windows[i][j] = new window(N, N, originalImage.type());
			//cout << "i: " << i << "; j: " << j << endl;
		}
	}

	cout << "matriz foi inicializada" << endl;

	fillWhiteBorderInImage(originalImage, &imageWhiteBorder, N, col - originalImage.cols,
			row - originalImage.rows, originalImage.cols, originalImage.rows);
	cout << "imagem preenchida com borda branca" << endl;

	createWindows(imageWhiteBorder, N, col, row, &windows);
	cout << "janelas criadas" << endl;


	equalizeWindows(N, col, row, &windows);

	recreateImage(windows, row, col, N, "imagem equalizada");

	minutiaeExtract();
	matching();

	waitKey(0);

	//TODO fazer o delete das windows

	return 0;
}
