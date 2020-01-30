/*
 * NetworkMgr.cpp
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#include "MessageQueue.h"
#include "Poco/AtomicCounter.h"
#include "NetworkMgr.h"
#include "ByteArray.h"
#include "ClientsMgr.h"
#include "ClientConnection.h"

NetworkMgr::NetworkMgr() {
	// TODO Auto-generated constructor stub
	_mq = new MessageQueue(64,128);
}

NetworkMgr::~NetworkMgr() {
	// TODO Auto-generated destructor stub
}


int NetworkMgr::uniqueId()
{
	static Poco::AtomicCounter counter;
	return ++counter;
}

void NetworkMgr::addClientMsg(ByteArray * ba)
{
	_mq->writeRevMsg(ba);
}

ByteArray * NetworkMgr::popClientMsg()
{
	return _mq->popReadMsg();
}

void NetworkMgr::release(ByteArray * ba)
{
	_mq->release(ba);
}

//向底层发送消息
void NetworkMgr::sendResponseMessage(ByteArray * msg)
{
	int ID = msg->getTag();
	ClientConnection * cc = ClientsMgr::Instance()->getClient(ID);
	if(cc)
	{
		ByteArray * sndMsg = _mq->popBuffer();
		sndMsg->setTag(ID);
		unsigned short * len = (unsigned short *) msg->base();
		int tmplen = * len;
		sndMsg->copy(msg->base(),*len);
		cc->sendMsg(sndMsg);
	}
}

//向服务器发请求消息
void NetworkMgr::sendRequestMessage(ByteArray * msg)
{


}

//向多个服务器发送消息
void NetworkMgr::broadcastRequestMessage(ByteArray * msg)
{

}

//向多个服务器广播多个转发消息
void NetworkMgr::broadcastResponseMessage(ByteArray * msg)
{

}

//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
void NetworkMgr::disconnectClient(unsigned int aHandle)
{

}
