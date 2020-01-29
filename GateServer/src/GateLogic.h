/*
 * GateServer.h
 *
 *  Created on: Jan 20, 2020
 *      Author: ltzd
 */

#ifndef GATELOGIC_H_
#define GATELOGIC_H_

#include "ServiceInterface.h"
#include "Poco/Foundation.h"

class GateLogic : public IServiceModule
{
public:
	GateLogic();
	~GateLogic();

	void Init(IService * aService);
	//处理message,返回0=消息已处理，//返回-1，消息未处理
	int ProcessRequestMessage(const char * aMsg, unsigned int size);
	int ProcessResponseMessage(const char * aMsg, unsigned int size);
	//处理逻辑
	int Run();
	//模块被销毁
	void Uninit();

private:
	IService * iService;
};

SERVICE_ENTRY_DECLARE;


#endif /* GATELOGIC_H_ */
