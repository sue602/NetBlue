/*
 * ServerRejectFilter.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include "Poco/Logger.h"
using Poco::Logger;

#include <iostream>
#include "CommonDef.h"
#include "ClientRejectFilter.h"

ClientRejectFilter::ClientRejectFilter() {
	// TODO Auto-generated constructor stub

}

ClientRejectFilter::~ClientRejectFilter() {
	// TODO Auto-generated destructor stub
}

//默认可以连接到服务器
bool ClientRejectFilter::accept(const StreamSocket& socket)
{
	Logger& logger = Logger::get(LOGGER_NAME);
	std::string client("new connection = ");
	client.append(socket.peerAddress().toString());
	poco_information(logger,client);
	return true;
}
