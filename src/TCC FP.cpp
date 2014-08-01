//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

struct window {
	int startX;
	int startY;
	int N;
	int quality;
};

void imageRead (Mat *image, int *dpi, string imagePath) {
	string teste;

	cout << "Quantos DPIs tem sua imagem? "; // prints !!!Hello World!!!
	cin >> *dpi;

	cout << "Digite o endereço da sua imagem (Ex: /home/Pictures/image.jpg): "; //get o imagePath
	cin >> imagePath;

	//Ao carregar a imagem, já se garante que será em tons de cinza
	//image = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
	*image = imread("/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Verifica se a imagem de entrada é válida
	if(! (*image).data ){
		cout <<  "Não foi possível abrir ou encontrar a imagem." << std::endl ;
		return;
	}
	else{
		namedWindow( "Display original image", CV_WINDOW_AUTOSIZE ); // Create a window to display image
		imshow( "Display original image", *image ); // Show the image inside it

		//teste
		cout << "mostrou" << endl;

		imwrite("/home/fernanda/Documents/tcc/imagens_teste/teste.tif", *image); // salva a imagem lida no diretório mencionada
	}

	//teste
	cout << "dpi" << endl;
	cout << dpi << endl;

	return;
}

void windowing (Mat image, int dpi, Mat *window, window** imageWindow) {//, int *N, int *Nx, int *Ny, int *x, int *y){
	int x, y;
	int N, Nx, Ny;
	int extraX, extraY;

	x = image.rows;
	y = image.cols;

	//para 500 dpi, janelas de 17 x 17, a proporção é de dpi/N = 29
	//as janelas da última coluna direita e da última linha podem ser um pouco maiores ou menores
	N = dpi/29;

	Nx = x/N;
	Ny = y/N;

	extraX = x - Nx*N;
	extraY = y - Ny*N;

	//teste
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "N: " << N << endl;
	cout << "Nx: " << Nx << endl;
	cout << "Ny: " << Ny << endl;
	cout << "extraX" << extraX << endl;

	return;
}

int main() {
	int dpi;			//resolução da imagem em dpi's
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	int x, y;			//tamanho da imagem original nos eixos x e y
	int N;				//dimensão das janelas
	int Nx, Ny;			//quantidade de janelas nos eixos x e y
	window** imageWindow;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);

	//faz o janelamento da imagem de acordo com a definição em dpis
	windowing(originalImage, dpi, &N, &imageWindow);//, &Nx, &Ny, &x, &y);

	return 0;
}
