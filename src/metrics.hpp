/*
 * metrics.hpp
 *
 *  Created on: Nov 15, 2014
 *      Author: priscila
 */

#ifndef METRICS_HPP_
#define METRICS_HPP_

#include "VInterfaceDTO.hpp"

void metricsUpdate(bool feedback, bool accepted1, bool accepted2, bool accepted31, bool accepted32, bool accepted33, float executionTime1, float executionTime2, float executionTime31, float executionTime32, float executionTime33);

void minimumScoresUpdate();

void refreshAllMetrics(VInterfaceDTO& vinterface);

#endif /* METRICS_HPP_ */
