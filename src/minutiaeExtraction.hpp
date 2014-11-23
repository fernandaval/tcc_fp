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
#include <stdio.h>
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
#include <iostream>
#include <opencv2/imgproc/types_c.h>
#include <fstream>
#include <sqlite3.h>
#include <time.h>

#include "window.hpp"
#include "preProcessing.hpp"
#include "minutia.hpp"
#include "VInterfaceDTO.hpp"

#define TRUE 1
#define FALSE 0

void minutiaeExtract(Mat image, int idSystem, int option, int id);

void minutiaePlot(int row, int col, int N, Mat minutiaeImage, int idSystem, VInterfaceDTO& vinterface);

#endif /* MINUTIAEEXTRACTION_HPP_ */
