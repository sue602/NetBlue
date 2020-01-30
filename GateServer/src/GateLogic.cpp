//============================================================================
// Name        : GateServer.cpp
// Author      : Su YinXiang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;



#include "GateLogic.h"

GateLogic::GateLogic()
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

int GateLogic::handleRequestMessage(const char * aMsg, unsigned int size)
{
	return -1;
}

int GateLogic::handleResponseMessage(const char * aMsg, unsigned int size)
{
	return -1;
}

int GateLogic::handle()
{
	return 0;
}

SERVICE_ENTRY_DEFINE(GateLogic);
