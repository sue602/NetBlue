//============================================================================
// Name        : Gate.cpp
// Author      : Su YinXiang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


//Poco INCLUDEs
#include "Poco/Manifest.h"
#include "Poco/ClassLoader.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Thread.h"

//GS INCLUDEs
#include "GS_ServiceModule.h"
using namespace GS;
using Poco::Thread;

#include "Gateway.h"
#include "CmdHandler.h"

typedef Poco::ClassLoader<IService> PluginLoader;
typedef Poco::Manifest<IService> PluginManifest;

int main(int argc, char** argv) {
	PluginLoader loader;std::string libName("libNetwork");
	libName += Poco::SharedLibrary::suffix(); // append .dll or .so
	loader.loadLibrary(libName);
	IService* network = loader.create("Network");
	loader.classFor("Network").autoDelete(network);
	//初始化
	network->Init();
	//接收命令
	CmdHandler cmdRunnable(network);
	Thread thread;
	thread.start(cmdRunnable);
	thread.join();
	//释放资源
	network->Uninit();
	loader.unloadLibrary(libName);
}
