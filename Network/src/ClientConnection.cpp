/*
 * ClientConnection.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include "Poco/Logger.h"
using Poco::Logger;
#include <iostream>
#include "ClientsMgr.h"
#include "NetworkMgr.h"
#include "MessageQueue.h"
#include "ClientConnection.h"

ClientConnection::ClientConnection(const StreamSocket& ss):
		TCPServerConnection(ss),
		ID(-1)
{
	_peer = ss.peerAddress().toString();
	_mq = new MessageQueue(64,128);
	ClientsMgr::Instance()->addClient(this);
}

ClientConnection::~ClientConnection() {
	std::cout << "connection disconnected " << std::endl;
	delete _mq;
	ClientsMgr::Instance()->delClient(ID);
}

void ClientConnection::run(){
	StreamSocket& ss = socket();
	_socket = & ss;
	try
	{
		char buffer[2];//头长度
		for(;;)
		{
			//接收数据
			int n = ss.receiveBytes(buffer, sizeof(buffer));
			if(2 == n)
			{
				int len  = buffer[0] * 256 + buffer[1];
				ByteArray * dataRev = _mq->popBuffer();
				if(NULL != dataRev)
				{
					dataRev->writeUint16(len);
					int recv = 0;
					while (recv<(len-2))
					{
						int count = ss.receiveBytes(dataRev->base() + 2,len);
						recv += count;
					}
					dataRev->setTag(ID);
					NetworkMgr::Instance()->addClientMsg(dataRev);
				}
			}
//			ByteArray * dataSnd = _mq->popWriteMsg();
//			if( NULL != dataSnd)
//			{
//				int len = dataSnd->length();
//				ss.sendBytes(dataSnd->base(), dataSnd->length());
//				//回收
//				_mq->release(dataSnd);
//			}
		}
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
	}
}

void ClientConnection::setID(int id)
{
	ID = id;
}

int ClientConnection::getID()
{
	return ID;
}

void ClientConnection::sendMsg(ByteArray * msg)
{
	int len = msg->length();
	_socket->sendBytes(msg->base(), msg->length());
	_mq->release(msg);
}
