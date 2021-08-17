#pragma once

#ifndef _WMIINSTANCE_H
#define _WMIINSTACNE_H

#include <string>
#include <wbemidl.h>

namespace Jade
{
	template<typename T>
	class WmiInstance : public WmiObject
	{
	private:
		const T& _pMember;

	public:
		WmiInstance() = delete;
		~WmiInstance();

		WmiInstance(const T& arg_pMember);

	public:
		const T& GetMember() const;

		void Put(const std::wstring& arg_strPropertyName, VARIANT vtProp) const;
		VARIANT Get(const std::wstring& arg_strPropertyName) const;

		std::wstring GetObjectText() const;
	};
}

#include "WmiInstance.inl"

#endif
