//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class window {
	public :

	int quality;
	double frequency;
	double angle;
	Mat imageWindow;

	window(int imageRowSize, int imageColSize, int imageType) {
		quality = -1;
		frequency = -1;
		angle = -1;
		imageWindow.create(imageRowSize, imageColSize, imageType);
	}
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
void fillWhiteBorderInImage(Mat image, Mat *imageWhiteBorder, int N, int extraX, int extraY, int x, int y){
	//o programa irá dividir pela metade extraX e extraY de modo a dividir equivalentemente as bordas brancas
	//quando extraX ou extraY for ímpar, ex: 5, as bordas lateral esquerda e/ou superior serão preenchidas com
	//1 branco a menos que as bordas inferior e lateral direita

	imageWhiteBorder->create(y + extraY, x + extraX, image.type());
	//imageWhiteBorder->create(extraX/2, y, image.type());

	cout << "y: " << y << endl;
	cout << "colunas: " << image.cols << endl;
	cout << "x: " << x << endl;
	cout << "linhas: " << image.rows << endl;

	//image.at<uchar>(0,0) = 0;

	//preenche borda superior
	cout << "preenche borda superior" << endl;
	for (int i =0; i < extraY/2; i++){
		for (int j = 0; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral esquerda
	cout << "preenche lateral esquerda" << endl;
	for (int i = extraY/2; i < y + extraY/2; i++){
		for (int j = 0; j < extraX/2; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche lateral direita
	cout << "preenche lateral direita" << endl;
	for (int i = extraY/2; i < y + extraY/2; i++){
		for (int j = x + extraX/2; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche borda inferior
	cout << "preenche borda inferior" << endl;
	for (int i = y + extraY/2; i < y + extraY; i++){
		for (int j = 0; j < x + extraX; j++) {
			imageWhiteBorder->at<uchar>(i,j) = 255;
		}
	}

	//preenche imagem na digital no centro
	cout << "preenche imagem na digital no centro" << endl;
	for (int i = extraY/2; i < y + extraY/2; i++){
	//for (int i = extraX/2; i < x; i++){
		for (int j = extraX/2; j < x + extraX/2; j++){
		//for (int j = extraY/2; j < y ; j++){
			imageWhiteBorder->at<uchar>(i,j) = image.at<uchar>(i - extraY/2, j - extraX/2);
		}
	}

	namedWindow( "Borda branca", WINDOW_AUTOSIZE ); // Create a window to display image
	imshow( "Borda branca", *imageWhiteBorder); // Show the image inside it

	imwrite("imageWhiteBorder.tiff", *imageWhiteBorder);
	imwrite("image.tiff", image);
	return;
}

void createWindows(Mat imageWhiteBorder, int N, int column, int row, vector< vector <window*> > *windows) {
	for (int j = 0; j < column/N; j++) {
		for (int i = 0; i < row/N; i++){
			//preenche cada pixel da janela de acordo com a leitura da imagem completa com a borda branca
			for (int l = 0; l < N; l++) {
				for (int m = 0; m < N; m++) {
					(*windows)[i][j]->imageWindow.at<uchar>(l,m) = imageWhiteBorder.at<uchar>(i*N + l, j*N + m);
				}
			}
			string imgName = "window_";

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

	windows.resize(col/N);
	for (int i = 0; i < col/N; i++){
		windows[i].resize((int)row/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < col/N; i++){
		for (int j = 0; j < row/N;  j++){
			windows[i][j] = new window(N, N, originalImage.type());
			cout << "i: " << i << "; j: " << j << endl;
//			window w(N, N, originalImage.type());
//			cout << "nova window ok" << endl;
////			windows[i][j] = w;
//			windows[i][j].angle = w.angle;
//			cout << "angle" << endl;
//			windows[i][j].frequency = w.frequency;
//			cout << "freq" << endl;
//			windows[i][j].imageWindow = w.imageWindow;
//			cout << "image" << endl;
//			windows[i][j].quality = w.quality;
//			cout << "quality" << endl;
		}
	}
	cout << "matriz foi inicializada" << endl;

	fillWhiteBorderInImage(originalImage, &imageWhiteBorder, N, col - originalImage.cols,
			row - originalImage.rows, originalImage.cols, originalImage.rows);
	cout << "imagem preenchida com borda branca" << endl;


	createWindows(imageWhiteBorder, N, col, row, &windows);
	cout << "janelas criadas" << endl;


	waitKey(0);

	//TODO fazer o delete das windows

	return 0;
}
