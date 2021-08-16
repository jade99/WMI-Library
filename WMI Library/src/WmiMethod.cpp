#include "WmiMethod.h"

#include <iostream>

namespace Jade
{
	WmiMethod::WmiMethod(IWbemClassObject*& arg_pMethod, const BSTR arg_strClassPath, const BSTR arg_strMethodName)
		: _pMethod(arg_pMethod), _strClassPath(arg_strClassPath), _strMethodName(arg_strMethodName)
	{
		std::cout << "[WmiMethod] constructed!" << std::endl;
	}

	WmiMethod::~WmiMethod()
	{
		_pMethod->Release();
		std::cout << "[WmiMethod] destroyed!" << std::endl;
	}

	WmiInstance<WmiMethod> WmiMethod::CreateInstance() const
	{
		return WmiInstance<WmiMethod>(this);
	}

	IWbemClassObject* WmiMethod::GetObjectPtr() const
	{
		return _pMethod;
	}

	BSTR WmiMethod::GetClassPath() const
	{
		return _strClassPath;
	}

	BSTR WmiMethod::GetMethodName() const
	{
		return _strMethodName;
	}
}