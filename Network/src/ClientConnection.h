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
	virtual void run();//inherit from superclass
	void setID(int id);
	int getID();
	void sendMsg(ByteArray * msg);//发送消息,进队列
	void disconnect();//主动断开连接
protected:
	std::string _peer;
	int ID;
	MessageQueue * _mq;
	StreamSocket * _socket;
	short _stopped;
};

#endif /* SRC_CLIENTCONNECTION_H_ */
