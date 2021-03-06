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
	clearRevList();
	clearSndList();
}

bool MessageQueue::pushSndMsg(ByteArray * msg)
{
	FastMutex::ScopedLock lock(_writeMutex);
	_writeList.push_back(msg);
	return true;
}

bool MessageQueue::pushRevMsg(ByteArray * msg)
{
	FastMutex::ScopedLock lock(_readMutex);
	_readList.push_back(msg);
	return true;
}

ByteArray * MessageQueue::popSndMsg()
{
	if (_writeList.empty())
		return NULL;
	FastMutex::ScopedLock lock(_writeMutex);
	ByteArray * data = * _writeList.begin();
	_writeList.erase(_writeList.begin());
	return data;
}

ByteArray * MessageQueue::popRevMsg()
{
	if (_readList.empty())
		return NULL;
	FastMutex::ScopedLock lock(_readMutex);
	ByteArray * data = * _readList.begin();
	_readList.erase(_readList.begin());
	return data;
}

void MessageQueue::clearRevList()
{
	FastMutex::ScopedLock lock(_readMutex);
	BlockVec::iterator itr = _readList.begin();
	for(; itr != _readList.end();itr++)
	{
		release(* itr);
	}
}

void MessageQueue::clearSndList()
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
		ptr->reuse();//重置
		_pMemoryPool.pop_back();
		return ptr;
	}
}
