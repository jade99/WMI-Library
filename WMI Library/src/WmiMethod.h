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
		const std::wstring _strClassPath;
		const std::wstring _strMethodName;
	
	public:
		WmiMethod() = delete;
		~WmiMethod();

		WmiMethod(
			const std::wstring arg_strMethodName, 
			IWbemClassObject* const& arg_pClass, 
			const std::wstring arg_strClassPath
		);

	public:
		WmiInstance<WmiMethod> CreateInstance() const;

		IWbemClassObject* GetObjectPtr() const;
		std::wstring GetClassPath() const;
		std::wstring GetMethodName() const;
	};
}

#endif