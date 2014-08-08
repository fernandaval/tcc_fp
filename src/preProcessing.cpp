//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Fingerprint Identification Algorithm
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#define outputPath "/home/fernanda/Documents/tcc/imagens_teste/Output/"
#define outputPath "/home/priscila/Documents/tcc/imagens_teste/Output/"

using namespace cv;
using namespace std;

class window {
	public :

	int quality;
	double frequency;
	double angle;
	Mat imageWindow;

	//construtor
	window(int imageRowSize, int imageColSize, int imageType) {
		quality = -1;
		frequency = -1;
		angle = -1;
		imageWindow.create(imageRowSize, imageColSize, imageType);
	}
};


//lê uma imagem de entrada e altera "image"
void imageRead (Mat *image, int *dpi, string imagePath) {

	//teste
	*dpi = 500;
	//imagePath = "/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif";
	imagePath = "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.jpg";

	cout << "Quantos DPIs tem sua imagem? "; // prints !!!Hello World!!!
	//cin >> *dpi;

	cout << "Digite o endereço da sua imagem (Ex: /home/Pictures/image.jpg): "; //get o imagePath
	//cin >> imagePath;

	//Ao carregar a imagem, já se garante que será em tons de cinza
	*image = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
	//*image = imread("/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Verifica se a imagem de entrada é válida
	if(! image->data ){
		cout <<  "Não foi possível abrir ou encontrar a imagem." << std::endl ;
		return;
	}
	else{
		namedWindow( "Display original image", WINDOW_AUTOSIZE ); // Create a window to display image
		imshow( "Display original image", *image ); // Show the image inside it
	}

	//teste
	cout << "dpi: " << *dpi << endl;

	return;
}

//Preenche a borda da imagem com brancos para garantir que o janelamento terá 100% das janelas quadradas
void fillWhiteBorderInImage(Mat image, Mat *imageWhiteBorder, int N, int extraX, int extraY, int x, int y){
	//o programa irá dividir pela metade extraX e extraY de modo a dividir equivalentemente as bordas brancas
	//quando extraX ou extraY for ímpar, ex: 5, as bordas lateral esquerda e/ou superior serão preenchidas com
	//1 branco a menos que as bordas inferior e lateral direita

	String imageWhiteBorderOutputPath;
	String imageOutputPath;

	imageWhiteBorder->create(y + extraY, x + extraX, image.type());

	cout << "y: " << y << endl;
	cout << "linhas: " << image.rows << endl;
	cout << "x: " << x << endl;
	cout << "colunas: " << image.cols << endl;

	//preenche borda superior
	for (int i =0; i < extraY/2; i++){
		for (int j = 0; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral esquerda
	for (int i = extraY/2; i < y + extraY/2; i++){
		for (int j = 0; j < extraX/2; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral direita
	for (int i = extraY/2; i < y + extraY/2; i++){
		for (int j = x + extraX/2; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche borda inferior
	for (int i = y + extraY/2; i < y + extraY; i++){
		for (int j = 0; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche imagem na digital no centro
	for (int i = extraY/2; i < y + extraY/2; i++){
	//for (int i = extraX/2; i < x; i++){
		for (int j = extraX/2; j < x + extraX/2; j++){
		//for (int j = extraY/2; j < y ; j++){
			imageWhiteBorder->at<uchar>(i,j) = image.at<uchar>(i - extraY/2, j - extraX/2);
		}
	}

	namedWindow( "Borda branca", WINDOW_AUTOSIZE ); // Create a window to display image
	imshow( "Borda branca", *imageWhiteBorder); // Show the image inside it

	imageWhiteBorderOutputPath.append(outputPath);
	imageWhiteBorderOutputPath.append("imageWhiteBorder.tiff");

	imageOutputPath.append(outputPath);
	imageOutputPath.append("image.tiff");

	imwrite(imageWhiteBorderOutputPath, *imageWhiteBorder);
	imwrite(imageOutputPath, image);
	return;
}

void equalizeWindows(int N, int col, int row, vector< vector <window*> > *windows) {

	for (int j = 0; j < col/N; j++) {
		for (int i = 0; i < row/N; i++) {
			equalizeHist((*windows)[i][j]->imageWindow, (*windows)[i][j]->imageWindow);

			//TESTE
			//salva a imagem equalizada
			String equalizedImageoutputPath;

			equalizedImageoutputPath.append(outputPath);
			equalizedImageoutputPath.append("equalizedWindow_");
			ostringstream iString;
			ostringstream jString;
			iString << i;
			jString << j;
			equalizedImageoutputPath.append(iString.str());
			equalizedImageoutputPath.append("_");
			equalizedImageoutputPath.append(jString.str());
			equalizedImageoutputPath.append(".tiff");
			imwrite(equalizedImageoutputPath, (*windows)[i][j]->imageWindow);
			//FIM TESTE
		}
	}

	return;
}

//Altera a matriz com cada um adas janelas, criando uma por uma (a partir de uma imagem de entrada -> imageWhiteBorder)
void createWindows(Mat imageWhiteBorder, int N, int column, int row, vector< vector <window*> > *windows) {
	for (int j = 0; j < column/N; j++) {
		for (int i = 0; i < row/N; i++){
			//preenche cada pixel da janela de acordo com a leitura da imagem completa com a borda branca
			for (int l = 0; l < N; l++) {
				for (int m = 0; m < N; m++) {
					(*windows)[i][j]->imageWindow.at<uchar>(l,m) = imageWhiteBorder.at<uchar>(i*N + l, j*N + m);
				}
			}
			string imgName;
			imgName = outputPath;
			imgName.append("window_");

			ostringstream iString;
			ostringstream jString;
			iString << i;
			jString << j;
			imgName.append(iString.str());
			imgName.append("_");
			imgName.append(jString.str());
			imgName.append(".tiff");

			imwrite(imgName, (*windows)[i][j]->imageWindow);

		}
	}
}

//Retorna as medidas da imagem que serão necessárias para realizar o janelamento
void imageMeasures(Mat image, int dpi, int *N, int *col, int *row) {
	int x, y, extraX, extraY, Nx, Ny;

	y = image.rows;
	x = image.cols;

	//para 500 dpi, janelas de 17 x 17, a proporção é de dpi/N = 29
	//as janelas da última coluna direita e da última linha podem ser um pouco maiores ou menores
	(*N) = dpi/29;

	Nx = x/(*N);
	Ny = y/(*N);

	//extraX e extraY indicam o quanto de faixa branca será necessário adicionar nas bordas
	extraX = x - Nx*(*N);
	if(extraX != 0) {
		extraX = (*N) - extraX;
	}
	extraY = y - Ny*(*N);
	if(extraY != 0) {
		extraY = (*N) - extraY;
	}

	(*col) = x + extraX;
	(*row) = y + extraY;

	return;
}
