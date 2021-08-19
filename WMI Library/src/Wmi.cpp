#include "Wmi.h"

#include <iostream>
#include <stdexcept>
#include <atlbase.h>

namespace Jade
{
	Wmi::Wmi(const std::wstring& arg_strWmiPath, const wchar_t* arg_strUsername, const wchar_t* arg_strPassowrd)
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
			NULL,
			nullptr
		);

		if (FAILED(hres))
		{
			CoUninitialize();
			throw std::runtime_error("Could not initalize COM security");
		}

		hres = CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&_pLocator);

		if (FAILED(hres))
		{
			CoUninitialize();
			throw std::runtime_error("Could not create COM instance");
		}

		hres = _pLocator->ConnectServer(
			CComBSTR(arg_strWmiPath.c_str()),
			CComBSTR(arg_strUsername),
			CComBSTR(arg_strPassowrd),
			NULL,
			0,
			NULL,
			nullptr,
			&_pServices
		);

		if (FAILED(hres))
		{
			_pLocator->Release();
			CoUninitialize();
			throw(std::runtime_error("Could not connect to COM"));
		}

		std::cout << "[Wmi] constructed!" << std::endl;
	}


	Wmi::~Wmi()
	{
		_pServices->Release();
		_pLocator->Release();
		CoUninitialize();

		std::cout << "[Wmi] destroyed!" << std::endl;
	}

	WmiClass Wmi::GetClass(const std::wstring& arg_strClassName) const
	{
		return WmiClass(arg_strClassName, _pServices);
	}

	void Wmi::ExecMethod(const WmiInstance<WmiMethod>& arg_wmiMethodInstance) const
	{
		const auto hres = _pServices->ExecMethod(
			CComBSTR(arg_wmiMethodInstance.GetMember()->GetClassPath().c_str()),
			CComBSTR(arg_wmiMethodInstance.GetMember()->GetMethodName().c_str()),
			0, nullptr,
			arg_wmiMethodInstance.GetInstancePtr(),
			nullptr,
			nullptr
		);

		std::cout << "Error 0x" << std::hex << hres << std::endl;
	}

	IEnumWbemClassObject* Wmi::Query(const std::wstring& arg_strQuery) const
	{
		IEnumWbemClassObject* pEnum = nullptr;
		_pServices->ExecQuery(CComBSTR(L"WQL"), CComBSTR(arg_strQuery.c_str()), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &pEnum);

		return pEnum;
	}
}