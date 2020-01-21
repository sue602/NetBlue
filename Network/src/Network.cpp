/*
 * network.cpp
 *
 *  Created on: Dec 14, 2019
 *      Author: ltzd
 */

#include <stdio.h>
using namespace std;

#include "Poco/SharedLibrary.h"
using Poco::SharedLibrary;

#include "Network.h"


Network::Network()
{

}

Network::~Network()
{

}

void
Network::Init()
{
	LoadModule();
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
