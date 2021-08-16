#pragma once

#ifndef _WMICLASS_H
#define _WMICLASS_H

#include "DLLDefinition.h"
#include "WmiMethod.h"

#include <string>
#include <WbemIdl.h>

namespace Jade
{
	class DLLDECL WmiClass
	{
	private:
		IWbemClassObject* _pClass = nullptr;

	public:
		WmiClass() = delete;
		~WmiClass();

		WmiClass(IWbemClassObject*& arg_pClass);

	public:
		BSTR GetPath() const;
		IWbemClassObject* GetObjectPtr() const;

		WmiMethod GetMethod(const std::wstring& arg_strMethodName) const;
		WmiInstance<WmiClass> CreateInstance() const;
	};
}

#endif