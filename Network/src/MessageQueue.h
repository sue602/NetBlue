/*
 * MessageQueue.h
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#ifndef SRC_MESSAGEQUEUE_H_
#define SRC_MESSAGEQUEUE_H_

#include "Poco/MemoryPool.h"
#include "ByteArray.h"

class MessageQueue {
public:
	MessageQueue();
	virtual ~MessageQueue();
};

#endif /* SRC_MESSAGEQUEUE_H_ */
