/*
 * ServiceModule.h
 *
 *  Created on: Dec 14, 2019
 *      Author: Su YinXiang
 */

#ifndef SRC_SERVICEINTERFACE_H_
#define SRC_SERVICEINTERFACE_H_

#define  KMessageConsumed 0
#define  KMessageNotConsumed -1

//服务接口
class IService
{
public:
	//初始化
	virtual void init()=0;
	//释放资源
	virtual void unInit()=0;
	//向底层发送消息
	virtual void sendResponseMessage(const char * msg, unsigned int sz)=0;
	//向服务器发请求消息
	virtual void sendRequestMessage(const char * msg, unsigned int sz)=0;
	//向多个服务器发送消息
	virtual void broadcastRequestMessage(const char * msg, unsigned int sz)=0;
	//向多个服务器广播多个转发消息
	virtual void broadcastResponseMessage(const char * msg, unsigned int sz)=0;
	//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
	virtual void disconnectClient(unsigned int aHandle)=0;
	//获取服务器KEY
	virtual long serverKey()=0;

};
//逻辑模块接口
class IServiceModule
{
public:
	//模块初始化
	virtual void init(IService * aService)=0;
	//处理message,返回0=消息已处理，//返回-1，消息未处理
	virtual int handleRequestMessage(const char * msg, unsigned int sz)=0;
	virtual int handleResponseMessage(const char * msg, unsigned int sz)=0;
	//处理逻辑
	virtual int handle()=0;
	//模块被销毁
	virtual void unInit()=0;
};


//库实现方法，多态接口
typedef IServiceModule * (*MODULE_ENTRY_FUNC)(void);
#define MODULE_ENTRY_FUNC_NAME "ServiceModule"
#define SERVICE_ENTRY_DECLARE extern "C" POCO_LIBRARY_API\
	IServiceModule * ServiceModule()

#define SERVICE_ENTRY_DEFINE(CLASS) extern "C" POCO_LIBRARY_API \
	IServiceModule * ServiceModule()\
	{\
		return (IServiceModule *)new CLASS;\
	}\

#endif /* SRC_SERVICEINTERFACE_H_ */
