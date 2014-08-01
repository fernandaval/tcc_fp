//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
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

	//teste
	*dpi = 500;
	imagePath = "/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif";

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
void fillWindowBorderWhite(Mat image, Mat *imageWhiteBorder, int N, int extraX, int extraY, int x, int y){
	//o programa irá dividir pela metade extraX e extraY de modo a dividir equivalentemente as bordas brancas
	//quando extraX ou extraY for ímpar, ex: 5, as bordas lateral esquerda e/ou superior serão preenchidas com
	//1 branco a menos que as bordas inferior e lateral direita

	imageWhiteBorder->create(x + extraX, y + extraY, image.type());
	//imageWhiteBorder->create(extraX/2, y, image.type());

	cout << "y: " << y << endl;
	cout << "colunas: " << image.cols << endl;
	cout << "x: " << x << endl;
	cout << "linhas: " << image.rows << endl;

	//image.at<uchar>(0,0) = 0;

	//preenche borda superior
	cout << "preenche borda superior" << endl;
	for (int i =0; i < extraX/2; i++){
		for (int j = 0; j < y + extraY; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral esquerda
	cout << "preenche lateral esquerda" << endl;
	for (int i = extraX/2; i < x + extraX/2; i++){
		for (int j = 0; j < extraY/2; j++) {
			//cout << "j: " << j << endl;
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral direita
	cout << "preenche lateral direita" << endl;
	for (int i = extraX/2; i < x + extraX/2; i++){
		for (int j = y + extraY/2; j < y + extraY; j++) {
			//cout << "j: " << j << endl;
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche borda inferior
	cout << "preenche borda inferior" << endl;
	for (int i = x + extraX/2; i < x +extraX; i++){
		for (int j = 0; j < y + extraY; j++) {
			//cout << "j: " << j << endl;
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche imagem na digital no centro
	cout << "preenche imagem na digital no centro" << endl;
	for (int i = extraX/2; i < x + extraX/2; i++){
	//for (int i = extraX/2; i < x; i++){
		cout << "i: " << i << endl;
		for (int j = extraY/2; j < y + extraY/2; j++){
		//for (int j = extraY/2; j < y ; j++){
			imageWhiteBorder->at<uchar>(i,j) = image.at<uchar>(i - extraX/2, j - extraY/2);
		}
	}


	namedWindow( "Borda", WINDOW_AUTOSIZE ); // Create a window to display image
	imshow( "Borda", *imageWhiteBorder); // Show the image inside it

	cout << "depois da janela das bordas" << endl;

//	vector< vector<int> > imageValue;


	//cout << "Vec: " << image.at<Vec>(0,0) << endl;

	//imageValue[0][0] = image.at<uchar>(0,0);

	//cout << "imageValue: " << imageValue[0][0] << endl;

	return;
}

void windowing (Mat image, int dpi, Mat *imageWhiteBorder, window** imageWindow) {
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

	//extraX e extraY indicam o quanto de faixa branca será necessário adicionar nas bordas
	extraX = x - Nx*N;
	if(extraX != 0) {
		extraX = N - extraX;
	}
	extraY = y - Ny*N;
	if(extraY != 0) {
		extraY = N - extraY;
	}

	fillWindowBorderWhite(image, imageWhiteBorder, N, extraX, extraY, x, y);

	//teste
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	cout << "N: " << N << endl;
	cout << "Nx: " << Nx << endl;
	cout << "Ny: " << Ny << endl;
	cout << "extraX: " << extraX << endl;
	cout << "extraY: " << extraY << endl;

	return;
}

int main() {
	int dpi;			//resolução da imagem em dpi's
	string imagePath;	//endereço da imagem de entrada
	Mat originalImage;	//imagem de entrada (no formato lido pelo opencv)
	window** imageWindow;
	Mat imageWhiteBorder;

	//Leitura da imagem de entrada
	imageRead(&originalImage, &dpi, imagePath);

	//faz o janelamento da imagem de acordo com a definição em dpis
	windowing(originalImage, dpi, &imageWhiteBorder, imageWindow);//, &Nx, &Ny, &x, &y);

	waitKey(0);

	return 0;
}
