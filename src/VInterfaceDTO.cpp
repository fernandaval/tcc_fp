/*
 * VInterfaceDTO.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: fernanda
 */

#include "VInterfaceDTO.hpp"

float VInterfaceDTO::getWindowingTime(void){
	return this->windowingTime;
}
void VInterfaceDTO::setWindowingTime(float windowingTime){
	this->windowingTime = windowingTime;
}

float VInterfaceDTO::getEqualizationTime(void){
	return this->equalizationTime;
}
void VInterfaceDTO::setEqualizationTime(float equalizationTime){
	this->equalizationTime = equalizationTime;
}

float VInterfaceDTO::getGaborFilterTime(void){
	return this->gaborFilterTime;
}
void VInterfaceDTO::setGaborFilterTime(float gaborFilterTime){
	this->gaborFilterTime = gaborFilterTime;
}

float VInterfaceDTO::getBinarizationTime(void){
	return this->binarizationTime;
}
void VInterfaceDTO::setBinarizationTime(float binarizationTime){
	this->binarizationTime = binarizationTime;
}

float VInterfaceDTO::getMinutiaeExtractionTime(void){
	return this->minutiaeExtractionTime;
}
void VInterfaceDTO::setMinutiaeExtractionTime(float minutiaeExtractionTime){
	this->minutiaeExtractionTime = minutiaeExtractionTime;
}

float VInterfaceDTO::getMatchingTime(void){
	return this->matchingTime;
}
void VInterfaceDTO::setMatchingTime(float matchingTime){
	this->matchingTime = matchingTime;
}


