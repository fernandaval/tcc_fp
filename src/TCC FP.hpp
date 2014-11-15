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
	void runSystem1(string path, int option, int idUser);
	void runSystem2(string path, int option, int idUser);
	void runSystem3(string path, int option, int idUser);
	void updateMetrics();
private:
	VInterfaceDTO vInterfaceDTO;
};



#endif /* TCC_FP_HPP_ */
