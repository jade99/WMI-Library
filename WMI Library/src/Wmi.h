#pragma once

#ifndef _WMI_H
#define _WMI_H

#pragma comment(lib, "wbemuuid.lib")

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
		IEnumWbemClassObject* Query(const std::wstring& arg_strQuery) const;

		void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAlternateClass) const;
		void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance) const;

		WmiClass GetClass(const std::wstring& arg_strClassName) const;
	};
}

#endif
