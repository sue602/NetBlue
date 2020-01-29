/*
 * ServerRejectFilter.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include <iostream>
#include "ServerRejectFilter.h"

ServerRejectFilter::ServerRejectFilter() {
	// TODO Auto-generated constructor stub

}

ServerRejectFilter::~ServerRejectFilter() {
	// TODO Auto-generated destructor stub
}

//默认可以连接到服务器
bool ServerRejectFilter::accept(const StreamSocket& socket)
{
	std::cout << "new connection = " << socket.address().toString() << std::endl;
	return true;
}
