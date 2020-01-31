/*
 * ClientsMgr.cpp
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#include "NetworkMgr.h"
#include "ClientConnection.h"
#include "ClientsMgr.h"

ClientsMgr::ClientsMgr() {

}

ClientsMgr::~ClientsMgr() {
}

bool ClientsMgr::addClient(ClientConnection * cc)
{
	FastMutex::ScopedLock lock(_clientsMutex);
	int ID = NetworkMgr::Instance()->uniqueId();
	cc->setID(ID);
	_clients.insert(CLIENT_PAIR(ID,cc));
	return true;
}

ClientConnection * ClientsMgr::getClient(int ID)
{
	FastMutex::ScopedLock lock(_clientsMutex);
	CLIENT_MAP::iterator itr = _clients.find(ID);
	if(itr != _clients.end())
		return itr->second;
	return NULL;
}

bool ClientsMgr::delClient(int ID)
{
	FastMutex::ScopedLock lock(_clientsMutex);
	CLIENT_MAP::iterator itr = _clients.find(ID);
	if(itr != _clients.end())
	{
		_clients.erase(itr);
		return true;
	}
	return false;
}

void ClientsMgr::clearClients()
{
	FastMutex::ScopedLock lock(_clientsMutex);
	_clients.clear();
}
