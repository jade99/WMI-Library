#include "Wmi.h"
#include <iostream>
#include <atlbase.h>

using namespace Jade;

int main()
{
	const Wmi OWmi(L"\\\\.\\root\\virtualization\\v2", nullptr, nullptr);
	const auto OWmiVSMS = OWmi.GetClass(L"Msvm_VirtualSystemManagementService");

	std::wcout << OWmiVSMS.GetPath() << std::endl;

	const auto OWmiVSSD = OWmi.GetClass(L"Msvm_VirtualSystemSettingData");
	const auto OWmiVSSDInstance = OWmiVSSD.CreateInstance();

	CComVariant vtElementName;
	vtElementName.vt = VT_BSTR;
	vtElementName.bstrVal = CComBSTR("WMI Library Test");

	OWmiVSSDInstance.Put(L"ElementName", vtElementName);

	const auto OWmiDefineMethod = OWmiVSMS.GetMethod(L"DefineSystem");
	const auto OWmiDefineInstance = OWmiDefineMethod.CreateInstance();

	CComVariant vtSystemSettings;
	vtSystemSettings.vt = VT_BSTR;
	vtSystemSettings.bstrVal = OWmiVSSDInstance.GetXML();

	OWmiDefineInstance.Put(L"SystemSettings", vtSystemSettings);

	OWmi.ExecMethod(OWmiDefineInstance);

	return 0;
}