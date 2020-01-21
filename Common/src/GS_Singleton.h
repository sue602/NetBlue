#ifndef GS_SINGLETON_H_
#define GS_SINGLETON_H_

#include "GS_Std.h"

namespace GS
{
	//单例
	template<class T>
	class  CSingleton
	{
	private:
		static T * iInstance;
	public:
		static T * Instance();
		static void FreeInstance();
	};

	template<class T>
	T * CSingleton<T>::iInstance=0;

	template<class T>
	T * CSingleton<T>::Instance()
	{
		if(iInstance == 0)
		{
			iInstance=new T();
		}

		return iInstance;
	}

	template<class T>
	void CSingleton<T>::FreeInstance()
	{
		if(iInstance)
		{	
			delete iInstance;
			iInstance=0;
		}
	}
}

#endif
