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

void
GateLogic::Init(IService * aService)
{
	this->iService = aService;
	printf("gatelogic = %p \n",aService);
}

void
GateLogic::Uninit()
{

}

int
GateLogic::ProcessRequestMessage(const char * aMsg, unsigned int size)
{
	return -1;
}

int
GateLogic::ProcessResponseMessage(const char * aMsg, unsigned int size)
{
	return -1;
}

int
GateLogic::Run()
{
	return 0;
}

SERVICE_ENTRY_DEFINE(GateLogic);
