#include "WmiClass.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	WmiClass::WmiClass(const std::wstring& arg_strClassName, IWbemServices* const& arg_pServices)
	{
		arg_pServices->GetObject(CComBSTR(arg_strClassName.c_str()), 0, nullptr, &_pClass, nullptr);
		std::cout << "[WmiClass] constructed!" << std::endl;
	}

	WmiClass::~WmiClass()
	{
		_pClass->Release();
		std::cout << "[WmiClass] destroyed!" << std::endl;
	}

	WmiMethod WmiClass::GetMethod(const std::wstring& arg_strMethodName, const std::wstring& arg_strClassPath) const
	{
		return WmiMethod(arg_strMethodName, _pClass, arg_strClassPath);
	}

	IWbemClassObject* WmiClass::GetObjectPtr() const
	{
		return _pClass;
	}

	WmiInstance<WmiClass> WmiClass::CreateInstance() const
	{
		return WmiInstance<WmiClass>(this);
	}
}