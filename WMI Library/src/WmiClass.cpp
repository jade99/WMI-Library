#include "WmiClass.h"

#include <iostream>
#include <atlbase.h>

namespace Jade
{
	WmiClass::WmiClass(const std::wstring& arg_strClassName, IWbemServices* const& arg_pServices)
		: WmiObject(arg_strClassName)
	{
		arg_pServices->GetObject(CComBSTR(arg_strClassName.c_str()), 0, nullptr, &_pObject, nullptr);

		RetrievePath();
		std::cout << "[WmiClass] created!" << std::endl;
	}

	WmiClass::~WmiClass()
	{
		_pObject->Release();
		std::cout << "[WmiClass] destroyed!" << std::endl;
	}

	WmiMethod WmiClass::GetMethod(const std::wstring& arg_strMethodName) const
	{
		return WmiMethod(arg_strMethodName, _pObject, GetObjectPath());
	}

	WmiInstance<WmiClass> WmiClass::CreateInstance() const
	{
		return WmiInstance<WmiClass>(*this);
	}
}