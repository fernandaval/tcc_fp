/*
 * minutiaeExtraction.hpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#ifndef MINUTIAEEXTRACTION_HPP_

#define MINUTIAEEXTRACTION_HPP_

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <sys/wait.h>
#include "err.h"
#include <signal.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<fstream>

#include "window.hpp"
#include "preProcessing.hpp"
#include "minutia.hpp"

#define TRUE 1
#define FALSE 0

void minutiaeExtract();

void minutiaePlot(vector < vector <window*> > *windows, int row, int col, int N);

#endif /* MINUTIAEEXTRACTION_HPP_ */
