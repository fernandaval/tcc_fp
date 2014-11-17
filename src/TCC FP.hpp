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
#include <string>
#include <sqlite3.h>

using namespace std;

void runSystem1(VInterfaceDTO vinterface, string path, int option, int idUser);
void runSystem2(VInterfaceDTO vinterface, string path, int option, int idUser);
void runSystem3(VInterfaceDTO vinterface, string path, int option, int idUser);
void fillBD(VInterfaceDTO vinterface);

enum SystemMode{
	DEFAULT = 0, RIGID = 1, TOLERANT = 2
};

class Main{
public:
	void execute(HasCallbackClass *_clazz, string imagePath);
	VInterfaceDTO getVInterfaceDTO(void);
    void updateMetrics(bool feedback, HasCallbackClass *_clazz);
private:
	VInterfaceDTO vInterfaceDTO;
};



#endif /* TCC_FP_HPP_ */
