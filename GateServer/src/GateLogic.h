/*
 * GateServer.h
 *
 *  Created on: Jan 20, 2020
 *      Author: ltzd
 */

#ifndef GATELOGIC_H_
#define GATELOGIC_H_

#include "ServiceInterface.h"
#include "Poco/ClassLibrary.h"

class ByteArray;

class GateLogic : public IServiceModule
{
public:
	GateLogic();
	~GateLogic();

	void init(IService * aService);
	//处理message,返回0=消息已处理，//返回-1，消息未处理
	int handleRequestMessage(ByteArray * msg);
	int handleResponseMessage(ByteArray * msg);
	//处理逻辑
	int handle();
	//模块被销毁
	void unInit();

private:
	IService * iService;
};

SERVICE_ENTRY_DECLARE;


#endif /* GATELOGIC_H_ */
