#pragma once

#ifndef _WMICLASS_H
#define _WMICLASS_H

#include "DLLDefinition.h"
#include "WmiObject.h"
#include "WmiMethod.h"

#include <string>
#include <WbemIdl.h>

namespace Jade
{
	class DLLDECL WmiClass : public WmiObject
	{
	public:
		WmiClass() = delete;
		~WmiClass();

		WmiClass(const std::wstring& arg_strClassName, IWbemServices* const& arg_pServices);

	public:
		WmiMethod GetMethod(const std::wstring& arg_strMethodName) const;
		WmiInstance<WmiClass> CreateInstance() const;
	};
}

#endif