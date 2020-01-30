/*
 * MessageQueue.cpp
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#include "MessageQueue.h"

#define BLOCK_RESERVE 128

MessageQueue::MessageQueue(int preAlloc, int maxAlloc)
{
	int r = BLOCK_RESERVE;
	if (preAlloc > r)
		r = preAlloc;
	if (maxAlloc > 0 && maxAlloc < r)
		r = maxAlloc;
	_pMemoryPool.reserve(r);

	try
	{
		for (int i = 0; i < preAlloc; ++i)
		{
			_pMemoryPool.push_back(new ByteArray);
		}
	}
	catch (...)
	{
		clearPool();
		throw;
	}
}

MessageQueue::~MessageQueue() {
	clearPool();
	clearReadList();
	clearWriteList();
}

bool MessageQueue::writeSndMsg(ByteArray * msg)
{
	FastMutex::ScopedLock lock(_writeMutex);
	_writeList.push_back(msg);
	return true;
}

bool MessageQueue::writeRevMsg(ByteArray * msg)
{
	FastMutex::ScopedLock lock(_readMutex);
	_readList.push_back(msg);
	return true;
}

ByteArray * MessageQueue::popWriteMsg()
{
	FastMutex::ScopedLock lock(_writeMutex);

	if (_writeList.empty())
		return NULL;

	ByteArray * data = * _writeList.begin();
	_writeList.erase(_writeList.begin());
	return data;
}

ByteArray * MessageQueue::popReadMsg()
{
	FastMutex::ScopedLock lock(_readMutex);

	if (_readList.empty())
		return NULL;

	ByteArray * data = * _readList.begin();
	_readList.erase(_readList.begin());
	return data;
}

void MessageQueue::clearReadList()
{
	FastMutex::ScopedLock lock(_readMutex);
	BlockVec::iterator itr = _readList.begin();
	for(; itr != _readList.end();itr++)
	{
		release(* itr);
	}
}

void MessageQueue::clearWriteList()
{
	FastMutex::ScopedLock lock(_writeMutex);
	BlockVec::iterator itr = _writeList.begin();
	for(; itr != _writeList.end();itr++)
	{
		release(* itr);
	}
}

void MessageQueue::clearPool()
{
	FastMutex::ScopedLock lock(_poolMutex);

	for (BlockVec::iterator it = _pMemoryPool.begin(); it != _pMemoryPool.end(); ++it)
	{
		delete *it;
	}
	_pMemoryPool.clear();
}

void MessageQueue::release(ByteArray * ba)
{
	FastMutex::ScopedLock lock(_poolMutex);
	try
	{
		_pMemoryPool.push_back(ba);
	}
	catch (...)
	{
		delete ba;
	}
}


ByteArray * MessageQueue::popBuffer()
{
	FastMutex::ScopedLock lock(_poolMutex);

	if (_pMemoryPool.empty())
	{
		return (new ByteArray);
	}
	else
	{
		ByteArray* ptr = _pMemoryPool.back();
		ptr->reuse();
		_pMemoryPool.pop_back();
		return ptr;
	}
}
