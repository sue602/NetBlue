//============================================================================
// Name        : GateServer.cpp
// Author      : Su YinXiang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory.h>
#include <stdio.h>
using namespace std;
#include "ByteArray.h"


#include "GateLogic.h"

GateLogic::GateLogic():
		iService(0)
{

}

GateLogic::~GateLogic()
{

}

void GateLogic::init(IService * aService)
{
	this->iService = aService;
}

void GateLogic::unInit()
{

}

int GateLogic::handleRequestMessage(ByteArray * msg)
{
	std::string result = msg->readString();
	std::cout << "gate logic recv = " << result << "\n" << std::endl;
	this->iService->sendResponseMessage(msg);
	return 1;
}

int GateLogic::handleResponseMessage(ByteArray * msg)
{

	return -1;
}

int GateLogic::handle()
{
	return 0;
}

SERVICE_ENTRY_DEFINE(GateLogic);
