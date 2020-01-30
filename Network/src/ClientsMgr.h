/*
 * ClientsMgr.h
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#ifndef SRC_CLIENTSMGR_H_
#define SRC_CLIENTSMGR_H_

#include <map>
#include "Singleton.h"
#include "Poco/Mutex.h"
using Poco::FastMutex;

class ClientConnection;

typedef std::map<int,ClientConnection *> CLIENT_MAP;
typedef std::pair<int,ClientConnection *> CLIENT_PAIR;

class ClientsMgr : public Singleton<ClientsMgr> {
public:
	ClientsMgr();
	virtual ~ClientsMgr();
	bool addClient(ClientConnection * cc);
	ClientConnection * getClient(int ID);
	bool delClient(int ID);
	void clearClients();
protected:
	CLIENT_MAP _clients;
	FastMutex   _clientsMutex;
};

#endif /* SRC_CLIENTSMGR_H_ */
