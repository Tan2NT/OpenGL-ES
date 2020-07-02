#pragma once

template <typename S>
class SingletonTemplate
{
protected:
	SingletonTemplate()  {}
	~SingletonTemplate() {}

	static S* ms_pInstance;

public:

	static S* GetInstance()
	{
		if (!ms_pInstance)
		{
			ms_pInstance =  new S;
		}
		return ms_pInstance;
	}

	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
};

template <class S>
S* SingletonTemplate<S>::ms_pInstance = 0;

