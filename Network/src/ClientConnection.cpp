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
	std::cout << "~ClientConnection " << std::endl;
	delete _mq;
	_mq = NULL;
	ClientsMgr::Instance()->delClient(ID);
}

void ClientConnection::run(){
	StreamSocket& ss = socket();
	_socket = & ss;
	Poco::Timespan timeout(2,0);
	_socket->setReceiveTimeout(timeout);
	_socket->setBlocking(false);//设置为非阻塞
	try
	{
		unsigned short headRead = 0;
		const unsigned short headSize = 2;
		char buffer[headSize] = {0};//头长度
		while(!_stopped)
		{
			//接收数据
			int n = ss.receiveBytes(buffer+headRead, headSize-headRead);
			if( n > 0)
			{
				headRead = headRead + n;
			}
			if(0 == n) //这里表示对端的socket已正常关闭
			{
				_stopped = 1;
				std::cout << "client disconnect id = " << ID << std::endl;
				break;
			}
			else if(headSize == headRead)
			{
				headRead = 0;
				int len  = buffer[0] * 256 + buffer[1];
				memset(buffer,0,headSize);//清零
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
		std::cerr << "Client : disconnected from " << _peer << std::endl;
	}
	catch (Poco::Exception& exc)
	{
		std::cerr << "Client Connection= " << ID << ":" << exc.displayText() << std::endl;
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
//	_socket->sendBytes(msg->base(), msg->length());
//	_mq->release(msg);
}

void ClientConnection::disconnect()
{
	_stopped = true;
	_socket->shutdown();
}
