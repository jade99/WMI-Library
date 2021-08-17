#pragma once

#ifndef _WMIOBJECT_H
#define _WMIOBJECT_H

#include "DLLDefinition.h"

#include <string>
#include <wbemidl.h>

namespace Jade
{
	class WmiObject
	{
	protected:
		IWbemClassObject* _pObject = nullptr;

	private:
		wchar_t* _strObjectName = nullptr;
		wchar_t* _strObjectPath = nullptr;

	public:
		WmiObject() = delete;
		~WmiObject();

		WmiObject(const std::wstring& arg_strObjectName);
		WmiObject(const WmiObject& arg_wmiOther);
		WmiObject(WmiObject&& arg_wmiOther) noexcept;

	protected:
		void RetrievePath();
		IWbemClassObject* GetObjectPtr() const;

	public:
		std::wstring GetObjectName() const;
		std::wstring GetObjectPath() const;
	};
}

#endif

