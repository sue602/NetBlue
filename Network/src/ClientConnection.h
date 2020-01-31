/*
 * ServerConnection.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef SRC_CLIENTCONNECTION_H_
#define SRC_CLIENTCONNECTION_H_

#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/TCPServerConnection.h"
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;

class MessageQueue;

class ClientConnection : public TCPServerConnection {
public:
	ClientConnection(const StreamSocket& ss);
	virtual ~ClientConnection();
	//inherit from superclass
	virtual void run();
	void setID(int id);
	int getID();
	void sendMsg(ByteArray * msg);
	void disconnect();//主动断开连接
protected:
	std::string _peer;
	int ID;
	MessageQueue * _mq;
	StreamSocket * _socket;
	short _stopped;
};

#endif /* SRC_CLIENTCONNECTION_H_ */
