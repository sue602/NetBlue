/*
 * ServerRejectFilter.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef SRC_SERVERREJECTFILTER_H_
#define SRC_SERVERREJECTFILTER_H_

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServer.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnectionFilter;

class ServerRejectFilter : public TCPServerConnectionFilter {
public:
	ServerRejectFilter();
	virtual ~ServerRejectFilter();
	virtual bool accept(const StreamSocket& socket);
};

#endif /* SRC_SERVERREJECTFILTER_H_ */
