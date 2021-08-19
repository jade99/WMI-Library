#pragma once

#ifndef _WMI_H
#define _WMI_H

#include "DLLDefinition.h"
#include "WmiClass.h"

#include <string>
#include <wbemidl.h>

namespace Jade
{
	class DLLDECL Wmi
	{
	private:
		IWbemLocator* _pLocator = nullptr;
		IWbemServices* _pServices = nullptr;

	public:
		Wmi() = delete;
		~Wmi();

		Wmi(const std::wstring& arg_strWmiPath, const wchar_t* arg_strUsername, const wchar_t* arg_strPassword);

	public:
		WmiClass GetClass(const std::wstring& arg_strClassName) const;
		void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance) const;
		IEnumWbemClassObject* Query(const std::wstring& arg_strQuery) const;
	};
}

#endif
