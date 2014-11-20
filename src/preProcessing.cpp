//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Fingerprint Identification Algorithm
//============================================================================

#include "preProcessing.hpp"
#include "constants.hpp"
#define GABOR_NOT_APPLICABLE 1000

using namespace cv;
using namespace std;

//lê uma imagem de entrada e altera "image"
void imageRead (Mat *image, int *dpi, string imagePath) {

	//teste
	*dpi = 500;

	//cout << "Quantos DPIs tem sua imagem? "; // prints !!!Hello World!!!
	//cin >> *dpi;

	//cout << "Digite o endereço da sua imagem (Ex: /home/Pictures/image.jpg): "; //get o imagePath
	//cin >> imagePath;

	//Ao carregar a imagem, já se garante que será em tons de cinza
	*image = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
	//*image = imread("/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Verifica se a imagem de entrada é válida
	if(! image->data ){
		//cout <<  "Não foi possível abrir ou encontrar a imagem." << std::endl ;
		return;
	}
	else{
		//namedWindow( "Display original image", WINDOW_AUTOSIZE ); // Create a window to display image
		//imshow( "Display original image", *image ); // Show the image inside it
	}

	//teste
	//cout << "dpi: " << *dpi << endl;

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

	//cout << "y: " << y << endl;
	//cout << "linhas: " << image.rows << endl;
	//cout << "x: " << x << endl;
	//cout << "colunas: " << image.cols << endl;

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

	//namedWindow( "Borda branca", WINDOW_AUTOSIZE ); // Create a window to display image
	//imshow( "Borda branca", *imageWhiteBorder); // Show the image inside it

	/*
	imageWhiteBorderOutputPath.append(outputPath);
	imageWhiteBorderOutputPath.append("imageWhiteBorder.tiff");

	imageOutputPath.append(outputPath);
	imageOutputPath.append("image.tiff");

	imwrite(imageWhiteBorderOutputPath, *imageWhiteBorder);
	imwrite(imageOutputPath, image);
	*/
	return;
}

void equalize(Mat *imageBefore, Mat *imageAfter) {

	equalizeHist(*imageBefore, *imageAfter);

	return;
}

void equalizeWindows(int N, int col, int row, vector< vector <window*> > *windows) {

	for (int j = 0; j < col/N; j++) {
		for (int i = 0; i < row/N; i++) {
			equalizeHist((*windows)[i][j]->getImageWindow(), (*windows)[i][j]->getImageWindow());
			//->get_imageWindow(), (*windows)[i][j]->get_imageWindow());

			//TESTE
			//salva a imagem equalizada
			/*
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
			equalizedImageoutputPath.append(".tif");
			imwrite(equalizedImageoutputPath, (*windows)[i][j]->getImageWindow());
			*/
			//FIM TESTE
		}
	}

	return;
}

//N = param
//int *p
//p= &i
//Altera a matriz com cada um adas janelas, criando uma por uma (a partir de uma imagem de entrada -> imageWhiteBorder)
void createWindows(Mat imageWhiteBorder, int N, int column, int row, vector< vector <window*> > *windows) {
	for (int j = 0; j < column/N; j++) {
		for (int i = 0; i < row/N; i++){
			//preenche cada pixel da janela de acordo com a leitura da imagem completa com a borda branca
			for (int l = 0; l < N; l++) {
				for (int m = 0; m < N; m++) {
					(*windows)[i][j]->getImageWindow().at<uchar>(l,m) = imageWhiteBorder.at<uchar>(i*N + l, j*N + m);
				}
			}
			/*
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

			imwrite(imgName, (*windows)[i][j]->getImageWindow());
			*/
		}
	}
	return;
}

//Retorna as medidas da imagem que serão necessárias para realizar o janelamento
void imageMeasures(Mat image, int dpi, int *N, int *col, int *row) {
	int x, y, extraX, extraY, Nx, Ny;

	y = image.rows;
	x = image.cols;

	//para 500 dpi, janelas de 17 x 17, a proporção é de dpi/N = 29
	//as janelas da última coluna direita e da última linha podem ser um pouco maiores ou menores
	//(*N) = dpi/29;
	//para 500 dpi, janelas de 32 x 32, a proporção é de dpi/N = 16
	//as janelas da última coluna direita e da última linha podem ser um pouco maiores ou menores
	//(*N) = dpi/16;
	(*N) = dpi/16;

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

//Recria a imagem a partir das janelas e exibe em uma janela e a armazena com o nome passado em imageName
//Obs: imageName é concatenado a outputPath
void recreateImage(vector< vector <window*> > windows, int row, int col, int N, String imageName) {
	Mat recreatedImage;
	String recreatedImageOutputPath;

	recreatedImage.create(row, col, windows[0][0]->getImageWindow().type());

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j < col/N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++){
					recreatedImage.at<uchar>(N*i + k, N*j + l) = windows[i][j]->getImageWindow().at<uchar>(k, l);
				}
			}
		}
	}

	recreatedImageOutputPath.append(outputPath);
	recreatedImageOutputPath.append(imageName);
	recreatedImageOutputPath.append(".jpg");
	//imshow( imageName, recreatedImage);
	imwrite(recreatedImageOutputPath, recreatedImage);

	return;
}

void recreateImagePath(vector< vector <window*> > windows, int row, int col, int N, String path) {
	Mat recreatedImage;

	recreatedImage.create(row, col, windows[0][0]->getImageWindow().type());

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j < col/N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++){
					recreatedImage.at<uchar>(N*i + k, N*j + l) = windows[i][j]->getImageWindow().at<uchar>(k, l);
				}
			}
		}
	}
	imwrite(path, recreatedImage);

	return;
}

void thinningIteration(cv::Mat& im, int iter) {
    cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
    return;
}

/**
 * Function for thinning the given binary image
 *
 * @param  im  Binary image with range = 0-255
 */
void thinning(cv::Mat& im) {
    bitwise_not(im, im);
	im /= 255;

    cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
    cv::Mat diff;

    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        cv::absdiff(im, prev, diff);
        im.copyTo(prev);
    }
    while (cv::countNonZero(diff) > 0);

    im *= 255;
    im = 255 - im;

    return;
}

void thinningWindows (vector < vector <window*> > *windows, int row, int col, int N) {

	vector < vector <window*> > aux;
	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
	aux.resize(row/N);
	for (int i = 0; i < row/N; i++){
		aux[i].resize((int)col/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			aux[i][j] = new window(N, N, (*windows)[i][j]->imageWindow.type());
		}
	}

	//CRIA CÓPIA DA IMAGEM DAS JANELAS
	/*for (int i = 0; i < row/N; i++) {
		for (int j = 0; j < col/N; j++) {
			aux[i][j]->imageWindow = (*windows)[i][j]->imageWindow;
		}
	}*/
	for (int i = 0; i < row/N; i++) {
		aux[i][0]->imageWindow = (*windows)[i][0]->imageWindow;
		aux[i][col/N - 1]->imageWindow = (*windows)[i][col/N - 1]->imageWindow;
	}
	for (int j = 0; j < col/N; j++) {
		aux[0][j]->imageWindow = (*windows)[0][j]->imageWindow;
		aux[row/N - 1][j]->imageWindow = (*windows)[row/N - 1][j]->imageWindow;
	}

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j <  col/N; j++) {
			if (i == 0 || i == row/N - 1 || j == 0 || j == col/N - 1) {
				thinning(aux[i][j]->imageWindow);
			}
			else {
				Mat imageWithBorder;
				getWindowBorder (&imageWithBorder, N, *windows, i, j);
				thinning(imageWithBorder);
				removeWindowBorder(&(aux[i][j]->imageWindow), imageWithBorder, N + 4, N);
			}
		}
	}

	recreateImage(aux, row, col, N, "imagem aux");

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j <  col/N; j++) {
			(*windows)[i][j]->imageWindow = aux[i][j]->imageWindow;

			/*
			String output;
			output.append(outputPath);
			output.append("thinnedWindow_");
			ostringstream iString;
			ostringstream jString;
			iString << i;
			jString << j;
			output.append(iString.str());
			output.append("_");
			output.append(jString.str());
			output.append(".jpg");
			imwrite(output, (*windows)[i][j]->getImageWindow());
			*/
		}
	}
	/*
	for (int i = 1; i < row/N - 1; i++) {
		for (int j = 1; j <  col/N - 1; j++) {
			Mat imageWithBorder;
			getWindowBorder (&imageWithBorder, N, *windows, i, j);
			thinning(imageWithBorder);
			removeWindowBorder(&((*windows)[i][j]->imageWindow), imageWithBorder, N + 4, N);
		}
	}*/

	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			delete aux[i][j];
		}
	}

	return;
}

void binarization (vector < vector <window*> > *windows, int row, int col, int N) {
	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j <  col/N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					if ((*windows)[i][j]->getImageWindow().at<uchar>(k,l) <= 127) {
						(*windows)[i][j]->getImageWindow().at<uchar>(k,l) = 0;
					}
					else {
						(*windows)[i][j]->getImageWindow().at<uchar>(k,l) = 255;
					}
				}
			}
		}
	}
	return;
}

void imageBinarization (Mat *image) {
	for (int i = 0; i < image->rows; i ++) {
		for (int j = 0; j < image->cols; j++) {
			if (image->at<uchar>(i, j) <= 127) {
				image->at<uchar>(i, j) = 0;
			}
			else {
				image->at<uchar>(i, j) = 255;
			}
		}
	}
	return;
}

void frequencyMap (vector < vector <window*> > *windows, int row, int col, int N){
	float lambda=0;
	Mat I;
	Mat FFT_Result;
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			I = (*windows)[i][j]->getImageWindow();
			FFT_Result=do_FFT(I);
			get_lambda(FFT_Result,lambda);
			(*windows)[i][j]->setFrequency((double)lambda);
			//cout << "Lambda:" << endl;
			//cout << lambda << endl;
		}
	}
	return;
}

void tempFrequencyMap (vector < vector <window*> > windows, int row, int col, int N, Mat *temp){
	Mat I;
	Mat FFT_Result;
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			I = windows[i][j]->getImageWindow();
			FFT_Result=do_FFT(I);
			//get_lambda(FFT_Result,lambda);
			//(*windows)[i][j]->setFrequency((double)lambda);
		}
	}
	return;
}

//Seta o ângulo de orientação de cada uma das janelas da imagem
//**** O ângulo setado é em RADIANOS
void orientationMapOLD (vector < vector <window*> > *windows, int row, int col, int N){

    Mat kernelX;
    kernelX.create(3, 3, CV_8SC1);
    kernelX.at<uchar>(0,0) = -1;
    kernelX.at<uchar>(0,1) = 0;
    kernelX.at<uchar>(0,2) = 1;
    kernelX.at<uchar>(1,0) = -2;
    kernelX.at<uchar>(1,1) = 0;
    kernelX.at<uchar>(1,2) = 2;
    kernelX.at<uchar>(2,0) = -1;
    kernelX.at<uchar>(2,1) = 0;
    kernelX.at<uchar>(2,2) = 1;

    Mat kernelY;
    kernelY.create(3, 3, CV_8SC1);
    kernelY.at<uchar>(0,0) = 1;
    kernelY.at<uchar>(0,1) = 2;
    kernelY.at<uchar>(0,2) = 1;
    kernelY.at<uchar>(1,0) = 0;
    kernelY.at<uchar>(1,1) = 0;
    kernelY.at<uchar>(1,2) = 0;
    kernelY.at<uchar>(2,0) = -1;
    kernelY.at<uchar>(2,1) = -2;
    kernelY.at<uchar>(2,2) = -1;

	for (int i = 0; i < row/N; i++) {

		for (int j = 0; j <  col/N; j++) {
			//GRADIENTE GX
			Mat Gx;
			filter2D((*windows)[i][j]->getImageWindow()/255, Gx, CV_16SC1, kernelX);

			//GRADIENTE GY
			Mat Gy;
			filter2D((*windows)[i][j]->getImageWindow()/255, Gy, CV_16SC1, kernelY);

			int Vx, Vy;
			Vx = 0;
			Vy = 0;

			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					Vx = Vx + 2 * Gx.at<signed short>(k, l) * Gy.at<signed short>(k, l);
					Vy = Vy + Gx.at<signed short>(k, l) * Gx.at<signed short>(k, l) - Gy.at<signed short>(k, l) * Gy.at<signed short>(k, l);
				}
			}

			//Grava o ângulo da janela na variável "angle", atributo da classe window
			//obs: precisa somar 90º, porque o ângulo para o gabor é ortogonal ao obtido pelo sobel
			if (Vy == 0) {	//a tangente de um valor dividido por zero é 90º = PI/2
				if (Vx == 0)(*windows)[i][j]->setAngle(GABOR_NOT_APPLICABLE);
				else if ( Vx > 0) (*windows)[i][j]->setAngle( (double)0.5 * (double)M_PI * 0.5);// - (double)M_PI * 0.5 );
				else (*windows)[i][j]->setAngle( (double)(-0.5) * (double)M_PI * 0.5);
			}
			else {
				double k;
				double angle;
				angle = (double)0.5 * atan((double) Vx / Vy);
				if ((angle < 0 && Vx < 0) || (angle >= 0 && Vx > 0)) k = 0.5;
				else if (angle < 0  && Vx >= 0) k = 0;
				else k = 0;

				(*windows)[i][j]->setAngle( angle + (double)(k * M_PI));// - (double)M_PI * 0.5);
			}
			if ((*windows)[i][j]->getAngle() != GABOR_NOT_APPLICABLE) {
				//cout << "janela (i: " << i << ", j: " << j << ") ";
				//cout << "ângulo: " << ((double)(180 / M_PI) * (*windows)[i][j]->getAngle()) << endl;
			}
		}
		//cout << endl;
	}
	return;



	//**************** CÓDIGO ANTIGO ***********************//

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j <  col/N; j++) {
			Mat Gx, Gy;
			//No sobel, parâmetros de entrada:
			//1º: imagem de entrada
			//2º: imagem de saída
			//3º: ddepth: profundidade da imagem (=-1 quer dizer que é equivalente à profundidade da imagem de entrada)
			//4º: dx: se é ordem de X =1 , se não =0
			//5º: dy: se é ordem de Y =1 , se não =0
			//6º: dimensão da matriz de sobel
			Sobel((*windows)[i][j]->getImageWindow()/255, Gx, -1, 1, 0, -1, 1, 0, BORDER_DEFAULT);
			Sobel((*windows)[i][j]->getImageWindow()/255, Gy, -1, 0, 1, -1, 1, 0, BORDER_DEFAULT);

			int Vx, Vy;
			Vx = 0;
			Vy = 0;
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					Vx = Vx + 2 * Gx.at<uchar>(k, l) * Gy.at<uchar>(k, l);//[k][l] * Gy[k][l];
					Vy = Vy + Gx.at<uchar>(k, l) * Gx.at<uchar>(k, l) - Gy.at<uchar>(k, l) * Gy.at<uchar>(k, l);
				}
			}

			//Grava o ângulo da janela na variável "angle", atributo da classe window
			//obs: precisa somar 90º, porque o ângulo para o gabor é ortogonal ao obtido pelo sobel
			if (Vy == 0) {	//a tangente de um valor dividido por zero é 90º = PI/2
				(*windows)[i][j]->setAngle( 0 );
			}
			else {
				(*windows)[i][j]->setAngle( (double)0.5 * atan((double) Vx / Vy) - (double)M_PI * 0.5);
			}

			//cout << "Ângulo janela (em graus) " << i << ", " << j << ": " << ((double)(180 / M_PI) * (*windows)[i][j]->getAngle())+90;// << endl;
			//cout << "; Ângulo janela (em radianos) " << i << ", " << j << ": " << (*windows)[i][j]->getAngle() + (double)M_PI * 0.5 << endl;
		}
	}
	return;
}

//Adiciona 2 pixels de cada lado da imagem (com a imagem das outras bordas, para garantir que o Gabor não terá problema nas bordas
//neste método, as janelas das bordas não devem ser incluídas
//Mat *imageWithBorder: imagem que será criada com a adição das bordas à uma imagem de uma janela
//int N: dimensão da janela original
//vector < vector <window*> > windows: estrutura com todas as janelas para serem acessadas
//int i, int j: índices do vetor window para saber qual janela será usada como base
void getWindowBorder (Mat *imageWithBorder, int N, vector < vector <window*> > windows, int i, int j) {

	imageWithBorder->create(N + 4, N + 4, windows[i][j]->getImageWindow().type());

	//PREENCHE BORDA SUPERIOR ESQUERDA
	//Para preencher esta borda, precisa acessar a imagem da janela (i-1, j-1)
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i - 1][j - 1]->getImageWindow().at<uchar>((N - 2 + row), (N - 2 + col));
		}
	}

	//PREENCHE BORDA INFERIOR ESQUERDA
	//Para preencher esta borda, precisa acessar a imagem da janela (i+1, j-1)
	for (int row = N + 2; row < N + 4; row++) {
		for (int col = 0; col < 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i + 1][j - 1]->getImageWindow().at<uchar>((row - (N + 2)), (col + (N - 2)));
		}
	}

	//PREENCHE BORDA SUPERIOR DIREITA
	//Para preencher esta borda, precisa acessar a imagem da janela (i-1, j+1)
	for (int row = 0 ; row < 2; row++) {
		for (int col = N + 2; col < N + 4; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i - 1][j + 1]->getImageWindow().at<uchar>((N - 2 + row), (col - (N + 2)));
		}
	}

	//PREENCHE BORDA INFERIOR DIREITA
	//Para preencher esta borda, precisa acessar a imagem da janela (i+1, j+1)
	for (int row = N + 2; row < N + 4; row++) {
		for (int col = N + 2; col < N + 4; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i + 1][j + 1]->getImageWindow().at<uchar>((row - (N + 2)), (col - (N + 2)));
		}
	}

	//PREENCHE TOPO
	//Para preencher esta borda, precisa acessar a imagem da janela (i-1, j)
	for (int row  = 0; row < 2; row++) {
		for (int col = 2; col < N + 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i - 1][j]->getImageWindow().at<uchar>(row + (N - 2), col - 2);
		}
	}

	//PREENCHE BASE (BOTTOM)
	//Para preencher esta borda, precisa acessar a imagem da janela (i+1, j)
	for (int row  = N + 2; row < N + 4; row++) {
		for (int col = 2; col < N + 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i + 1][j]->getImageWindow().at<uchar>(row - (N - 2), col - 2);
		}
	}

	//PREENCHE LATERAL ESQUERDA
	//Para preencher esta borda, precisa acessar a imagem da janela (i, j - 1)
	for (int row  = 2; row < N + 2; row++) {
		for (int col = 0; col < 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i][j - 1]->getImageWindow().at<uchar>(row -  2, col + (N - 2));
		}
	}

	//PREENCHE LATERAL DIREITA
	//Para preencher esta borda, precisa acessar a imagem da janela (i, j - 1)
	for (int row = 2; row < N + 2; row++) {
		for (int col = 0; col < 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i][j - 1]->getImageWindow().at<uchar>(row -  2, col + (N - 2));
		}
	}

	//PREENCHE CENTRO
	//Para preencher esta borda, precisa acessar a imagem da janela (i, j)
	for (int row = 2; row < N + 2; row++) {
		for (int col = 2; col < N + 2; col++) {
			imageWithBorder->at<uchar>(row, col) = windows[i][j]->getImageWindow().at<uchar>(row -  2, col - 2);
		}
	}

	return;
}

//Remove a borda utilizada para uso do Gabor
//int originalSize: tamanho da imagem com borda
//int newSize: tamanho da imagem sem bordar
void removeWindowBorder( Mat *imageWithoutBorder, Mat imageWithBorder, int originalSize, int newSize) {
	if (newSize > originalSize) {
		//cout << "Erro ao tentar remover borda da imagem: imagem original é menor que o tamanho da imagem sem borda." << endl;
	}
	for (int i = 0; i < newSize; i++){
		for (int j = 0; j < newSize; j++) {
			imageWithoutBorder->at<uchar>(i, j) = imageWithBorder.at<uchar>((i + (originalSize - newSize)/2), (j + (originalSize - newSize)/2));
		}
	}
	return;
}

void gaborFilter (vector < vector <window*> > *windows, int row, int col, int N) {

	int w = 10; // frequencia a ser utilizada no Gabor
	//TEMP

	vector < vector <window*> > windowsTemp;
	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
	windowsTemp.resize(row/N);
	for (int i = 0; i < row/N; i++){
		windowsTemp[i].resize((int)col/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windowsTemp[i][j] = new window(N, N, (*windows)[0][0]->getImageWindow().type());
			(*windows)[i][j]->getImageWindow().copyTo(windowsTemp[i][j]->imageWindow);
			windowsTemp[i][j]->setAngle((*windows)[i][j]->getAngle());
			//windowsTemp[i][j]->setImageWindow((*windows)[i][j]->getImageWindow());
		}
	}

	vector < vector <window*> > windowsTemp2;
	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
	windowsTemp2.resize(row/N);
	for (int i = 0; i < row/N; i++){
		windowsTemp2[i].resize((int)col/N);
	}

	//inicializando a matriz com as janelas (usando a classe window)
	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windowsTemp2[i][j] = new window(N, N, (*windows)[0][0]->getImageWindow().type());
			(*windows)[i][j]->getImageWindow().copyTo(windowsTemp2[i][j]->imageWindow);
			windowsTemp2[i][j]->setAngle((*windows)[i][j]->getAngle());
			//windowsTemp[i][j]->setImageWindow((*windows)[i][j]->getImageWindow());
		}
	}


//	vector < vector <window*> > windowsFinal;
//	//Dimensiona a matriz com as janelas (i = linhas, j = colunas)
//	windowsFinal.resize(row/N);
//	for (int i = 0; i < row/N; i++){
//		windowsFinal[i].resize((int)col/N);
//	}
//
//	//inicializando a matriz com as janelas (usando a classe window)
//	for (int i = 0; i < row/N; i++){
//		for (int j = 0; j < col/N;  j++){
//			windowsFinal[i][j] = new window(N, N, (*windows)[0][0]->getImageWindow().type());
//			(*windows)[i][j]->getImageWindow().copyTo(windowsFinal[i][j]->imageWindow);
//			windowsFinal[i][j]->setAngle((*windows)[i][j]->getAngle());
//		}
//	}

	for (int i = 1; i < row/N - 1; i++) {
			for (int j = 1; j <  col/N - 1; j++) {
				if ( windowsTemp[i][j]->getAngle() != GABOR_NOT_APPLICABLE) {
					Mat imageWithBorder;
					getWindowBorder (&imageWithBorder, N, windowsTemp, i, j);

					Mat gaborKernel;
					gaborKernel = getGaborKernel( Size(N + 4,N + 4) , 4, windowsTemp[i][j]->getAngle()+ M_PI/2, w, 1, 0, CV_32F );

					Mat gaborKernel2;
					gaborKernel2 = getGaborKernel( Size(N + 4,N + 4) , 4, windowsTemp2[i][j]->getAngle(), w, 1, 0, CV_32F );

					Mat imageAux;
					Mat imageAux2;
					imageAux.create(N+4, N+4, imageWithBorder.type());
					imageAux2.create(N+4, N+4, imageWithBorder.type());
					filter2D(imageWithBorder, imageAux, -1, gaborKernel);
					filter2D(imageWithBorder, imageAux2, -1, gaborKernel2);

					removeWindowBorder( &windowsTemp[i][j]->imageWindow, imageAux, N + 4, N);
					removeWindowBorder( &windowsTemp2[i][j]->imageWindow, imageAux2, N + 4, N);

					float media = mean(windowsTemp[i][j]->imageWindow, windowsTemp[i][j]->imageWindow)[0];
					float media2 = mean(windowsTemp2[i][j]->imageWindow, windowsTemp2[i][j]->imageWindow)[0];

					if (media > media2) {
//						windowsTemp[i][j]->imageWindow.copyTo(windowsFinal[i][j]->imageWindow);
						windowsTemp[i][j]->imageWindow.copyTo((*windows)[i][j]->imageWindow);
					}
					else {
//						windowsTemp2[i][j]->imageWindow.copyTo(windowsFinal[i][j]->imageWindow);
						windowsTemp2[i][j]->imageWindow.copyTo((*windows)[i][j]->imageWindow);
					}
				}
			}
		}
//
//		Mat fullImage;
//		fullImage.create(row, col, CV_8UC1);
//		groupImageWindows(&fullImage, windowsFinal, row, col, N);
//
//		string nome;
//		nome.append("Imagem Final depois do Gabor ");
//		nome.append(static_cast<ostringstream*>( &(ostringstream() << w) )->str());
//		imshow (nome, fullImage);

		Mat tempImage;
		tempImage.create(row, col, CV_8UC1);
		groupImageWindows(&tempImage, windowsTemp, row, col, N);

		string sqlstr;
		sqlstr.append("teste ");
		sqlstr.append(static_cast<ostringstream*>( &(ostringstream() << w) )->str());
		//imshow (sqlstr, tempImage);

		Mat tempImage2;
		tempImage2.create(row, col, CV_8UC1);
		groupImageWindows(&tempImage2, windowsTemp2, row, col, N);

		string sqlstr2;
		sqlstr2.append("teste2 ");
		sqlstr2.append(static_cast<ostringstream*>( &(ostringstream() << w) )->str());
		//imshow (sqlstr2, tempImage2);


	//PERCORRE A IMAGEM COMBINADA DE DOIS GABORS PARA CORRIGIR JANELAS QUE NÃO ESTÃO ADEQUADAS
	//precisa percorrer as janelas deixando duas de sobra para olhar os vizinhos
//	for (int i = 2; i < row/N - 2; i++) {
//		for (int j = 2; j <  col/N - 2; j++) {
//			if (windowsFinal[i][j]->getAngle() != GABOR_NOT_APPLICABLE) {
//				float mediaVizinhas = 0;
//				float media = mean(windowsFinal[i][j]->getImageWindow(), windowsFinal[i][j]->getImageWindow())[0];
//				cout << "media " << media << endl;
//
//				int count = 0;
//				for (int k = i - 1; k <= i +1; k +=2) {
//					for (int l = j - 1; l <= j +1; l +=2) {
//						if (windowsFinal[k][l]->getAngle() != GABOR_NOT_APPLICABLE) {
//							count ++;
//							mediaVizinhas = mediaVizinhas + mean(windowsFinal[k][l]->getImageWindow(), windowsFinal[k][l]->getImageWindow())[0];
//						}
//					}
//				}
//				if ( count != 0) {
//					mediaVizinhas = mediaVizinhas/count;
//
//					if (abs(media - mediaVizinhas) > 5) {
//						cout << "mudou a imagem da janela" << endl;
//
//						float media1 = mean(windowsTemp[i][j]->imageWindow, windowsTemp[i][j]->imageWindow)[0];
//						float media2 = mean(windowsTemp2[i][j]->imageWindow, windowsTemp2[i][j]->imageWindow)[0];
//
//						if (media1 > media2) {
//							windowsTemp2[i][j]->imageWindow.copyTo(windowsFinal[i][j]->imageWindow);
//						}
//						else {
//							windowsTemp[i][j]->imageWindow.copyTo(windowsFinal[i][j]->imageWindow);//.copyTo(&windowsTemp[i][j]->imageWindow);
//						}
//
//					}
//				}

	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windowsTemp[i][j];
		}
	}

	for (int i = 0; i < row/N; i++){
		for (int j = 0; j < col/N;  j++){
			windowsTemp2[i][j];
		}
	}

	return;
}

Mat do_FFT(Mat padded)
{
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);  // Add to the expanded another plane with zeros

	dft(complexI, complexI); // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);    // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);         // planes[0] = magnitude
	Mat magI = planes[0];

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                      // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//magI.at<float>(QUAD/2,QUAD/2)=0;

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).

	return magI;
}


void get_lambda(Mat& in, float& lambda)
{
	const int npontos=4;
	const int meio=in.rows/2;

	in.at<float>(in.rows/2,in.cols/2)=0;

	vector<Point3f> pontos;
	for (int i=0;i<npontos;i++)
		pontos.push_back(Point3f(0,0,-1));

	for (int i=0;i<in.rows;i++)
		for (int j=0;j<in.rows;j++)
		{
			if (in.at<float>(i,j) >= pontos[3].z)
			{
				pontos.push_back(Point3f(i,j,in.at<float>(i,j)));
				std::sort (pontos.begin(), pontos.end(), comparar);
				pontos.erase(pontos.begin()); //apaga o primeiro elemento, o menor
			}
		}

	float x2=0;
	float xy=0;
	for (int i=0; i<npontos; i++)
	{
		in.at<float>(pontos[i].x,pontos[i].y)=1;
		x2+=(pontos[i].x-meio)*(pontos[i].x-meio);
		xy+=(pontos[i].x-meio)*(pontos[i].y-meio);
	}
	in.at<float>(in.rows/2,in.cols/2)=1;

	vector<float> dist;
	for (int i=0;i<npontos;i++)
		dist.push_back((pontos[i].x-meio)*(pontos[i].x-meio)+(pontos[i].y-meio)*(pontos[i].y-meio));
	std::sort(dist.begin(),dist.end());

	lambda=dist[0];
}

bool comparar (Point3f i,Point3f j) { return (i.z<j.z); }

void groupImageWindows(Mat *imageNew, vector < vector <window*> > windows, int row, int col, int N) {
//	//cria cópia da imagem de cada janela
//	for (int i = 0; i < row/N; i++) {
////		for (int j = 0; j < col/N; j++) {
////			Mat temp(windows[i][j]->imageWindow);
////		}
////	}
//	for (int i = 0; i < row/N; i++) {
//		for (int j = 0; j < col/N; j++) {
//			Mat temp(windows[i][j]->imageWindow);
//			for (int k = 0; k < N; k++) {
//				for (int l = 0; l < N; l++){
//					imageNew->at<uchar>(N*i + k, N*j + l) = temp.at<uchar>(k, l);
//				}
//			}
//		}
//	}

	for (int i = 0; i < row/N; i++) {
		for (int j = 0; j < col/N; j++) {
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++){
					imageNew->at<uchar>(N*i + k, N*j + l) = windows[i][j]->getImageWindow().at<uchar>(k, l);
				}
			}
		}
	}
	return;
}


Mat doFFT(Mat padded)
{
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);  // Add to the expanded another plane with zeros

	dft(complexI, complexI); // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);    // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);         // planes[0] = magnitude
	Mat magI = planes[0];

	//magI += Scalar::all(1);                    // switch to logarithmic scale
	//log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                      // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//magI.at<float>(QUAD/2,QUAD/2)=0;

	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).

	return magI;
}


void get_angle_and_lambda(Mat& in, float& angle, float& lambda)
{
	const int npontos=4;
	const int meio=in.rows/2;

	in.at<float>(in.rows/2,in.cols/2)=0;

	vector<Point3f> pontos;
	for (int i=0;i<npontos;i++)
		pontos.push_back(Point3f(0,0,-1));

	for (int i=0;i<in.rows;i++)
		for (int j=0;j<in.rows;j++)
		{
			if (in.at<float>(i,j) >= pontos[3].z)
			{
				pontos.push_back(Point3f(i,j,in.at<float>(i,j)));
				std::sort (pontos.begin(), pontos.end(), comparar);
				pontos.erase(pontos.begin()); //apaga o primeiro elemento, o menor
			}
		}

	float x2=0;
	float xy=0;
	for (int i=0; i<npontos; i++)
	{
		in.at<float>(pontos[i].x,pontos[i].y)=1;
		x2+=(pontos[i].x-meio)*(pontos[i].x-meio);
		xy+=(pontos[i].x-meio)*(pontos[i].y-meio);
	}
	in.at<float>(in.rows/2,in.cols/2)=1;

	angle=atan2(xy,x2);

	//Vamos achar lambda agora
	vector<float> dist;
	for (int i=0;i<npontos;i++)
		dist.push_back((pontos[i].x-meio)*(pontos[i].x-meio)+(pontos[i].y-meio)*(pontos[i].y-meio));
	std::sort(dist.begin(),dist.end());

	//lambda=dist[0];
	lambda=10;
	//cout << "L:" << lambda << endl;
}


void applyGabor(Mat& in, Mat& out, float theta, float lambda)
{
	//imshow("TESTE",in);
	//waitKey(0);

	Mat gaborKernel = getGaborKernel( cv::Size(17,17) , 4, -theta+CV_PI/2, lambda, 1, 0, CV_32F );
	filter2D(in,out,-1,gaborKernel);
}

void rotate(cv::Mat& src, double angle, cv::Mat& dst)
{
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);

    cv::warpAffine(src, dst, r, cv::Size(len, len));
}

void gaborNET(Mat I, int row, int col, int N, Mat *finalImage) {

    Mat kernelX;
    kernelX.create(3, 3, CV_8SC1);
    kernelX.at<uchar>(0,0) = -1;
    kernelX.at<uchar>(0,1) = 0;
    kernelX.at<uchar>(0,2) = 1;
    kernelX.at<uchar>(1,0) = -2;
    kernelX.at<uchar>(1,1) = 0;
    kernelX.at<uchar>(1,2) = 2;
    kernelX.at<uchar>(2,0) = -1;
    kernelX.at<uchar>(2,1) = 0;
    kernelX.at<uchar>(2,2) = 1;

    Mat kernelY;
    kernelY.create(3, 3, CV_8SC1);
    kernelY.at<uchar>(0,0) = 1;
    kernelY.at<uchar>(0,1) = 2;
    kernelY.at<uchar>(0,2) = 1;
    kernelY.at<uchar>(1,0) = 0;
    kernelY.at<uchar>(1,1) = 0;
    kernelY.at<uchar>(1,2) = 0;
    kernelY.at<uchar>(2,0) = -1;
    kernelY.at<uchar>(2,1) = -2;
    kernelY.at<uchar>(2,2) = -1;
//	cout << "******** KernelY ********" << endl;
//	cout << kernelY << endl;

	Mat FFT_Result;
	Mat Final_Result = Mat::zeros(I.rows,I.cols,CV_8U);
	Mat FFT_Final_Result = Mat::zeros(I.rows,I.cols,CV_32F);
	Mat dst_roi;
	Mat ttt;

	for (int i = 0; i < I.rows - N; i = i + N) {
		for (int j = 0; j < I.cols - N; j = j + N) {

			float angulo=0,lambda=0;

			FFT_Result=doFFT(I(Rect(j,i,N,N)));
			get_angle_and_lambda(FFT_Result,angulo,lambda);
			dst_roi = FFT_Final_Result(Rect(j, i, N, N));
			FFT_Result.copyTo(dst_roi);
			//applyGabor(I,ttt,angulo,lambda);
			applyGabor(I, ttt, getAngle (kernelX, kernelY, FFT_Result, N), 10);

			Mat temp=Mat::zeros(N,N,CV_8U);
			Mat temp2=Mat::zeros(N,N,CV_8U);
			line(temp,Point(0,N/2),Point(N,N/2),Scalar(255,255,255),1);
			rotate(temp,angulo*180/3.141592653589,temp2);

			dst_roi = Final_Result(Rect(j, i, N, N));
			ttt(Rect(j,i,N,N)).copyTo(dst_roi);
		}
	}

	ttt.copyTo(*finalImage);
	return;
}

float getAngle (Mat kernelX, Mat kernelY, Mat image, int N){
	float angle = GABOR_NOT_APPLICABLE;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <  N; j++) {
			//GRADIENTE GX
			Mat Gx;
			filter2D(image/255, Gx, CV_16SC1, kernelX);

			//GRADIENTE GY
			Mat Gy;
			filter2D(image/255, Gy, CV_16SC1, kernelY);

			int Vx, Vy;
			Vx = 0;
			Vy = 0;

			int flag = 0;
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					if (Gx.at<signed short>(k, l) != 0) flag = 1;
					Vx = Vx + 2 * Gx.at<signed short>(k, l) * Gy.at<signed short>(k, l);
					Vy = Vy + Gx.at<signed short>(k, l) * Gx.at<signed short>(k, l) - Gy.at<signed short>(k, l) * Gy.at<signed short>(k, l);
				}
			}

			if ( flag == 1) {
				//Grava o ângulo da janela na variável "angle", atributo da classe window
				//obs: precisa somar 90º, porque o ângulo para o gabor é ortogonal ao obtido pelo sobel
				if (Vy == 0) {	//a tangente de um valor dividido por zero é 90º = PI/2
					angle = (float)0.5 * (float)(M_PI * 0.5);// - (double)M_PI * 0.5 );
				}
				else {
					angle = (float)0.5 * atan((float) (Vx / Vy));// - (double)M_PI * 0.5);
				}
			}

			if (flag == 1) {
				//cout << "Ângulo janela (em graus) : " << ((float)(180 / M_PI)) * angle;
				//cout << "; Ângulo janela (em radianos) : " << angle << endl;
			}

		}
	}
	return angle;
}

//A diferença entre este mapa de orientação e o da função orientationMapOLD é que este selecionada uma janela
//2N x 2N para o cálculo do Gabor, enquanto a função orientationMapOLD seleciona a própria janela N x N
void orientationMap (vector < vector <window*> > *windows, int row, int col, int N){

	Mat fullFPImage;
	fullFPImage.create(row, col, CV_8UC1);
	groupImageWindows(&fullFPImage, *windows, row, col, N);

//	Mat kernelX;
//    kernelX.create(3, 3, CV_8SC1);
//    kernelX.at<uchar>(0,0) = -1;
//    kernelX.at<uchar>(0,1) = 0;
//    kernelX.at<uchar>(0,2) = 1;
//    kernelX.at<uchar>(1,0) = -2;
//    kernelX.at<uchar>(1,1) = 0;
//    kernelX.at<uchar>(1,2) = 2;
//    kernelX.at<uchar>(2,0) = -1;
//    kernelX.at<uchar>(2,1) = 0;
//    kernelX.at<uchar>(2,2) = 1;
//
//    Mat kernelY;
//    kernelY.create(3, 3, CV_8SC1);
//    kernelY.at<uchar>(0,0) = 1;
//    kernelY.at<uchar>(0,1) = 2;
//    kernelY.at<uchar>(0,2) = 1;
//    kernelY.at<uchar>(1,0) = 0;
//    kernelY.at<uchar>(1,1) = 0;
//    kernelY.at<uchar>(1,2) = 0;
//    kernelY.at<uchar>(2,0) = -1;
//    kernelY.at<uchar>(2,1) = -2;
//    kernelY.at<uchar>(2,2) = -1;

	Mat kernelX;
    kernelX.create(5, 5, CV_8SC1);

    kernelX.at<uchar>(0,0) = -2;
    kernelX.at<uchar>(0,1) = -1;
    kernelX.at<uchar>(0,2) = 0;
    kernelX.at<uchar>(0,3) = 1;
    kernelX.at<uchar>(0,4) = 2;

    kernelX.at<uchar>(1,0) = -2;
    kernelX.at<uchar>(1,1) = -4;
    kernelX.at<uchar>(1,2) = 0;
    kernelX.at<uchar>(1,3) = 4;
    kernelX.at<uchar>(1,4) = 2;

    kernelX.at<uchar>(2,0) = -2;
	kernelX.at<uchar>(2,1) = -4;
	kernelX.at<uchar>(2,2) = 0;
	kernelX.at<uchar>(2,3) = 4;
	kernelX.at<uchar>(2,4) = 2;

	kernelX.at<uchar>(3,0) = -2;
	kernelX.at<uchar>(3,1) = -4;
	kernelX.at<uchar>(3,2) = 0;
	kernelX.at<uchar>(3,3) = 4;
	kernelX.at<uchar>(3,4) = 2;

    kernelX.at<uchar>(4,0) = -2;
    kernelX.at<uchar>(4,1) = -1;
    kernelX.at<uchar>(4,2) = 0;
    kernelX.at<uchar>(4,3) = 1;
    kernelX.at<uchar>(4,4) = 2;

    Mat kernelY;
    kernelY.create(5, 5, CV_8SC1);

    kernelY.at<uchar>(0,0) = -2;
    kernelY.at<uchar>(0,1) = -2;
    kernelY.at<uchar>(0,2) = -2;
    kernelY.at<uchar>(0,3) = -2;
    kernelY.at<uchar>(0,4) = -2;

    kernelY.at<uchar>(1,0) = -1;
    kernelY.at<uchar>(1,1) = -4;
    kernelY.at<uchar>(1,2) = -4;
    kernelY.at<uchar>(1,3) = -4;
    kernelY.at<uchar>(1,4) = -1;

    kernelY.at<uchar>(2,0) = 0;
    kernelY.at<uchar>(2,1) = 0;
    kernelY.at<uchar>(2,2) = 0;
    kernelY.at<uchar>(2,3) = 0;
    kernelY.at<uchar>(2,4) = 0;

    kernelY.at<uchar>(3,0) = 1;
    kernelY.at<uchar>(3,1) = 4;
    kernelY.at<uchar>(3,2) = 4;
    kernelY.at<uchar>(3,3) = 4;
    kernelY.at<uchar>(3,4) = 1;

    kernelY.at<uchar>(4,0) = 2;
    kernelY.at<uchar>(4,1) = 2;
    kernelY.at<uchar>(4,2) = 2;
    kernelY.at<uchar>(4,3) = 2;
    kernelY.at<uchar>(4,4) = 2;

    //não percorre as bordas, porque elas já serão utilizadas no cálculo do ângulo
    //Se a janela é N x N, o Sobel fará o cálculo em uma imagem 2N x 2N
	for (int i = N; i < row - N; i = i + N) {
		for (int j = N; j <  col - N; j = j + N) {
			//GRADIENTE GX
			Mat Gx;
			filter2D(fullFPImage(Rect(j - N/2, i - N/2, 2*N, 2*N))/255, Gx, CV_16SC1, kernelX);
//			filter2D(fullFPImage(Rect(j - N, i - N, 2*N, 2*N))/255, Gx, CV_16SC1, kernelX);
			//filter2D((*windows)[i][j]->getImageWindow()/255, Gx, CV_16SC1, kernelX);

			//GRADIENTE GY
			Mat Gy;
			filter2D(fullFPImage(Rect(j - N/2, i - N/2, 2*N, 2*N))/255, Gy, CV_16SC1, kernelY);
//			filter2D(fullFPImage(Rect(j - N, i - N, 2*N, 2*N))/255, Gy, CV_16SC1, kernelY);
			//filter2D((*windows)[i][j]->getImageWindow()/255, Gy, CV_16SC1, kernelY);

			int Vx, Vy;
			Vx = 0;
			Vy = 0;

			for (int k = 0; k < 2*N; k++) {
				for (int l = 0; l < 2*N; l++) {
					Vx = Vx + 2 * Gx.at<signed short>(k, l) * Gy.at<signed short>(k, l);
					Vy = Vy + Gx.at<signed short>(k, l) * Gx.at<signed short>(k, l) - Gy.at<signed short>(k, l) * Gy.at<signed short>(k, l);
				}
			}

			if (abs(Vx) < 10000 || abs(Vy) < 10000) (*windows)[(int)i/N][(int)j/N]->setAngle(GABOR_NOT_APPLICABLE);
			if ((Vy > -10 && Vy < 10) || abs(Vx) > abs(Vy)*100) {	//a tangente de um valor dividido por zero é 90º = PI/2
				if (Vx == 0) {
					(*windows)[(int)i/N][(int)j/N]->setAngle(GABOR_NOT_APPLICABLE);
				}
				else if ( Vx > 0) {
					(*windows)[(int)i/N][(int)j/N]->setAngle( (-0.5) * M_PI * 0.5);// - (double)M_PI * 0.5 );
				}
				else {
					(*windows)[(int)i/N][(int)j/N]->setAngle( (0.5) * M_PI * 0.5);
				}
			}
			else {
				double k = 0;
				if (Vx == 0 && Vy > 0) {
					k = 0.5;
				}
				double angle;
				angle = (double)0.5 * atan((double) Vx / Vy) + (double) (k * M_PI);
				(*windows)[(int)i/N][(int)j/N]->setAngle(angle);// - (double)M_PI * 0.5);
			}
		}
		//cout << endl;
	}
	return;
}
