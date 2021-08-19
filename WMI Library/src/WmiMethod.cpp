#include "WmiMethod.h"

#include <iostream>

namespace Jade
{
	WmiMethod::WmiMethod(
		const std::wstring& arg_strMethodName,
		IWbemClassObject* const& arg_pClass,
		const std::wstring& arg_strClassPath
	) : WmiObject(arg_strMethodName)
	{
		arg_pClass->GetMethod(CComBSTR(arg_strMethodName.c_str()), 0, &_pObject, nullptr);
		RetrievePath();

		const auto length = arg_strClassPath.size() + 1;
		_strClassPath = new wchar_t[length];
		wcscpy_s(_strClassPath, length, arg_strClassPath.c_str());

		std::cout << "[WmiMethod] created!" << std::endl;
	}

	WmiMethod::~WmiMethod()
	{
		_pObject->Release();
		std::cout << "[WmiMethod] destroyed!" << std::endl;
	}

	WmiInstance<WmiMethod> WmiMethod::CreateInstance() const
	{
		return WmiInstance<WmiMethod>(*this);
	}
}