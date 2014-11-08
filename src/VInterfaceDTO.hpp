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
	float getWindowingTime(void);
	void setWindowingTime(float windowingTime);

	float getEqualizationTime(void);
	void setEqualizationTime(float equalizationTime);

	float getGaborFilterTime(void);
	void setGaborFilterTime(float gaborFilterTime);

	float getBinarizationTime(void);
	void setBinarizationTime(float binarizationTime);

	float getMinutiaeExtractionTime(void);
	void setMinutiaeExtractionTime(float minutiaeExtractionTime);

	float getMatchingTime(void);
	void setMatchingTime(float matchingTime);

	bool getAccepted(void);
	void setAccepted(bool accepted);

private:
	float windowingTime;
	float equalizationTime;
	float gaborFilterTime;
	float binarizationTime;
	float minutiaeExtractionTime;
	float matchingTime;

	bool accepted;

};



#endif /* VINTERFACEDTO_HPP_ */
