/*
 * MessageQueue.h
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#ifndef SRC_MESSAGEQUEUE_H_
#define SRC_MESSAGEQUEUE_H_

#include "ByteArray.h"
#include "Poco/Mutex.h"
using Poco::FastMutex;

typedef std::vector<ByteArray *> BlockVec;

class MessageQueue {
public:
	MessageQueue(int preAlloc, int maxAlloc);
	virtual ~MessageQueue();
	bool pushSndMsg(ByteArray * msg);//待发送消息入队列
	bool pushRevMsg(ByteArray * msg);//接收到客户端消息，并将其入队列
	ByteArray * popBuffer();
	ByteArray * popSndMsg();//待发送出队列
	ByteArray * popRevMsg();//从队列中弹出已接收到消息
	void clearRevList();
	void clearSndList();
	void release(ByteArray * ba);
	void clearPool();
protected:
	BlockVec _pMemoryPool;
	FastMutex   _poolMutex;
	FastMutex   _readMutex;
	FastMutex   _writeMutex;
	BlockVec _writeList; //要写入队列
	BlockVec _readList;//要读取队列
};

#endif /* SRC_MESSAGEQUEUE_H_ */
