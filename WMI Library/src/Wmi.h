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

	public:
		SWmi(const SWmi& wmi) = delete;
		
		static IEnumWbemClassObject* Query(const std::wstring& arg_strQuery) 
		{ return Get().QueryImpl(arg_strQuery); };

		static WmiClass GetClass(const std::wstring& arg_strClassName)
		{ return Get().GetClassImpl(arg_strClassName); };


		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAltObjectPath)
		{ Get().ExecMethodImpl(arg_wmiMethodInstance, arg_strAltObjectPath); };

		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance)
		{ Get().ExecMethodImpl(arg_wmiMethodInstance, arg_wmiMethodInstance.GetObjectPath()); };


		static bool Connect(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword)
		{  return Get().ConnectImpl(arg_strWmiPath, arg_strUsername, arg_strPassword); };

		static void Disconnect()
		{ Get().DisconnectImpl(); };

	private:
		SWmi();
		~SWmi();

		static SWmi& Get()
		{ static SWmi instance; return instance; }

		IEnumWbemClassObject* QueryImpl(const std::wstring& arg_strQuery) const;
		WmiClass GetClassImpl(const std::wstring& arg_strClassName) const;

		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strObjectPath) const;

		bool ConnectImpl(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		void DisconnectImpl();
	};
}

#endif
