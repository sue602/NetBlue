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
#include "Poco/ThreadPool.h"
using Poco::ThreadPool;

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
	try
	{
		int n = 0;
		unsigned short headRead = 0;
		const unsigned short headSize = 2;
		char buffer[headSize] = {0};//头长度
		//接收头数据
		n = ss.receiveBytes(buffer+headRead, headSize-headRead);
		while (n > 0)
		{
			headRead = headRead + n;
			if(headSize == headRead)
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
						int count = ss.receiveBytes(dataRev->base() + headSize,len);
						if(0 == count) //这里表示对端的socket已正常关闭
						{
							_stopped = 1;
							std::cout << "client disconnect id = " << ID << std::endl;
							return;
						}
						recv += count;
					}
					dataRev->setTag(ID);
					NetworkMgr::Instance()->addClientMsg(dataRev);

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
			 //继续读头文件
			n = ss.receiveBytes(buffer+headRead, headSize-headRead);
		}
		_stopped = 1;
		std::cout << "client disconnect id = " << ID << std::endl;
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
}

void ClientConnection::disconnect()
{
	_stopped = true;
	_socket->shutdown();
}
