/*
 * TCC FP.hpp
 *
 *  Created on: Oct 12, 2014
 *      Author: rafael
 */

#ifndef TCC_FP_HPP_
#define TCC_FP_HPP_
#include "VInterfaceDTO.hpp"
#include "HasCallbackClass.hpp"

enum SystemMode{
	DEFAULT = 0, RIGID = 1, TOLERANT = 2
};

class Main{
public:
	void execute(SystemMode mode,  HasCallbackClass *_clazz);
	VInterfaceDTO getVInterfaceDTO(void);
	void fillBD();
	void runSystem1();
	void runSystem2();
	void runSystem3();
	void updateMetrics();
private:
	VInterfaceDTO vInterfaceDTO;
};



#endif /* TCC_FP_HPP_ */
