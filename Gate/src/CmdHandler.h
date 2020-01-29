/*
 * CmdHandler.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef CMDHANDLER_H_
#define CMDHANDLER_H_

#include "Poco/Runnable.h"
using Poco::Runnable;

#include "GS_ServiceModule.h"
using namespace GS;

class CmdHandler : public Runnable {
public:
	CmdHandler(IService* mSvr);
	virtual ~CmdHandler();
	virtual void run();
protected:
	IService* _iSvr;
	short _stopped;
};

#endif /* CMDHANDLER_H_ */
