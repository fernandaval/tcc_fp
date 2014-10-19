/*
 * minutia.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: fernanda
 */

#include "minutia.hpp"

using namespace std;

minutia::minutia() {
	// TODO Auto-generated constructor stub
	this->x = -1;
	this->y = -1;
	this->theta = -1;
	this->quality = -1;
}

void minutia::setMinutia(int X, int Y, int theta, int quality) {
	this->x = X;
	this->y = Y;
	this->theta = theta;
	this->quality = quality;
}
int minutia::getX(void) {
	return this->x;
}

int minutia::getY(void) {
	return this->y;
}

int minutia::getTheta(void) {
	return this->theta;
}

int minutia::getQuality(void) {
	return this->quality;
}

void minutia::setX(int X) {
	this->x = X;
	return;
}

void minutia::setY(int Y) {
	this->y = Y;
	return;
}

void minutia::setTheta(int theta) {
	this->theta = theta;
	return;
}

void minutia::setQuality(int quality) {
	this->quality = quality;
	return;
}


