/*
 * VInterfaceDTO.hpp
 *
 *  Created on: Oct 19, 2014
 *      Author: fernanda
 */

#ifndef VINTERFACEDTO_HPP_
#define VINTERFACEDTO_HPP_

/**
 *	Not exactly a DTO but is a class that stores data that will be used by the GUI project
 **/
class VInterfaceDTO{

public:

	float getAvgTime1(void);
	void setAvgTime1(float avgTime1);

	float getAvgTime2(void);
	void setAvgTime2(float avgTime2);

	float getAvgTime31(void);
	void setAvgTime31(float avgTime31);

	float getAvgTime32(void);
	void setAvgTime32(float avgTime32);

	float getAvgTime33(void);
	void setAvgTime33(float avgTime33);

	float getTotalTime1(void);

	float getTotalTime2(void);

	float getTotalTime31(void);

	float getTotalTime32(void);

	float getTotalTime33(void);

	float getWindowingTime3(void);
	void setWindowingTime3(float windowingTime3);

	float getEqualizationTime2(void);
	void setEqualizationTime2(float equalizationTime2);

	float getEqualizationTime3(void);
	void setEqualizationTime3(float equalizationTime3);

	float getGaborFilterTime3(void);
	void setGaborFilterTime3(float gaborFilterTime3);

	float getBinarizationTime2(void);
	void setBinarizationTime2(float binarizationTime2);

	float getBinarizationTime3(void);
	void setBinarizationTime3(float binarizationTime3);

	float getMinutiaeExtractionTime1(void);
	void setMinutiaeExtractionTime1(float minutiaeExtractionTime1);

	float getMinutiaeExtractionTime2(void);
	void setMinutiaeExtractionTime2(float minutiaeExtractionTime2);

	float getMinutiaeExtractionTime3(void);
	void setMinutiaeExtractionTime3(float minutiaeExtractionTime3);

	float getMatchingTime1(void);
	void setMatchingTime1(float matchingTime1);

	float getMatchingTime2(void);
	void setMatchingTime2(float matchingTime2);

	float getMatchingTime31(void);
	void setMatchingTime31(float matchingTime31);

	float getMatchingTime32(void);
	void setMatchingTime32(float matchingTime32);

	float getMatchingTime33(void);
	void setMatchingTime33(float matchingTime33);

	bool getAccepted1(void);
	void setAccepted1(bool accepted1);

	bool getAccepted2(void);
	void setAccepted2(bool accepted2);

	bool getAccepted31(void);
	void setAccepted31(bool accepted31);

	bool getAccepted32(void);
	void setAccepted32(bool accepted32);

	bool getAccepted33(void);
	void setAccepted33(bool accepted33);

	bool getFeedback(void);
	void setFeedback(bool feedback);

	int getMinutiaeQuantity1(void);
	void setMinutiaeQuantity1(int minutiaeQuantity1);

	float getMinutiaeQuality1(void);
	void setMinutiaeQuality1(float setMinutiaeQuality1);

	int getMinutiaeQuantity2(void);
	void setMinutiaeQuantity2(int minutiaeQuantity2);

	float getMinutiaeQuality2(void);
	void setMinutiaeQuality2(float setMinutiaeQuality2);

	int getMinutiaeQuantity3(void);
	void setMinutiaeQuantity3(int minutiaeQuantity3);

	float getMinutiaeQuality3(void);
	void setMinutiaeQuality3(float setMinutiaeQuality3);

	float getFar1(void);
	void setFar1(float far1);

	float getFar2(void);
	void setFar2(float far2);

	float getFar31(void);
	void setFar31(float far31);

	float getFar32(void);
	void setFar32(float far32);

	float getFar33(void);
	void setFar33(float far33);

	float getFrr1(void);
	void setFrr1(float frr1);

	float getFrr2(void);
	void setFrr2(float frr2);

	float getFrr31(void);
	void setFrr31(float frr31);

	float getFrr32(void);
	void setFrr32(float frr32);

	float getFrr33(void);
	void setFrr33(float frr33);

	float getTar1(void);
	void setTar1(float tar1);

	float getTar2(void);
	void setTar2(float tar2);

	float getTar31(void);
	void setTar31(float tar31);

	float getTar32(void);
	void setTar32(float tar32);

	float getTar33(void);
	void setTar33(float tar33);

	float getTrr1(void);
	void setTrr1(float trr1);

	float getTrr2(void);
	void setTrr2(float trr2);

	float getTrr31(void);
	void setTrr31(float trr31);

	float getTrr32(void);
	void setTrr32(float trr32);

	float getTrr33(void);
	void setTrr33(float trr33);

private:
	float windowingTime3;
	float equalizationTime2;
	float equalizationTime3;
	float gaborFilterTime3;
	float binarizationTime2;
	float binarizationTime3;
	float minutiaeExtractionTime1;
	float minutiaeExtractionTime2;
	float minutiaeExtractionTime3;
	float matchingTime1;
	float matchingTime2;
	float matchingTime31;
	float matchingTime32;
	float matchingTime33;
	float avgTime1;
	float avgTime2;
	float avgTime31;
	float avgTime32;
	float avgTime33;

	bool accepted1;
	bool accepted2;
	bool accepted31;
	bool accepted32;
	bool accepted33;

	int minutiaeQuantity1;
	int minutiaeQuantity2;
	int minutiaeQuantity3;

	float minutiaeQuality1;
	float minutiaeQuality2;
	float minutiaeQuality3;

	float far1;
	float far2;
	float far31;
	float far32;
	float far33;

	float frr1;
	float frr2;
	float frr31;
	float frr32;
	float frr33;

	float tar1;
	float tar2;
	float tar31;
	float tar32;
	float tar33;

	float trr1;
	float trr2;
	float trr31;
	float trr32;
	float trr33;

	bool feedback;
};



#endif /* VINTERFACEDTO_HPP_ */
