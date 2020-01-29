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
	Timespan interval(0,999);//设置毫秒时间
	int time = 0;
	while(!_stopped)
	{
		handler(time);
		now.update();
		Timestamp::TimeDiff dt = now - startTime;
		if(interval - dt > 0)
		{
			std::cout << "sleep =" << dt << std::endl;
			time = interval.microseconds();//转化成毫秒
			Thread::sleep( time - dt);
		}else
		{
			std::cout << "yield =" << dt << std::endl;
			Thread::yield();
			time = interval.microseconds() + (dt%1000000)*1000;//转化成毫秒
		}
		//更新时间
		startTime.update();
	}
}

void
ModuleHandler::Stop()
{
	_stopped = false;
}

static int xx= 0;
void
ModuleHandler::handler(int dt)
{
	if( xx == 3)
	{
		Thread::sleep( 3000 );
	}
	xx++;
	Timespan startTime;
	std::cout << "handler =" << dt << " = " << startTime.totalSeconds() << " - " << startTime.totalMicroseconds() << std::endl;
}
