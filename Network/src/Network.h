/*
 * network.h
 *
 *  Created on: Dec 14, 2019
 *      Author: ltzd
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <memory>
#include <iostream>
using namespace std;

#include "Singleton.h"
#include "ServiceInterface.h"

//Poco INCLUDEs
#include "Poco/Thread.h"
#include "Poco/Manifest.h"
#include "Poco/ClassLoader.h"
#include "Poco/ClassLibrary.h"

class ModuleHandler;

class Network : public IService
{
public:
	Network();
	virtual ~Network();
public:
	void loadModule();
	void initServer();
	void startServer();
	void stopServer();
public:
	//初始化
	virtual void init();
	//释放资源
	virtual void unInit();
	//向底层发送消息
	virtual void sendResponseMessage(const char * msg, unsigned int sz);
	//向服务器发请求消息
	virtual void sendRequestMessage(const char * msg, unsigned int sz);
	//向多个服务器发送消息
	virtual void broadcastRequestMessage(const char * msg, unsigned int sz);
	//向多个服务器广播多个转发消息
	virtual void broadcastResponseMessage(const char * msg, unsigned int sz);
	//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
	virtual void disconnectClient(unsigned int aHandle);
	//获取服务器KEY
	virtual long serverKey();
protected:
	TCPServer* _tcpsrv;
	ModuleHandler * _modHandler;
	Thread _modThread;
	IServiceModule * _module;
};

POCO_BEGIN_MANIFEST(IService)
	POCO_EXPORT_CLASS(Network)
POCO_END_MANIFEST

// optional set up and clean up functions
void pocoInitializeLibrary()
{
    std::cout << "Network Library initializing" << std::endl;
}
void pocoUninitializeLibrary()
{
    std::cout << "Network Library uninitializing" << std::endl;
}

#endif /* SRC_NETWORK_H_ */
