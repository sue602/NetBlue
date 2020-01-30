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
	bool writeSndMsg(ByteArray * msg);
	bool writeRevMsg(ByteArray * msg);
	ByteArray * popBuffer();
	ByteArray * popWriteMsg();
	ByteArray * popReadMsg();
	void clearReadList();
	void clearWriteList();
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
