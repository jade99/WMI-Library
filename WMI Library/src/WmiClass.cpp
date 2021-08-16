#include "WmiClass.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	WmiClass::WmiClass(IWbemClassObject*& arg_pClass)
		: _pClass(arg_pClass)
	{
		std::cout << "[WmiClass] constructed!" << std::endl;
	}

	WmiClass::~WmiClass()
	{
		_pClass->Release();
		std::cout << "[WmiClass] destroyed!" << std::endl;
	}

	BSTR WmiClass::GetPath() const
	{
		CComVariant vtPath;
		_pClass->Get(L"__PATH", 0, &vtPath, nullptr, nullptr);

		return vtPath.bstrVal;
	}

	WmiMethod WmiClass::GetMethod(const std::wstring& arg_strMethodName) const
	{
		IWbemClassObject* pMethod = nullptr;
		_pClass->GetMethod(arg_strMethodName.c_str(), 0, &pMethod, nullptr);
		
		return WmiMethod(pMethod, GetPath(), CComBSTR(arg_strMethodName.c_str()));
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