

#include "window.hpp"

using namespace cv;
using namespace std;


window::window(int imageRowSize, int imageColSize, int imageType){
	this->quality= -1;
	this->frequency = -1;
	this->angle = -1;
	this->imageWindow.create(imageRowSize, imageColSize, imageType);
}


int window::getQuality(void){
	return this->quality;
}

void window::setQuality(int quality){
	this->quality = quality;
}

double window::getFrequency(void){
	return this->frequency;
}

void window::setFrequency(double frequency){
	this->frequency = frequency;
}

double window::getAngle(void){
	return this->angle;
}

void window::setAngle(double angle){
	this->angle = angle;
}

Mat window::getImageWindow(void){
	return this->imageWindow;
}

void window::setImageWindow(Mat imageWindow){
	this->imageWindow = imageWindow;
}
