/*
 * matching.hpp
 *
 *  Created on: Aug 8, 2014
 *      Author: priscila
 */

#ifndef MATCHING_HPP_
#define MATCHING_HPP_

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

#define TRUE 1
#define FALSE 0
bool matching();

#endif /* MATCHING_HPP_ */
