/*
 * ServerRejectFilter.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef SRC_CLIENTREJECTFILTER_H_
#define SRC_CLIENTREJECTFILTER_H_

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServer.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnectionFilter;

class ClientRejectFilter : public TCPServerConnectionFilter {
public:
	ClientRejectFilter();
	virtual ~ClientRejectFilter();
	virtual bool accept(const StreamSocket& socket);
};

#endif /* SRC_CLIENTREJECTFILTER_H_ */
