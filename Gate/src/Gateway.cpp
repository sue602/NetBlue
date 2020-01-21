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

//GS INCLUDEs
#include "GS_ServiceModule.h"
using namespace GS;

#include "Gateway.h"

typedef Poco::ClassLoader<IService> PluginLoader;
typedef Poco::Manifest<IService> PluginManifest;

int main(int argc, char** argv) {
	PluginLoader loader;std::string libName("libNetwork");
	libName += Poco::SharedLibrary::suffix(); // append .dll or .so
	loader.loadLibrary(libName);
	IService* network = loader.create("Network");
	//初始化
	network->Init();
	loader.classFor("Network").autoDelete(network);
	loader.unloadLibrary(libName);
}
