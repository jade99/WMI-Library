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
	class DLLDECL SWmi
	{
	private:
		IWbemLocator* _pLocator = nullptr;
		IWbemServices* _pServices = nullptr;

		static SWmi s_WmiInstance;

	public:
		SWmi(const SWmi& wmi) = delete;

		static SWmi& Get();
		
		static IEnumWbemClassObject* Query(const std::wstring& arg_strQuery);
		static WmiObject GetWmiObject(const std::wstring& arg_strObjectName);

		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAlternateClass);
		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance);

		static void connect(const std::wstring& arg_strNamespace, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		static void disconnect();

	private:
		SWmi();
		~SWmi();

		IEnumWbemClassObject* QueryImpl(const std::wstring& arg_strQuery) const;
		WmiObject GetWmiObjectImpl(const std::wstring& arg_strObjectName) const;

		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAlternateClass) const;
		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance) const;

		void connectImpl(const std::wstring& arg_strNamespace, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		void disconnectImpl();
	};
}

#endif
