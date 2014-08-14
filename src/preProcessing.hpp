/*
 * preProcessing.hpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#ifndef PREPROCESSING_HPP_
#define PREPROCESSING_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "window.hpp"
#include <math.h>

#define outputPath "/home/fernanda/Documents/tcc/imagens_teste/Output/"
//#define outputPath "/home/priscila/Documents/tcc/imagens_teste/Output/"

using namespace cv;
using namespace std;

//lê uma imagem de entrada e altera "image"
void imageRead (Mat *image, int *dpi, string imagePath);

//Preenche a borda da imagem com brancos para garantir que o janelamento terá 100% das janelas quadradas
void fillWhiteBorderInImage(Mat image, Mat *imageWhiteBorder, int N, int extraX, int extraY, int x, int y);

void equalizeWindows(int N, int col, int row, vector< vector <window*> > *windows);

//Altera a matriz com cada um adas janelas, criando uma por uma (a partir de uma imagem de entrada -> imageWhiteBorder)
void createWindows(Mat imageWhiteBorder, int N, int column, int row, vector< vector <window*> > *windows);

//Retorna as medidas da imagem que serão necessárias para realizar o janelamento
void imageMeasures(Mat image, int dpi, int *N, int *col, int *row);

void recreateImage(vector < vector <window*> > windows, int row, int col, int N, String imageName);

void thinningIteration(cv::Mat& im, int iter);

void thinning(cv::Mat& im);

void thinningWindows (vector < vector <window*> > *windows, int row, int col, int N);

void orientationMap (vector < vector <window*> > *windows, int row, int col, int N);

void gaborFilter (vector < vector <window*> > *windows, int row, int col, int N);

#endif /* PREPROCESSING_HPP_ */
