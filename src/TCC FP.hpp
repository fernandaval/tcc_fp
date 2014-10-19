/*
 * TCC FP.hpp
 *
 *  Created on: Oct 12, 2014
 *      Author: rafael
 */

#ifndef TCC_FP_HPP_
#define TCC_FP_HPP_
#include "VInterfaceDTO.hpp"

class Main{
public:
	void execute();
	VInterfaceDTO getVInterfaceDTO(void);

private:
	VInterfaceDTO vInterfaceDTO;
};



#endif /* TCC_FP_HPP_ */
