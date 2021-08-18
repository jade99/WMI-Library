#include "Wmi.h"

#include <iostream>
#include <stdexcept>
#include <atlbase.h>

namespace Jade
{
	SWmi::SWmi()
	{
		auto hres = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		if (FAILED(hres))
		{
			throw std::runtime_error("Could not initialize COM");
		}

		hres = CoInitializeSecurity(
			NULL,
			-1,
			nullptr,
			nullptr,
			RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			nullptr,
			EOAC_NONE,
			nullptr
		);

		if (FAILED(hres))
		{
			CoUninitialize();
			throw std::runtime_error("Could not initalize COM security");
		}

		std::cout << "[Wmi] created!" << std::endl;
	}


	SWmi::~SWmi()
	{
		if (_bIsConnected)
		{
			DisconnectImpl();
		}

		CoUninitialize();

		std::cout << "[Wmi] destroyed!" << std::endl;
	}

	IEnumWbemClassObject* SWmi::QueryImpl(const std::wstring& arg_strQuery) const
	{
		IEnumWbemClassObject* pEnum = nullptr;
		_pServices->ExecQuery(CComBSTR(L"WQL"), CComBSTR(arg_strQuery.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnum);

		return pEnum;
	}

	WmiClass SWmi::GetClassImpl(const std::wstring& arg_strObjectName) const
	{
		return WmiClass(arg_strObjectName, _pServices);
	}

	void SWmi::ExecMethodImpl(const WmiInstance<WmiMethod>& arg_wmiMethodInstance, const std::wstring& arg_strAltObjectPath) const
	{
		const auto hres = _pServices->ExecMethod(
			CComBSTR(arg_strAltObjectPath.c_str()),
			CComBSTR(arg_wmiMethodInstance.GetObjectName().c_str()),
			0, nullptr,
			arg_wmiMethodInstance.GetObjectPtr(),
			nullptr,
			nullptr
		);

		std::cout << "[Wmi::ExecMethod] Return: 0x" << std::hex << hres << std::endl;
	}

	bool SWmi::ConnectImpl(const std::wstring& arg_strWmiPath, const wchar_t* const arg_strUsername, const wchar_t* const arg_strPassword)
	{
		if (_bIsConnected)
		{
			DisconnectImpl();
		}

		auto hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&_pLocator);
		if (FAILED(hres)) return false;

		hres = _pLocator->ConnectServer(
			CComBSTR(arg_strWmiPath.c_str()),
			CComBSTR(arg_strUsername),
			CComBSTR(arg_strPassword),
			NULL,
			0,
			NULL,
			nullptr,
			&_pServices
		);

		if (FAILED(hres)) { _pLocator->Release(); return false; }

		hres = CoSetProxyBlanket(
			_pServices,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHZ_NONE,
			nullptr,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			nullptr,
			EOAC_NONE
		);

		if (FAILED(hres)) { DisconnectImpl(); return false; }

		_bIsConnected = true;

		return true;
	}

	void SWmi::DisconnectImpl()
	{
		_pServices->Release();
		_pLocator->Release();
	}
}