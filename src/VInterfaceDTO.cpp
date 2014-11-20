/*
 * VInterfaceDTO.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: fernanda
 */

#include "VInterfaceDTO.hpp"

float VInterfaceDTO::getTotalTime1(void){
	float totalTime = this->minutiaeExtractionTime1 + this->matchingTime1;
	return totalTime;
}

float VInterfaceDTO::getTotalTime2(void){
	float totalTime = this->equalizationTime2 + this->binarizationTime2 + this->minutiaeExtractionTime2 + this->matchingTime2;
	return totalTime;
}

float VInterfaceDTO::getTotalTime31(void){
	float totalTime = this->windowingTime3 + this->equalizationTime3 + this->gaborFilterTime3 + this->binarizationTime3 + this->minutiaeExtractionTime3 + this->matchingTime31;
	return totalTime;
}

float VInterfaceDTO::getTotalTime32(void){
	float totalTime = this->windowingTime3 + this->equalizationTime3 + this->gaborFilterTime3 + this->binarizationTime3 + this->minutiaeExtractionTime3 + this->matchingTime32;
	return totalTime;
}

float VInterfaceDTO::getTotalTime33(void){
	float totalTime = this->windowingTime3 + this->equalizationTime3 + this->gaborFilterTime3 + this->binarizationTime3 + this->minutiaeExtractionTime3 + this->matchingTime33;
	return totalTime;
}

float VInterfaceDTO::getWindowingTime3(void){
	return this->windowingTime3;
}

void VInterfaceDTO::setWindowingTime3(float windowingTime3){
	this->windowingTime3 = windowingTime3;
}

float VInterfaceDTO::getEqualizationTime2(void){
	return this->equalizationTime2;
}

void VInterfaceDTO::setEqualizationTime2(float equalizationTime2){
	this->equalizationTime2 = equalizationTime2;
}

float VInterfaceDTO::getEqualizationTime3(void){
	return this->equalizationTime3;
}

void VInterfaceDTO::setEqualizationTime3(float equalizationTime3){
	this->equalizationTime3 = equalizationTime3;
}

float VInterfaceDTO::getGaborFilterTime3(void){
	return this->gaborFilterTime3;
}
void VInterfaceDTO::setGaborFilterTime3(float gaborFilterTime3){
	this->gaborFilterTime3 = gaborFilterTime3;
}

float VInterfaceDTO::getBinarizationTime2(void){
	return this->binarizationTime2;
}
void VInterfaceDTO::setBinarizationTime2(float binarizationTime2){
	this->binarizationTime2 = binarizationTime2;
}

float VInterfaceDTO::getBinarizationTime3(void){
	return this->binarizationTime3;
}
void VInterfaceDTO::setBinarizationTime3(float binarizationTime3){
	this->binarizationTime3 = binarizationTime3;
}

float VInterfaceDTO::getMinutiaeExtractionTime1(void){
	return this->minutiaeExtractionTime1;
}
void VInterfaceDTO::setMinutiaeExtractionTime1(float minutiaeExtractionTime1){
	this->minutiaeExtractionTime1 = minutiaeExtractionTime1;
}

float VInterfaceDTO::getMinutiaeExtractionTime2(void){
	return this->minutiaeExtractionTime2;
}
void VInterfaceDTO::setMinutiaeExtractionTime2(float minutiaeExtractionTime2){
	this->minutiaeExtractionTime2 = minutiaeExtractionTime2;
}

float VInterfaceDTO::getMinutiaeExtractionTime3(void){
	return this->minutiaeExtractionTime3;
}
void VInterfaceDTO::setMinutiaeExtractionTime3(float minutiaeExtractionTime3){
	this->minutiaeExtractionTime3 = minutiaeExtractionTime3;
}

float VInterfaceDTO::getMatchingTime1(void){
	return this->matchingTime1;
}

void VInterfaceDTO::setMatchingTime1(float matchingTime1){
	this->matchingTime1 = matchingTime1;
}

float VInterfaceDTO::getMatchingTime2(void){
	return this->matchingTime2;
}

void VInterfaceDTO::setMatchingTime2(float matchingTime2){
	this->matchingTime2 = matchingTime2;
}

float VInterfaceDTO::getMatchingTime31(void){
	return this->matchingTime31;
}

void VInterfaceDTO::setMatchingTime31(float matchingTime31){
	this->matchingTime31 = matchingTime31;
}

float VInterfaceDTO::getMatchingTime32(void){
	return this->matchingTime32;
}

void VInterfaceDTO::setMatchingTime32(float matchingTime32){
	this->matchingTime32 = matchingTime32;
}

float VInterfaceDTO::getMatchingTime33(void){
	return this->matchingTime33;
}

void VInterfaceDTO::setMatchingTime33(float matchingTime33){
	this->matchingTime33 = matchingTime33;
}

bool VInterfaceDTO::getAccepted1(void){
	return this->accepted1;
}

void VInterfaceDTO::setAccepted1(bool accepted1){
	this->accepted1 = accepted1;
}

bool VInterfaceDTO::getAccepted2(void){
	return this->accepted2;
}

void VInterfaceDTO::setAccepted2(bool accepted2){
	this->accepted2 = accepted2;
}

bool VInterfaceDTO::getAccepted31(void){
	return this->accepted31;
}

void VInterfaceDTO::setAccepted31(bool accepted31){
	this->accepted31 = accepted31;
}

bool VInterfaceDTO::getAccepted32(void){
	return this->accepted32;
}

void VInterfaceDTO::setAccepted32(bool accepted32){
	this->accepted32 = accepted32;
}

bool VInterfaceDTO::getAccepted33(void){
	return this->accepted33;
}

void VInterfaceDTO::setAccepted33(bool accepted33){
	this->accepted33 = accepted33;
}

void VInterfaceDTO::setFeedback(bool feedback){
	this->feedback = feedback;
}

bool VInterfaceDTO::getFeedback(void){
	return this->feedback;
}

void VInterfaceDTO::setMinutiaeQuantity1(int minutiaeQuantity1){
	this->minutiaeQuantity1 = minutiaeQuantity1;
}

int VInterfaceDTO::getMinutiaeQuantity1(void){
	return this->minutiaeQuantity1;
}

void VInterfaceDTO::setMinutiaeQuantity2(int minutiaeQuantity2){
	this->minutiaeQuantity2 = minutiaeQuantity2;
}

int VInterfaceDTO::getMinutiaeQuantity2(void){
	return this->minutiaeQuantity2;
}

void VInterfaceDTO::setMinutiaeQuantity3(int minutiaeQuantity3){
	this->minutiaeQuantity3 = minutiaeQuantity3;
}

int VInterfaceDTO::getMinutiaeQuantity3(void){
	return this->minutiaeQuantity3;
}

void VInterfaceDTO::setMinutiaeQuality1(float minutiaeQuality1){
	this->minutiaeQuality1 = minutiaeQuality1;
}

float VInterfaceDTO::getMinutiaeQuality1(void){
	return this->minutiaeQuality1;
}

void VInterfaceDTO::setMinutiaeQuality2(float minutiaeQuality2){
	this->minutiaeQuality2 = minutiaeQuality2;
}

float VInterfaceDTO::getMinutiaeQuality2(void){
	return this->minutiaeQuality2;
}

void VInterfaceDTO::setMinutiaeQuality3(float minutiaeQuality3){
	this->minutiaeQuality3 = minutiaeQuality3;
}

float VInterfaceDTO::getMinutiaeQuality3(void){
	return this->minutiaeQuality3;
}
