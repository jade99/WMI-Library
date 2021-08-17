#include "WmiObject.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	WmiObject::WmiObject(const std::wstring& arg_strObjectName)
	{
		const auto length = arg_strObjectName.size() + 1;
		_strObjectName = new wchar_t[length];
		wcscpy_s(_strObjectName, length, arg_strObjectName.c_str());

		std::cout << "[WmiObject] created!" << std::endl;
	}

	WmiObject::WmiObject(const WmiObject& arg_wmiOther)
	{
		_pObject = arg_wmiOther._pObject;

		const auto lenName = wcslen(arg_wmiOther._strObjectName) + 1;
		_strObjectName = new wchar_t[lenName];
		wcscpy_s(_strObjectName, lenName, arg_wmiOther._strObjectName);

		const auto lenPath = wcslen(arg_wmiOther._strObjectPath) + 1;
		_strObjectPath = new wchar_t[lenPath];
		wcscpy_s(_strObjectPath, lenPath, arg_wmiOther._strObjectPath);

		std::cout << "[WmiObject] copied!" << std::endl;
	}

	WmiObject::WmiObject(WmiObject&& arg_wmiOther) noexcept
	{
		_pObject = arg_wmiOther._pObject;
		arg_wmiOther._pObject = nullptr;

		_strObjectName = arg_wmiOther._strObjectName;
		arg_wmiOther._strObjectName = nullptr;

		_strObjectPath = arg_wmiOther._strObjectPath;
		arg_wmiOther._strObjectPath = nullptr;

		std::cout << "[WmiObject] moved!" << std::endl;
	}

	WmiObject::~WmiObject()
	{
		delete _strObjectName;
		delete _strObjectPath;

		std::cout << "[WmiObject] destroyed!" << std::endl;
	}

	void WmiObject::RetrievePath()
	{
		if (_pObject == nullptr) return;

		CComVariant vtPATH;
		const auto hres = _pObject->Get(L"__PATH", 0, &vtPATH, nullptr, nullptr);

		if (FAILED(hres) || vtPATH.vt != VT_BSTR) return;

		const auto length = wcslen(vtPATH.bstrVal) + 1;
		_strObjectPath = new wchar_t[length];
		wcscpy_s(_strObjectPath, length, vtPATH.bstrVal);
	}

	IWbemClassObject* WmiObject::GetObjectPtr() const
	{
		return _pObject;
	}

	std::wstring WmiObject::GetObjectName() const
	{
		return std::wstring(_strObjectName);
	}

	std::wstring WmiObject::GetObjectPath() const
	{
		return std::wstring(_strObjectPath);
	}
}