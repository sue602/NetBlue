/*
 * network.h
 *
 *  Created on: Dec 14, 2019
 *      Author: ltzd
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <memory>
#include <iostream>
using namespace std;

#include "GS_Std.h"
#include "GS_Singleton.h"
#include "GS_ServiceModule.h"
using namespace GS;

//Poco INCLUDEs
#include "Poco/Manifest.h"
#include "Poco/ClassLoader.h"
#include "Poco/ClassLibrary.h"

namespace GS
{
	class Network : public IService,public CSingleton<Network>
	{
	public:
		Network();
		virtual ~Network();
	public:
		void LoadModule();
		void InitServer();
		void StartServer();
		void StopServer();
	public:
		//初始化
		virtual void Init();
		//释放资源
		virtual void Uninit();
		//向底层发送消息
		virtual void SendResponseMessage(const char * msg, unsigned int sz);
		//向服务器发请求消息
		virtual void SendRequestMessage(const char * msg, unsigned int sz);
		//向多个服务器发送消息
		virtual void BroadcastRequestMessage(const char * msg, unsigned int sz);
		//向多个服务器广播多个转发消息
		virtual void BroadcastResponseMessage(const char * msg, unsigned int sz);
		//关闭客户连接,参数为连接句柄，连接句柄一般存于命令的extension
		virtual void DisconnectClient(unsigned int aHandle);
		//获取服务器KEY
		virtual long ServerKey();
	protected:
		TCPServer* tcpsrv;
	public:
		friend class CSingleton<Network>;
	};
}

POCO_BEGIN_MANIFEST(IService)
	POCO_EXPORT_CLASS(Network)
POCO_END_MANIFEST



#endif /* SRC_NETWORK_H_ */
