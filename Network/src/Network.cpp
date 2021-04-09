/*
 * network.cpp
 *
 *  Created on: Dec 14, 2019
 *      Author: ltzd
 */

#include <stdio.h>
using namespace std;

#include "Poco/Thread.h"
#include "Poco/SharedLibrary.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServerParams.h"

using Poco::Thread;
using Poco::SharedLibrary;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServerParams;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnectionFactoryImpl;

#include "Network.h"
#include "ClientsMgr.h"
#include "NetworkMgr.h"
#include "ModuleHandler.h"
#include "ClientRejectFilter.h"
#include "ClientConnection.h"


Network::Network():
		_tcpsrv(0),
		_modHandler(0),
		_module(0)
{
	NetworkMgr::Instance();//初始化

}

Network::~Network()
{
	delete _tcpsrv;
}

void Network::init()
{
	loadModule();
	initServer();
	startServer();
}

void Network::unInit()
{
	stopServer();
}

void Network::broadcastRequestMessage(ByteArray * msg)
{
	NetworkMgr::Instance()->broadcastRequestMessage(msg);
}

void Network::broadcastResponseMessage(ByteArray * msg)
{
	NetworkMgr::Instance()->broadcastResponseMessage(msg);
}

void Network::sendResponseMessage(ByteArray * msg)
{
	NetworkMgr::Instance()->sendResponseMessage(msg);
}

void Network::sendRequestMessage(ByteArray * msg)
{
	NetworkMgr::Instance()->sendRequestMessage(msg);
}

void Network::disconnectClient(unsigned int aHandle)
{
	NetworkMgr::Instance()->disconnectClient(aHandle);
}

long Network::serverKey()
{
	std::cout << "network server key\n" << std::endl;
	return 1;
}

void Network::loadModule()
{
	//加载逻辑库
	std::string path("libGateServer");
//	path.append(SharedLibrary::suffix()); // adds ".dll" or ".so"
	path.append(".so");
	SharedLibrary library(path); // will also load the library
	MODULE_ENTRY_FUNC func = (MODULE_ENTRY_FUNC)(library.getSymbol(MODULE_ENTRY_FUNC_NAME));
	if(func)
	{
		_module=func();
		if(_module)
		{
			_module->init(this);
		}
	}
	//启动模块处理线程
	_modHandler = new ModuleHandler(_module);
	_modThread.start(*_modHandler);//启动线程
}

void Network::initServer()
{
	short port = 2222;
	ServerSocket svs(port);//端口号
	TCPServerParams* pParams = new TCPServerParams;
	pParams->setMaxQueued(8192);
	pParams->setThreadIdleTime(64);
	_tcpsrv = new TCPServer(new TCPServerConnectionFactoryImpl<ClientConnection>(), svs, pParams);
	_tcpsrv->setConnectionFilter(new ClientRejectFilter);
	printf("Server is listen on %d...\n",port);
}

/* 启动服务器
 * */
void Network::startServer()
{
	_tcpsrv->start();
}

/* 停止服务器
 * */
void Network::stopServer()
{
	//等待网络线程结束
	_tcpsrv->stop();
	//停止模块处理线程
	_modHandler->Stop();
	//等待模块处理线程结束
	_modThread.join();
}
