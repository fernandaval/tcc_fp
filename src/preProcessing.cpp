//============================================================================
// Name        : TCC.cpp
// Author      : Fernanda Baumgarten Ribeiro do Val and Priscila Ribeiro Marcelino
// Version     :
// Copyright   : This system may not be used commercialy without the authors permission
// Description : Fingerprint Identification Algorithm
//============================================================================

#include "preProcessing.hpp"


using namespace cv;
using namespace std;


//lê uma imagem de entrada e altera "image"
void imageRead (Mat *image, int *dpi, string imagePath) {

	//teste
	*dpi = 500;
	//imagePath = "/home/fernanda/Documents/tcc/BDs_imagens_de_digitais/2004/DB1/101_1.tif";
	imagePath = "/home/priscila/BDs_imagens_de_digitais/2004/DB1/101_1.tif";
	//imagePath = "/home/priscila/teste.jpg";
	//imagePath = "/home/priscila/Rel_4.2.0/mindtct/bin/101_1.jpg";

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
	imshow( imageName, recreatedImage);
	imwrite(recreatedImageOutputPath, recreatedImage);

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
void orientationMap (vector < vector <window*> > *windows, int row, int col, int N){
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
			Sobel((*windows)[i][j]->getImageWindow()/255, Gx, -1, 1, 0, 3, 1, 0, BORDER_DEFAULT);
			Sobel((*windows)[i][j]->getImageWindow()/255, Gy, -1, 0, 1, 3, 1, 0, BORDER_DEFAULT);

			int Vx, Vy;
			Vx = 0;
			Vy = 0;
			for (int k = 0; k < N; k++) {
				for (int l = 0; l < N; l++) {
					Vx = Vx + 2 * Gx.at<uchar>(k, l) * Gy.at<uchar>(k, l);//[k][l] * Gy[k][l];
					Vy = Vy + Gx.at<uchar>(k, l) * Gx.at<uchar>(k, l) * Gy.at<uchar>(k, l) * Gy.at<uchar>(k, l);
				}
			}

			//Grava o ângulo da janela na variável "angle", atributo da classe window
			if (Vx == 0) {	//a tangente de um valor dividido por zero é 90º = PI/2
				(*windows)[i][j]->setAngle( (double)M_PI * 0.5);
			}
			else {
				(*windows)[i][j]->setAngle( (double)0.5 * atan((double) Vy / Vx));
			}

			//(*windows)[i][j]->setAngle(0.785398163); //45º em rad

			cout << "Ângulo janela (em graus) " << i << ", " << j << ": " << ((double)(180 / M_PI) * (*windows)[i][j]->getAngle());// << endl;
			cout << "; Ângulo janela (em radianos) " << i << ", " << j << ": " << (*windows)[i][j]->getAngle() << endl;
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
		cout << "Erro ao tentar remover borda da imagem: imagem original é menor que o tamanho da imagem sem borda." << endl;
	}
	for (int i = 0; i < newSize; i++){
		for (int j = 0; j < newSize; j++) {
			imageWithoutBorder->at<uchar>(i, j) = imageWithBorder.at<uchar>((i + (originalSize - newSize)/2), (j + (originalSize - newSize)/2));
		}
	}
	return;
}

void gaborFilter (vector < vector <window*> > *windows, int row, int col, int N) {
	for (int i = 1; i < row/N - 1; i++) {
		for (int j = 1; j <  col/N - 1; j++) {
			Mat imageWithBorder;
			getWindowBorder (&imageWithBorder, N, *windows, i, j);

//			Mat gaborKernel = getGaborKernel( Size(N + 4,N + 4) , 4, (*windows)[i][j]->getAngle()+ M_PI/2, (*windows)[i][j]->getFrequency(), 1, 0, CV_32F );

			//DE ACORDO COM A TEORIA, A ORIENTAÇÃO DA JANELA DEVERIA SER UM ÂNGULO (EM RADIANOS), NORMAL À ORIENTAÇÃO REAL
			//APESAR DISSO, DE ACORDO COM OS TESTE REALIZADOS, ISSO NÃO OCORRE. O ÂNGULO DEVE SER A ORIENTAÇÃO NATURAL DA JANELA
			Mat gaborKernel = getGaborKernel( Size(N + 4,N + 4) , 4, (*windows)[i][j]->getAngle(), 5.8, 1, 0, CV_32F );
			filter2D(imageWithBorder, imageWithBorder, -1, gaborKernel);
			removeWindowBorder( &(*windows)[i][j]->imageWindow, imageWithBorder, N + 4, N);
			//filter2D((*windows)[i][j]->getImageWindow(), (*windows)[i][j]->imageWindow, -1, gaborKernel);
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
