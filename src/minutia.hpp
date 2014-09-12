/*
 * minutia.hpp
 *
 *  Created on: Sep 10, 2014
 *      Author: fernanda
 */

#ifndef MINUTIA_HPP_
#define MINUTIA_HPP_

#include <iostream>
#include <vector>

class minutia{
private:
int x;
int y;
int theta;
int quality;

public:
	minutia();

	void setMinutia(int X, int Y, int theta, int quality);

	int getX(void);

	int getY(void);

	int getTheta(void);

	int getQuality(void);

	void setX(int X);

	void setY(int Y);

	void setTheta(int theta);

	void setQuality(int quality);
};


#endif /* POINT_HPP_ */
