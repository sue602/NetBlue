/*
 * ModuleHandler.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include <iostream>
#include "ModuleHandler.h"
#include "Poco/Thread.h"
using Poco::Thread;

ModuleHandler::ModuleHandler():
_stopped(0)
{

}

ModuleHandler::~ModuleHandler()
{
}


void ModuleHandler::run()
{
	Timestamp startTime;
	Timestamp now;
	double elapsed = 0;
	while(!_stopped)
	{
		handler(elapsed);
		now.update();
		Timestamp::TimeDiff dt = now - startTime;//100纳秒为1个单位
		//转化为毫秒
		elapsed = dt * 100 / 1000000.0;
		//更新时间
		startTime.update();
	}
}

void
ModuleHandler::Stop()
{
	_stopped = true;
}

void
ModuleHandler::handler(double dt)
{

}
