/*
 * ServerConnection.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef SRC_SERVERCONNECTION_H_
#define SRC_SERVERCONNECTION_H_

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServerConnection.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

class ServerConnection : public TCPServerConnection {
public:
	ServerConnection(const StreamSocket& s);
	virtual ~ServerConnection();
	//inherit from superclass
	virtual void run();
};

#endif /* SRC_SERVERCONNECTION_H_ */
