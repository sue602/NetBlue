/*
 * ServerConnection.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include "Poco/Logger.h"
using Poco::Logger;
#include <iostream>
#include "ServerConnection.h"

ServerConnection::ServerConnection(const StreamSocket& ss): TCPServerConnection(ss) {
	_peer = ss.peerAddress().toString();
}

ServerConnection::~ServerConnection() {
	std::cout << "connection disconnected " << std::endl;
}

void ServerConnection::run(){
	StreamSocket& ss = socket();
	try
	{
		char buffer[256];
		int n = ss.receiveBytes(buffer, sizeof(buffer));
		while (n > 0)
		{
			ss.sendBytes(buffer, n);
			n = ss.receiveBytes(buffer, sizeof(buffer));
		}
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
	}
}
