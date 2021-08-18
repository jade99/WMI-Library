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
		bool _bIsConnected = false;

		IWbemLocator* _pLocator = nullptr;
		IWbemServices* _pServices = nullptr;

		static SWmi s_WmiInstance;

	public:
		SWmi(const SWmi& wmi) = delete;

		static SWmi& Get();
		
		static IEnumWbemClassObject* Query(const std::wstring& arg_strQuery);
		static WmiClass GetWmiClass(const std::wstring& arg_strClassName);

		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAltObjectPath);
		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance);

		static void connect(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		static void disconnect();

	private:
		SWmi();
		~SWmi();

		IEnumWbemClassObject* QueryImpl(const std::wstring& arg_strQuery) const;
		WmiClass GetClassImpl(const std::wstring& arg_strClassName) const;

		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAltObjectPath) const;
		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance) const;

		bool ConnectImpl(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		void DisconnectImpl();
	};
}

#endif
