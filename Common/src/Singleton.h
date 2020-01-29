#ifndef GS_SINGLETON_H_
#define GS_SINGLETON_H_

//单例
template<class T>
class  Singleton
{
private:
	static T * iInstance;
public:
	static T * Instance();
	static void FreeInstance();
};

template<class T>
T * Singleton<T>::iInstance=0;

template<class T>
T * Singleton<T>::Instance()
{
	if(iInstance == 0)
	{
		iInstance=new T();
	}

	return iInstance;
}

template<class T>
void Singleton<T>::FreeInstance()
{
	if(iInstance)
	{
		delete iInstance;
		iInstance=0;
	}
}

#endif
