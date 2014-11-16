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

void binarization (vector < vector <window*> > *windows, int row, int col, int N);

void frequencyMap (vector < vector <window*> > *windows, int row, int col, int N);

void orientationMapOLD (vector < vector <window*> > *windows, int row, int col, int N);

void getWindowBorder (Mat *imageWithBorder, int N, vector < vector <window*> > windows, int i, int j);

void removeWindowBorder( Mat *imageWithoutBorder, Mat imageWithBorder, int originalSize, int newSize);

void gaborFilter (vector < vector <window*> > *windows, int row, int col, int N);

Mat do_FFT(Mat padded);

void get_lambda(Mat& in, float& lambda);

bool comparar (Point3f i,Point3f j);

void tempFrequencyMap (vector < vector <window*> > windows, int row, int col, int N, Mat *temp);

void groupImageWindows(Mat *imageNew, vector < vector <window*> > windows, int row, int col, int N);

Mat doFFT(Mat padded);

void get_angle_and_lambda(Mat& in, float& angle, float& lambda);

void applyGabor(Mat& in, Mat& out, float theta, float lambda);

void rotate(cv::Mat& src, double angle, cv::Mat& dst);

void gaborNET(Mat I, int row, int col, int N, Mat *finalImage);

void imageBinarization (Mat *image);

float getAngle (Mat kernelX, Mat kernelY, Mat image, int N);

void orientationMap (vector < vector <window*> > *windows, int row, int col, int N);

#endif /* PREPROCESSING_HPP_ */
