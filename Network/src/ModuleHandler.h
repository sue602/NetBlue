/*
 * ModuleHandler.h
 *
 *  Created on: Jan 29, 2020
 *      Author: ltzd
 */

#ifndef SRC_MODULEHANDLER_H_
#define SRC_MODULEHANDLER_H_

#include "ServiceInterface.h"
#include "Poco/Runnable.h"
#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
using Poco::Runnable;
using Poco::Timespan;
using Poco::Timestamp;

class ModuleHandler : public Runnable {
public:
	ModuleHandler(IServiceModule * module);
	virtual ~ModuleHandler();
	virtual void run();
	void Stop();
protected:
	short _stopped;
	IServiceModule * _module;

private:
	void handler(double dt);
};

#endif /* SRC_MODULEHANDLER_H_ */
