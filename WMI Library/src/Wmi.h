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

		static SWmi _s_WmiInstance;

	public:
		SWmi(const SWmi& wmi) = delete;
		
		static IEnumWbemClassObject* Query(const std::wstring& arg_strQuery) 
		{ return _s_WmiInstance.QueryImpl(arg_strQuery); };

		static WmiClass GetWmiClass(const std::wstring& arg_strClassName)
		{ return _s_WmiInstance.GetWmiClass(arg_strClassName); };


		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAltObjectPath)
		{ _s_WmiInstance.ExecMethodImpl(arg_wmiMethodInstance, arg_strAltObjectPath); };

		static void ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance)
		{ _s_WmiInstance.ExecMethodImpl(arg_wmiMethodInstance, arg_wmiMethodInstance.GetObjectPath()); };


		static bool Connect(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword)
		{  return _s_WmiInstance.ConnectImpl(arg_strWmiPath, arg_strUsername, arg_strPassword); };

		static void Disconnect()
		{ _s_WmiInstance.DisconnectImpl(); };

	private:
		SWmi();
		~SWmi();

		IEnumWbemClassObject* QueryImpl(const std::wstring& arg_strQuery) const;
		WmiClass GetClassImpl(const std::wstring& arg_strClassName) const;

		void ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strObjectPath) const;

		bool ConnectImpl(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword);
		void DisconnectImpl();
	};
}

#endif
