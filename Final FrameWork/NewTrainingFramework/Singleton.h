//#pragma once

//class Singleton
//{
//private:
//    static bool instanceFlag;
//    static Singleton *intance;
//
//public:
//	 Singleton(void);
//    static Singleton* GetInstance();
//    ~Singleton()
//    {
//        instanceFlag = false;
//    }
//};
//
//bool Singleton::instanceFlag = false;
//Singleton* Singleton::intance = NULL;
//Singleton* Singleton::GetInstance()
//{
//    if(! instanceFlag)
//    {
//        intance = new Singleton();
//        instanceFlag = true;
//        return intance;
//    }
//    else
//    {
//        return intance;
//    }
//}
#pragma once

template <class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if(!m_pInstance)
		{
			m_pInstance = new T;
		}
		return m_pInstance;	  
	}
	static void FreeInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = 0;
		}
	}
	//protected:
	Singleton(void);
	virtual ~Singleton(void);
private:
	Singleton(Singleton const&);	
	Singleton& operator=(Singleton const&);
	static T* m_pInstance;
};

template <class T> 
T* Singleton<T>::m_pInstance=NULL;

template <class T>
Singleton<T>::Singleton(void)
{
	m_pInstance = (T*) this;
}

template <class T>
Singleton<T>::~Singleton()
{
	m_pInstance = 0;
}