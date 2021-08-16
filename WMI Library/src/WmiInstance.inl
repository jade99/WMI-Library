#pragma once

#ifndef _WMIINSTANCE_IML
#define _WMIINSTANCE_IML

#include "WmiInstance.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	template<typename T>
	WmiInstance<T>::WmiInstance(const T* arg_pMember)
		: _pMember(arg_pMember)
	{
		_pMember->GetObjectPtr()->SpawnInstance(0, &_pInstance);
		std::cout << "[WmiInstance] constructed!" << std::endl;
	}

	template<typename T>
	WmiInstance<T>::~WmiInstance()
	{
		_pInstance->Release();
		_pMember = nullptr;

		std::cout << "[WmiInstance] destroyed!" << std::endl;
	}

	template<typename T>
	IWbemClassObject* WmiInstance<T>::GetInstance() const
	{
		return _pInstance;
	}

	template<typename T>
	const T* WmiInstance<T>::GetMember() const
	{
		return _pMember;
	}

	template<typename T>
	void WmiInstance<T>::Put(const std::wstring& arg_strPropertyName, VARIANT& vtProp) const
	{
		auto hres = _pInstance->Put(arg_strPropertyName.c_str(), 0, &vtProp, NULL);
		std::cout << "0x" << std::hex << hres << std::endl;
	}

	template<typename T>
	BSTR WmiInstance<T>::GetXML() const
	{
		CComPtr<IWbemObjectTextSrc> pTextSource;
		pTextSource.CoCreateInstance(CLSID_WbemObjectTextSrc, nullptr, CLSCTX_INPROC_SERVER);

		CComBSTR strXML;
		pTextSource->GetText(0, _pInstance, WMI_OBJ_TEXT_WMI_DTD_2_0, nullptr, &strXML);

		return strXML;
	}
}

#endif
