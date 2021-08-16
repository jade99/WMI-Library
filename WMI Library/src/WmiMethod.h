#pragma once

#ifndef _WMIMETHOD_H
#define _WMIMETHOD_H

#include "DLLDefinition.h"
#include "WmiInstance.h"

#include <wbemidl.h>

namespace Jade
{
	class DLLDECL WmiMethod
	{
	private:
		IWbemClassObject* _pMethod = nullptr;
		const BSTR _strClassPath;
		const BSTR _strMethodName;
	
	public:
		WmiMethod() = delete;
		~WmiMethod();

		WmiMethod(IWbemClassObject*& arg_pMethod, const BSTR const arg_strClassPath, BSTR arg_strMethodName);

	public:
		WmiInstance<WmiMethod> CreateInstance() const;

		IWbemClassObject* GetObjectPtr() const;
		BSTR GetClassPath() const;
		BSTR GetMethodName() const;
	};
}

#endif