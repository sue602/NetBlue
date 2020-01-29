/*
 * network.cpp
 *
 *  Created on: Dec 14, 2019
 *      Author: ltzd
 */

#include <stdio.h>
using namespace std;

#include "Poco/SharedLibrary.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServerParams.h"
using Poco::SharedLibrary;
using Poco::Net::TCPServer;
using Poco::Net::ServerSocket;
using Poco::Net::TCPServerParams;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnectionFactoryImpl;

#include "Network.h"
#include "ServerRejectFilter.h"
#include "ServerConnection.h"


Network::Network():
		tcpsrv(0)
{

}

Network::~Network()
{
	delete tcpsrv;
}

void
Network::Init()
{
	LoadModule();
	InitServer();
	StartServer();
}

void
Network::Uninit()
{
	StopServer();
}

void
Network::BroadcastRequestMessage(const char * msg, unsigned int sz)
{

}

void
Network::BroadcastResponseMessage(const char * msg,unsigned int sz)
{

}

void
Network::SendResponseMessage(const char * msg, unsigned int sz)
{

}

void
Network::SendRequestMessage(const char * msg, unsigned int sz)
{

}

void
Network::DisconnectClient(unsigned int aHandle)
{

}

long
Network::ServerKey()
{
	std::cout << "network server key\n" << std::endl;
	return 1;
}

void
Network::LoadModule()
{
	//加载逻辑库
	std::string path("libGateServer");
	path.append(SharedLibrary::suffix()); // adds ".dll" or ".so"
	SharedLibrary library(path); // will also load the library
	MODULE_ENTRY_FUNC func = (MODULE_ENTRY_FUNC)(library.getSymbol(MODULE_ENTRY_FUNC_NAME));
	IServiceModule * module=0;
	if(func)
	{
		module=func();
		if(module)
		{
			printf("network init = %p\n",this);
			module->Init(this);
		}
	}
}

void
Network::InitServer(){
	ServerSocket svs(2222);//端口号
	TCPServerParams* pParams = new TCPServerParams;
	pParams->setMaxThreads(2);
	pParams->setMaxQueued(2);
	pParams->setThreadIdleTime(64);
	tcpsrv = new TCPServer(new TCPServerConnectionFactoryImpl<ServerConnection>(), svs, pParams);
	tcpsrv->setConnectionFilter(new ServerRejectFilter);
}

/* 启动服务器
 * */
void
Network::StartServer(){
	tcpsrv->start();
}

/* 停止服务器
 * */
void
Network::StopServer(){
	tcpsrv->stop();
}
