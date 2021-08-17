#pragma once

#ifndef _WMIINSTANCE_IML
#define _WMIINSTANCE_IML

#include "WmiInstance.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	template<typename T>
	WmiInstance<T>::WmiInstance(const T& arg_pMember)
		: WmiObject(arg_pMember.GetObjectName()), _pMember(arg_pMember)
	{
		_pMember.GetObjectPtr()->SpawnInstance(0, &_pObject);
		std::cout << "[WmiInstance] created!" << std::endl;
	}

	template<typename T>
	WmiInstance<T>::~WmiInstance()
	{
		_pObject->Release();
		std::cout << "[WmiInstance] destroyed!" << std::endl;
	}

	template<typename T>
	const T& WmiInstance<T>::GetMember() const
	{
		return _pMember;
	}

	template<typename T>
	void WmiInstance<T>::Put(const std::wstring& arg_strPropertyName, VARIANT vtProp) const
	{
		auto hres = _pObject->Put(arg_strPropertyName.c_str(), 0, &vtProp, NULL);
		std::cout << "[WmiInstance::Put] Result: 0x" << std::hex << hres << std::endl;
	}

	template<typename T>
	VARIANT WmiInstance<T>::Get(const std::wstring& arg_strPropertyName) const
	{
		VARIANT vtProp;
		VariantInit(&vtProp);

		_pObject->Get(arg_strPropertyName.c_str(), 0, &vtProp, nullptr, nullptr);

		return vtProp;
	}

	template<typename T>
	std::wstring WmiInstance<T>::GetObjectText() const
	{
		CComPtr<IWbemObjectTextSrc> pTextSource;
		pTextSource.CoCreateInstance(CLSID_WbemObjectTextSrc, nullptr, CLSCTX_INPROC_SERVER);

		CComBSTR strXML;
		pTextSource->GetText(0, _pObject, WMI_OBJ_TEXT_WMI_DTD_2_0, nullptr, &strXML);

		pTextSource.Release();

		return std::wstring(strXML);
	}
}

#endif
