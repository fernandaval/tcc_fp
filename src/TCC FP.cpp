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
#include "metrics.hpp"

#include "constants.hpp"


using namespace cv;
using namespace std;


VInterfaceDTO Main::getVInterfaceDTO(void){
	return this->vInterfaceDTO;
}

void runTests(VInterfaceDTO& vinterface) {
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	vector < vector <window*> > windows;

	int a,b,c;
	int option;
	b = 1;
	c = 2;
	a = 0;
	option = 2;

	while (a <= 1)
	{
		while (b <= 9)
		{
			while (c<=8)
			{
				if (10*a+b <= 10) //Só executa para ID de usuário <= 10
				{
					stringstream stra;
					stringstream strb;
					stringstream strc;
					stra << a;
					strb << b;
					strc << c;

					//imagens que deveriam ser aceitas
					string temp = imagePathTCCFP1;
					imagePath = temp + stra.str() + strb.str() + "_" + strc.str() + ".tif";

					cout << "USUARIO CADASTRADO" << endl;
					runSystem1(vinterface,imagePath,option,(a*10)+b);
					runSystem2(vinterface,imagePath,option,(a*10)+b);
					runSystem3(vinterface,imagePath,option,(a*10)+b);

					updateMetrics(true,vinterface);

					cout << "usuario NAO cadastrado" << endl;

					//imagens que deveriam ser rejeitadas
					imagePath = imagePathTCCFP2 + stra.str() + strb.str() + "_" + strc.str() + ".tif";

					runSystem1(vinterface,imagePath,option,(a*10)+b);
					runSystem2(vinterface,imagePath,option,(a*10)+b);
					runSystem3(vinterface,imagePath,option,(a*10)+b);

					updateMetrics(false,vinterface);
				}
				c = c + 1;
			}
			b = b + 1;
			c = 1;
		}
		b = 0;
		a = a + 1;
	}
}

void fillBD(VInterfaceDTO& vinterface) {
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	vector < vector <window*> > windows;

	int a,b,c, option;
	b = 1;
	c = 1;
	a = 0;
	option = 1;

	while (a <= 1)
	{
		while (b <= 9)
		{
			while (c<=1) //quantas imagens de cada pessoa queremos cadastrar
			{
				if (10*a+b <= 10) //Só executa para ID de usuário <= 10
				{
					stringstream stra;
					stringstream strb;
					stringstream strc;
					stra << a;
					strb << b;
					strc << c;
					imagePath = "/home/priscila/BDs_imagens_de_digitais/2004/DB1/1" + stra.str() + strb.str() + "_" + strc.str() + ".tif";

					runSystem1(vinterface,imagePath,option,(a*10)+b);
					cout << "cadastrei template " << strc.str() << " do usuario " << stra.str() + strb.str() << " no sistema 1" << endl;

					runSystem2(vinterface,imagePath,option,(a*10)+b);
					cout << "cadastrei template " << strc.str() << " do usuario " << stra.str() + strb.str() << " no sistema 2" << endl;

					runSystem3(vinterface,imagePath,option,(a*10)+b);
					cout << "cadastrei template " << strc.str() << " do usuario " << stra.str() + strb.str() << " no sistema 3" << endl;

				}
				c = c + 1;
			}
			b = b + 1;
			c = 1;
		}
		b = 0;
		a = a + 1;
	}
}

void runSystem1(VInterfaceDTO& vinterface, string imagePath, int option, int idUser) {

	int idSystem = 1;
	int dpi;			//resolução da imagem em dpi's
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	int N, col, row;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);

	imwrite(originalPath,originalImage);

	imageMeasures (originalImage, dpi, &N, &col, &row); //retorna coluna e linha da imagem final com borda

	//Converte a imagem no formato colorido para que seja possível utilizá-la na hora de exibir as minúcias (em cor)
	Mat minutiaeImage;
	cvtColor(originalImage, minutiaeImage, CV_GRAY2RGB);

	//MINUTIA EXTRACTION
	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
	gettimeofday (&minutiaeExtractionTimeBefore, NULL);
	minutiaeExtract(originalImage,idSystem,option,idUser);
	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
				+ (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
	//cout << "minutiaeExtractionTime(1): " << minutiaeExtractionTime << " segundos" << endl;
	vinterface.setMinutiaeExtractionTime1(minutiaeExtractionTime);

	minutiaePlot(row, col, N, minutiaeImage,idSystem,vinterface);
	imwrite(minutiae1Path, minutiaeImage);

	if (option == 2) {
		struct timeval matchingTimeBefore, matchingTimeAfter;  // removed comma
		gettimeofday (&matchingTimeBefore, NULL);
		bool result1 = matching(idSystem,1);
		vinterface.setAccepted1(result1);

		gettimeofday (&matchingTimeAfter, NULL);
		float matchingTime = ((matchingTimeAfter.tv_sec - matchingTimeBefore.tv_sec)
					+ (matchingTimeAfter.tv_usec - matchingTimeBefore.tv_usec)/(float)1000000);
		//cout << "matchingTime(1): " << matchingTime << " segundos" << endl;
		vinterface.setMatchingTime1(matchingTime);

		if (result1 == true) cout << "Usuario aceito!(1)" << endl;
		else cout << "Usuario recusado.(1)" << endl;

	}

}

void runSystem2(VInterfaceDTO& vinterface, string imagePath, int option, int idUser) {

	int idSystem = 2;
	int dpi;			//resolução da imagem em dpi's
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	int N, col, row;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);

	imageMeasures (originalImage, dpi, &N, &col, &row); //retorna coluna e linha da imagem final com borda

	Mat equalizedImage;
	//EQUALIZATION
	struct timeval equalizationTimeBefore, equalizationTimeAfter;  // removed comma
	gettimeofday (&equalizationTimeBefore, NULL);
	equalize(&originalImage,&equalizedImage);
	gettimeofday (&equalizationTimeAfter, NULL);
	float equalizationTime = ((equalizationTimeAfter.tv_sec - equalizationTimeBefore.tv_sec)
				+ (equalizationTimeAfter.tv_usec - equalizationTimeBefore.tv_usec)/(float)1000000);
	//cout << "equalizationTime(2): " << equalizationTime << " segundos" << endl;
	vinterface.setEqualizationTime2(equalizationTime);

	imwrite(equalized2Path, equalizedImage);

	//BINARIZATION
	struct timeval binarizationTimeBefore, binarizationTimeAfter;  // removed comma
	gettimeofday (&binarizationTimeBefore, NULL);
	//binarization(&windows, row, col, N);
	imageBinarization (&equalizedImage);
	gettimeofday (&binarizationTimeAfter, NULL);
	float binarizationTime = ((binarizationTimeAfter.tv_sec - binarizationTimeBefore.tv_sec)
				+ (binarizationTimeAfter.tv_usec - binarizationTimeBefore.tv_usec)/(float)1000000);
	//cout << "binarizationTime(2): " << binarizationTime << " segundos" << endl;
	vinterface.setBinarizationTime2(binarizationTime);

	imwrite(binarized2Path, equalizedImage);

	//THINNING
	/*
	struct timeval thinningTimeBefore, thinningTimeAfter;  // removed comma
	gettimeofday (&thinningTimeBefore, NULL);

	//thinning(imageAfterGabor);

	gettimeofday (&thinningTimeAfter, NULL);
	float thinningTime = ((thinningTimeAfter.tv_sec - thinningTimeBefore.tv_sec)
				+ (thinningTimeAfter.tv_usec - thinningTimeBefore.tv_usec)/(float)1000000);
	//cout << "thinningTime(2): " << thinningTime << " segundos" << endl;
	*/

	//Converte a imagem no formato colorido para que seja possível utilizá-la na hora de exibir as minúcias (em cor)
	Mat minutiaeImage;
	cvtColor(equalizedImage, minutiaeImage, CV_GRAY2RGB);

	//MINUTIA EXTRACTION
	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
	gettimeofday (&minutiaeExtractionTimeBefore, NULL);

	minutiaeExtract(equalizedImage,idSystem,option,idUser);

	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
				+ (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
	//cout << "minutiaeExtractionTime(2): " << minutiaeExtractionTime << " segundos" << endl;
	vinterface.setMinutiaeExtractionTime2(minutiaeExtractionTime);

	minutiaePlot(row, col, N, minutiaeImage,idSystem,vinterface);

	imwrite(minutiae2Path, minutiaeImage);

	if (option == 2) {
		struct timeval matchingTimeBefore, matchingTimeAfter;  // removed comma
		gettimeofday (&matchingTimeBefore, NULL);
		bool result2 = matching(idSystem,1);
		vinterface.setAccepted2(result2);

		gettimeofday (&matchingTimeAfter, NULL);
		float matchingTime = ((matchingTimeAfter.tv_sec - matchingTimeBefore.tv_sec)
					+ (matchingTimeAfter.tv_usec - matchingTimeBefore.tv_usec)/(float)1000000);
		//cout << "matchingTime(2): " << matchingTime << " segundos" << endl;
		vinterface.setMatchingTime2(matchingTime);

		if (result2 == true) cout << "Usuario aceito!(2)" << endl;
		else cout << "Usuario recusado.(2)" << endl;

	}

}

void runSystem3(VInterfaceDTO& vinterface, string imagePath, int option, int idUser) {

	int idSystem = 3;
	int dpi;			//resolução da imagem em dpi's
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
	//cout << "windowingTime(3): " << windowingTime << " segundos" << endl;
	vinterface.setWindowingTime3(windowingTime);
	//cria as janelas após adicionar bordas brancas
	createWindows(imageWhiteBorder, N, col, row, &windows);

	imwrite(whiteBorder3Path, imageWhiteBorder);

	//EQUALIZATION
	struct timeval equalizationTimeBefore, equalizationTimeAfter;  // removed comma
	gettimeofday (&equalizationTimeBefore, NULL);
	equalizeWindows(N, col, row, &windows);
	gettimeofday (&equalizationTimeAfter, NULL);
	float equalizationTime = ((equalizationTimeAfter.tv_sec - equalizationTimeBefore.tv_sec)
				+ (equalizationTimeAfter.tv_usec - equalizationTimeBefore.tv_usec)/(float)1000000);
	//cout << "equalizationTime(3): " << equalizationTime << " segundos" << endl;
	vinterface.setEqualizationTime3(equalizationTime);
	recreateImagePath(windows, row, col, N, equalized3Path);

	//GABOR (including Orientation Map and Frequency Map)
	Mat fullImage;
	fullImage.create(row, col, CV_8UC1);
	groupImageWindows(&fullImage, windows, row, col, N);
	struct timeval gaborFilterTimeBefore, gaborFilterTimeAfter;  // removed comma
	gettimeofday (&gaborFilterTimeBefore, NULL);
//	orientationMapOLD(&windows, row, col, N);
	orientationMap(&windows, row, col, N);
//	frequencyMap(&windows, row, col, N);
	//cout << "depois mapa de orientação, antes gabor" << endl;
	gaborFilter (&windows, row, col, N);
	//cout << "depois gabor" << endl;
	gettimeofday (&gaborFilterTimeAfter, NULL);
	float gaborFilterTime = ((gaborFilterTimeAfter.tv_sec - gaborFilterTimeBefore.tv_sec)
	            + (gaborFilterTimeAfter.tv_usec - gaborFilterTimeBefore.tv_usec)/(float)1000000);
	//cout << "gaborFilterTime(3): " << gaborFilterTime << " segundos" << endl;
	//recreateImage(windows, row, col, N, "Gabor");

	//código temporário para teste
	Mat imageAfterGabor;
	imageAfterGabor.create(row, col, CV_8UC1);
	groupImageWindows(&imageAfterGabor, windows, row, col, N);

	vinterface.setGaborFilterTime3(gaborFilterTime);
	imwrite(gabor3Path, imageAfterGabor);

	//BINARIZATION
	struct timeval binarizationTimeBefore, binarizationTimeAfter;  // removed comma
	gettimeofday (&binarizationTimeBefore, NULL);
	//binarization(&windows, row, col, N);
	imageBinarization (&imageAfterGabor);
	gettimeofday (&binarizationTimeAfter, NULL);
	float binarizationTime = ((binarizationTimeAfter.tv_sec - binarizationTimeBefore.tv_sec)
				+ (binarizationTimeAfter.tv_usec - binarizationTimeBefore.tv_usec)/(float)1000000);
	//cout << "binarizationTime(3): " << binarizationTime << " segundos" << endl;
	vinterface.setBinarizationTime3(binarizationTime);
	imwrite(binarized3Path,imageAfterGabor);

	//THINNING

	/*struct timeval thinningTimeBefore, thinningTimeAfter;  // removed comma
	gettimeofday (&thinningTimeBefore, NULL);

	thinning(imageAfterGabor);

	gettimeofday (&thinningTimeAfter, NULL);
	float thinningTime = ((thinningTimeAfter.tv_sec - thinningTimeBefore.tv_sec)
				+ (thinningTimeAfter.tv_usec - thinningTimeBefore.tv_usec)/(float)1000000);
	cout << "thinningTime(3): " << thinningTime << " segundos" << endl;*/


	//Converte a imagem no formato colorido para que seja possível utilizá-la na hora de exibir as minúcias (em cor)
	Mat minutiaeImage;
	cvtColor(imageAfterGabor, minutiaeImage, CV_GRAY2RGB);

	//MINUTIA EXTRACTION
	struct timeval minutiaeExtractionTimeBefore, minutiaeExtractionTimeAfter;  // removed comma
	gettimeofday (&minutiaeExtractionTimeBefore, NULL);
	minutiaeExtract(imageAfterGabor,idSystem,option,idUser);
	gettimeofday (&minutiaeExtractionTimeAfter, NULL);
	float minutiaeExtractionTime = ((minutiaeExtractionTimeAfter.tv_sec - minutiaeExtractionTimeBefore.tv_sec)
				+ (minutiaeExtractionTimeAfter.tv_usec - minutiaeExtractionTimeBefore.tv_usec)/(float)1000000);
	//cout << "minutiaeExtractionTime(3): " << minutiaeExtractionTime << " segundos" << endl;
	vinterface.setMinutiaeExtractionTime3(minutiaeExtractionTime);

	minutiaePlot(row, col, N, minutiaeImage,idSystem,vinterface);
	imwrite(minutiae3Path, minutiaeImage);

	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			delete windows[i][j];
		}
	}

	if (option == 2) {
		//MODO 1 (padrao)
		struct timeval matchingTimeBefore31, matchingTimeAfter31;  // removed comma
		gettimeofday (&matchingTimeBefore31, NULL);
		bool result31 = matching(idSystem,1);
		vinterface.setAccepted31(result31);

		gettimeofday (&matchingTimeAfter31, NULL);
		float matchingTime31 = ((matchingTimeAfter31.tv_sec - matchingTimeBefore31.tv_sec)
					+ (matchingTimeAfter31.tv_usec - matchingTimeBefore31.tv_usec)/(float)1000000);
		//cout << "matchingTime(3): " << matchingTime << " segundos" << endl;
		vinterface.setMatchingTime31(matchingTime31);

		//MODO 2 (tolerante)
		struct timeval matchingTimeBefore32, matchingTimeAfter32;  // removed comma
		gettimeofday (&matchingTimeBefore32, NULL);
		bool result32 = matching(idSystem,2);
		vinterface.setAccepted32(result32);

		gettimeofday (&matchingTimeAfter32, NULL);
		float matchingTime32 = ((matchingTimeAfter32.tv_sec - matchingTimeBefore32.tv_sec)
					+ (matchingTimeAfter32.tv_usec - matchingTimeBefore32.tv_usec)/(float)1000000);
		//cout << "matchingTime(3): " << matchingTime << " segundos" << endl;
		vinterface.setMatchingTime32(matchingTime32);

		//MODO 3 (rigoroso)
		struct timeval matchingTimeBefore33, matchingTimeAfter33;  // removed comma
		gettimeofday (&matchingTimeBefore33, NULL);
		bool result33 = matching(idSystem,3);
		vinterface.setAccepted33(result33);

		gettimeofday (&matchingTimeAfter33, NULL);
		float matchingTime33 = ((matchingTimeAfter33.tv_sec - matchingTimeBefore33.tv_sec)
					+ (matchingTimeAfter33.tv_usec - matchingTimeBefore33.tv_usec)/(float)1000000);
		//cout << "matchingTime(3): " << matchingTime << " segundos" << endl;
		vinterface.setMatchingTime33(matchingTime33);

		if (result31 == true) cout << "Usuario aceito!(31)" << endl;
		else cout << "Usuario recusado.(31)" << endl;

		if (result32 == true) cout << "Usuario aceito!(32)" << endl;
		else cout << "Usuario recusado.(32)" << endl;

		if (result33 == true) cout << "Usuario aceito!(33)" << endl;
		else cout << "Usuario recusado.(33)" << endl;
	}

}

void Main::updateMetrics(bool feedback, HasCallbackClass *_clazz) {

	metricsUpdate(feedback,this->vInterfaceDTO.getAccepted1(),this->vInterfaceDTO.getAccepted2(),this->vInterfaceDTO.getAccepted31(),this->vInterfaceDTO.getAccepted32(),this->vInterfaceDTO.getAccepted33());

	minimumScoresUpdate();

	//cout << "Feedback: " << feedback << endl;

	_clazz->callback();
}

void updateMetrics(bool feedback, VInterfaceDTO& vinterface) {

	metricsUpdate(feedback,vinterface.getAccepted1(),vinterface.getAccepted2(),vinterface.getAccepted31(),vinterface.getAccepted32(),vinterface.getAccepted33());
	minimumScoresUpdate();

}

void Main::getMetrics(HasCallbackClass *_clazz) {

	refreshAllMetrics(this->vInterfaceDTO);

	_clazz->callback();
}

void Main::showImage (string path){
	Mat image = imread(path.substr(7,path.length()));
	namedWindow( "Selected Image", WINDOW_AUTOSIZE ); // Create a window to display image
	imshow( "Selected Image", image ); // Show the image inside it
}

void Main::execute(HasCallbackClass *_clazz, string imagePath) {

	//fillBD(this->vInterfaceDTO);

	//imagePath = "/home/priscila/BDs_imagens_de_digitais/2004/DB1/108_8.tif"; //apenas para teste

	runSystem1(this->vInterfaceDTO, imagePath,2,0);
	runSystem2(this->vInterfaceDTO, imagePath,2,0);
	runSystem3(this->vInterfaceDTO, imagePath,2,0);

	//runTests(this->vInterfaceDTO);

	_clazz->callback();
	//waitKey(0);

	//TODO fazer o delete das windows
}
