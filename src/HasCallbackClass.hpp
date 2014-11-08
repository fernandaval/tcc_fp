/*
 * HasCallbackClass.hpp
 *
 *  Created on: Nov 2, 2014
 *      Author: rafael
 */

#ifndef HASCALLBACKCLASS_HPP_
#define HASCALLBACKCLASS_HPP_

/**
 * 	Classe abstrata (interface) que serve como base para outras classes que precisem do método callback();
 **/
class HasCallbackClass{
public:
	virtual void callback(void) = 0;
};



#endif /* HASCALLBACKCLASS_HPP_ */
