/*
 * window.hpp
 *
 *  Created on: Aug 8, 2014
 *      Author: fernanda
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_


#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class window {
private:
	int quality;
	double frequency;
	double angle;

public:
	Mat imageWindow;

//public:
	//construtor
	window(int imageRowSize, int imageColSize, int imageType);

	/*
	*	quality
	*/
	int getQuality(void);
	void setQuality(int quality);

	/*
	*	frequency
	*/
	double getFrequency(void);
	void setFrequency(double frequency);

	/*
	*	angle
	*/
	double getAngle(void);
	void setAngle(double angle);

	/*
	*	imageWindow
	*/
	Mat getImageWindow(void);
	void setImageWindow(Mat imageWindow);

};






#endif /* WINDOW_HPP_ */
