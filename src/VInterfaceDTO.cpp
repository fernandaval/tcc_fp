/*
 * VInterfaceDTO.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: fernanda
 */

#include "VInterfaceDTO.hpp"

float VInterfaceDTO::getAvgTime1(void){
	return this->avgTime1;
}

float VInterfaceDTO::getAvgTime2(void){
	return this->avgTime2;
}

float VInterfaceDTO::getAvgTime31(void){
	return this->avgTime31;
}

float VInterfaceDTO::getAvgTime32(void){
	return this->avgTime32;
}

float VInterfaceDTO::getAvgTime33(void){
	return this->avgTime33;
}

void VInterfaceDTO::setAvgTime1(float avgTime1){
	this->avgTime1 = avgTime1;
}

void VInterfaceDTO::setAvgTime2(float avgTime2){
	this->avgTime2 = avgTime2;
}

void VInterfaceDTO::setAvgTime31(float avgTime31){
	this->avgTime31 = avgTime31;
}

void VInterfaceDTO::setAvgTime32(float avgTime32){
	this->avgTime32 = avgTime32;
}

void VInterfaceDTO::setAvgTime33(float avgTime33){
	this->avgTime33 = avgTime33;
}

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

void VInterfaceDTO::setFar1(float far1){
	this->far1 = far1;
}

float VInterfaceDTO::getFar1(void){
	return this->far1;
}

void VInterfaceDTO::setFar2(float far2){
	this->far2 = far2;
}

float VInterfaceDTO::getFar2(void){
	return this->far2;
}

void VInterfaceDTO::setFar31(float far31){
	this->far31 = far31;
}

float VInterfaceDTO::getFar31(void){
	return this->far31;
}

void VInterfaceDTO::setFar32(float far32){
	this->far32 = far32;
}

float VInterfaceDTO::getFar32(void){
	return this->far32;
}

void VInterfaceDTO::setFar33(float far33){
	this->far33 = far33;
}

float VInterfaceDTO::getFar33(void){
	return this->far33;
}

void VInterfaceDTO::setFrr1(float frr1){
	this->frr1 = frr1;
}

float VInterfaceDTO::getFrr1(void){
	return this->frr1;
}

void VInterfaceDTO::setFrr2(float frr2){
	this->frr2 = frr2;
}

float VInterfaceDTO::getFrr2(void){
	return this->frr2;
}

void VInterfaceDTO::setFrr31(float frr31){
	this->frr31 = frr31;
}

float VInterfaceDTO::getFrr31(void){
	return this->frr31;
}

void VInterfaceDTO::setFrr32(float frr32){
	this->frr32 = frr32;
}

float VInterfaceDTO::getFrr32(void){
	return this->frr32;
}

void VInterfaceDTO::setFrr33(float frr33){
	this->frr33 = frr33;
}

float VInterfaceDTO::getFrr33(void){
	return this->frr33;
}

void VInterfaceDTO::setTar1(float tar1){
	this->tar1 = tar1;
}

float VInterfaceDTO::getTar1(void){
	return this->tar1;
}

void VInterfaceDTO::setTar2(float tar2){
	this->tar2 = tar2;
}

float VInterfaceDTO::getTar2(void){
	return this->tar2;
}

void VInterfaceDTO::setTar31(float tar31){
	this->tar31 = tar31;
}

float VInterfaceDTO::getTar31(void){
	return this->tar31;
}

void VInterfaceDTO::setTar32(float tar32){
	this->tar32 = tar32;
}

float VInterfaceDTO::getTar32(void){
	return this->tar32;
}

void VInterfaceDTO::setTar33(float tar33){
	this->tar33 = tar33;
}

float VInterfaceDTO::getTar33(void){
	return this->tar33;
}

void VInterfaceDTO::setTrr1(float trr1){
	this->trr1 = trr1;
}

float VInterfaceDTO::getTrr1(void){
	return this->trr1;
}

void VInterfaceDTO::setTrr2(float trr2){
	this->trr2 = trr2;
}

float VInterfaceDTO::getTrr2(void){
	return this->trr2;
}

void VInterfaceDTO::setTrr31(float trr31){
	this->trr31 = trr31;
}

float VInterfaceDTO::getTrr31(void){
	return this->trr31;
}

void VInterfaceDTO::setTrr32(float trr32){
	this->trr32 = trr32;
}

float VInterfaceDTO::getTrr32(void){
	return this->trr32;
}

void VInterfaceDTO::setTrr33(float trr33){
	this->trr33 = trr33;
}

float VInterfaceDTO::getTrr33(void){
	return this->trr33;
}
