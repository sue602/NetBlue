/*
 * NetworkMgr.h
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#ifndef SRC_NETWORKMGR_H_
#define SRC_NETWORKMGR_H_

#include "Singleton.h"

class MessageQueue;
class ByteArray;

class NetworkMgr : public Singleton<NetworkMgr> {
public:
	NetworkMgr();
	virtual ~NetworkMgr();
	int uniqueId();
	void addClientMsg(ByteArray * ba);
	ByteArray * popClientMsg();
	void release(ByteArray * ba);
	//向底层发送消息
	void sendResponseMessage(ByteArray * msg);
	//向服务器发请求消息
	void sendRequestMessage(ByteArray * msg);
	//向多个服务器发送消息
	void broadcastRequestMessage(ByteArray * msg);
	//向多个服务器广播多个转发消息
	void broadcastResponseMessage(ByteArray * msg);
	//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
	void disconnectClient(unsigned int aHandle);
protected:
	MessageQueue * _mq;
};

#endif /* SRC_NETWORKMGR_H_ */
