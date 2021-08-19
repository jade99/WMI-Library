#pragma once

#ifndef _WMIINSTANCE_H
#define _WMIINSTACNE_H

#include <string>
#include <wbemidl.h>

namespace Jade
{
	template<typename T>
	class WmiInstance
	{
	private:
		IWbemClassObject* _pInstance = nullptr;
		const T* _pMember;

	public:
		WmiInstance() = delete;
		~WmiInstance();

		WmiInstance(const T* arg_pMember);

	public:
		const T* GetMember() const;
		IWbemClassObject* GetInstancePtr() const;

		void Put(const std::wstring& arg_strPropertyName, VARIANT vtProp) const;
		BSTR GetXML() const;
		VARIANT Get(const std::wstring& arg_strPropertyName) const;
	};

}

#include "WmiInstance.inl"

#endif
