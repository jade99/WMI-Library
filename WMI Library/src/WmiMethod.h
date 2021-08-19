#pragma once

#ifndef _WMIMETHOD_H
#define _WMIMETHOD_H

#include "DLLDefinition.h"
#include "WmiObject.h"
#include "WmiInstance.h"

#include <wbemidl.h>

namespace Jade
{
	class DLLDECL WmiMethod : public WmiObject
	{
	private:
		wchar_t* _strClassPath = nullptr;

	public:
		WmiMethod() = delete;
		~WmiMethod();

		WmiMethod(
			const std::wstring& arg_strMethodName, 
			IWbemClassObject* const& arg_pClass, 
			const std::wstring& arg_strClassPath
		);

	public:
		WmiInstance<WmiMethod> CreateInstance() const;
	};
}

#endif