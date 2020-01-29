//============================================================================
// Name        : Gate.cpp
// Author      : Su YinXiang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


//Poco INCLUDEs
#include "ServiceInterface.h"
#include "Poco/Manifest.h"
#include "Poco/ClassLoader.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Thread.h"
#include "Poco/Logger.h"
#include "Poco/Message.h"

//GS INCLUDEs
using Poco::Thread;
using Poco::Logger;
using Poco::Message;

#include <iostream>
#include "Gateway.h"
#include "CmdHandler.h"

typedef Poco::ClassLoader<IService> PluginLoader;
typedef Poco::Manifest<IService> PluginManifest;

Gateway::Gateway()
{

}

Gateway::~Gateway()
{

}

void
Gateway::initialize(Application& self)
{
	//server start step 2;
	loadConfiguration(); // load default configuration files, if present
	ServerApplication::initialize(self);
}

void
Gateway::uninitialize()
{
	ServerApplication::uninitialize();
}

void
Gateway::defineOptions(OptionSet& options)
{
	//server start step 1;
	ServerApplication::defineOptions(options);
}

void
Gateway::handleOption(const std::string& name, const std::string& value)
{

}

int
Gateway::main(const std::vector<std::string>& args)
{
	//server start step 3;
	Logger& logger = Logger::get("GateServer");
	logger.setLevel(Message::PRIO_INFORMATION);
	PluginLoader loader;std::string libName("libNetwork");
	libName += Poco::SharedLibrary::suffix(); // append .dll or .so
	loader.loadLibrary(libName);
	IService* network = loader.create("Network");
	loader.classFor("Network").autoDelete(network);
	poco_information(logger,"Server is init ...");
	//初始化
	network->Init();
	poco_information(logger,"Server start success !");
	//接收命令线程
	CmdHandler cmdRunnable(network);
	Thread thread;
	thread.start(cmdRunnable);//启动线程
	thread.join();//等待线程结束
	poco_information(logger,"Server is uninit ...");
	//释放资源
	network->Uninit();
	poco_information(logger,"Server uninit success");
	loader.unloadLibrary(libName);
	poco_information(logger,"Server done");
	return Application::EXIT_OK;
}

//主函数
int main(int argc, char** argv) {
	Gateway app;
	return app.run(argc, argv);
}
