#include "WmiMethod.h"

#include <iostream>

namespace Jade
{
	WmiMethod::WmiMethod(
		const std::wstring arg_strMethodName,
		IWbemClassObject* const& arg_pClass,
		const std::wstring arg_strClassPath
	)
		: _strClassPath(arg_strClassPath), _strMethodName(arg_strMethodName)
	{
		arg_pClass->GetMethod(CComBSTR(arg_strMethodName.c_str()), 0, &_pMethod, nullptr);
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

	std::wstring WmiMethod::GetClassPath() const
	{
		return _strClassPath;
	}

	std::wstring WmiMethod::GetMethodName() const
	{
		return _strMethodName;
	}
}