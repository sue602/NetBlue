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
		ID(-1),
		_mq(0),
		_socket(0),
		_stopped(0)
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
	_socket->setBlocking(false);//设置为非阻塞
	try
	{
		char buffer[2];//头长度
		while(!_stopped)
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
			//从待发送队列弹出一条消息
			ByteArray * dataSnd = _mq->popSndMsg();
			if( NULL != dataSnd)
			{
				ss.sendBytes(dataSnd->base(), dataSnd->length());
				//回收
				_mq->release(dataSnd);
			}
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
	_mq->pushSndMsg(msg);
}

void ClientConnection::disconnect()
{
	_stopped = true;
	_socket->shutdown();
}
