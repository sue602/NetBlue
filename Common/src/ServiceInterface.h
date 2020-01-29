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
	virtual void Init()=0;
	//释放资源
	virtual void Uninit()=0;
	//向底层发送消息
	virtual void SendResponseMessage(const char * msg, unsigned int sz)=0;
	//向服务器发请求消息
	virtual void SendRequestMessage(const char * msg, unsigned int sz)=0;
	//向多个服务器发送消息
	virtual void BroadcastRequestMessage(const char * msg, unsigned int sz)=0;
	//向多个服务器广播多个转发消息
	virtual void BroadcastResponseMessage(const char * msg, unsigned int sz)=0;
	//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
	virtual void DisconnectClient(unsigned int aHandle)=0;
	//获取服务器KEY
	virtual long ServerKey()=0;

};
//逻辑模块接口
class IServiceModule
{
public:
	//模块初始化
	virtual void Init(IService * aService)=0;
	//处理message,返回0=消息已处理，//返回-1，消息未处理
	virtual int ProcessRequestMessage(const char * msg, unsigned int sz)=0;
	virtual int ProcessResponseMessage(const char * msg, unsigned int sz)=0;
	//处理逻辑
	virtual int Run()=0;
	//模块被销毁
	virtual void Uninit()=0;
};


//库实现方法，多态接口
typedef IServiceModule * (*MODULE_ENTRY_FUNC)(void);
#define MODULE_ENTRY_FUNC_NAME "ServiceModule"
#define SERVICE_ENTRY_DECLARE extern "C" Foundation_API\
	IServiceModule * ServiceModule()

#define SERVICE_ENTRY_DEFINE(CLASS) extern "C" Foundation_API \
	IServiceModule * ServiceModule()\
	{\
		return (IServiceModule *)new CLASS;\
	}\

#endif /* SRC_SERVICEINTERFACE_H_ */
