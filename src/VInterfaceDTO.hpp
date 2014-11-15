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

	float getMatchingTime3(void);
	void setMatchingTime3(float matchingTime3);

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

	int getFeedback(void);
	void setFeedback(int feedback);

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
	float matchingTime3;

	bool accepted1;
	bool accepted2;
	bool accepted31;
	bool accepted32;
	bool accepted33;

	int feedback;
};



#endif /* VINTERFACEDTO_HPP_ */
