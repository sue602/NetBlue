/*
 * CmdHandler.cpp
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#include <iostream>
#include <memory>
#include <string.h>
#include "CmdHandler.h"

CmdHandler::CmdHandler(IService* mSvr):
	_iSvr(mSvr),
	_stopped(0)
{

}

CmdHandler::~CmdHandler() {
	// TODO Auto-generated destructor stub
}

void CmdHandler::run()
{
	char cmd[64] = {0};
	while(!_stopped)
	{
		std::cin >> cmd;
		if( memcmp("stop",cmd,strlen(cmd)) == 0)
		{
			break;
		}
	}
}
