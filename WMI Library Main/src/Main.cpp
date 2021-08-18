#include "Wmi.h"
#include <iostream>
#include <atlbase.h>

using namespace Jade;

int main()
{
	if (!SWmi::Connect(L"\\\\.\\root\\virtualization\\v2", nullptr, nullptr)) return 1;

	const auto OWmiVSSD = SWmi::GetClass(L"Msvm_VirtualSystemSettingData");
	const auto OWmiVSSDInstance = OWmiVSSD.CreateInstance();

	CComVariant vtElementName;
	vtElementName.vt = VT_BSTR;
	vtElementName.bstrVal = CComBSTR(L"WMI Library Test");

	OWmiVSSDInstance.Put(L"ElementName", vtElementName);

	vtElementName.Clear();

	const auto OWmiVSMS = SWmi::GetClass(L"Msvm_VirtualSystemManagementService");
	const auto OWmiDefineMethod = OWmiVSMS.GetMethod(L"DefineSystem");
	const auto OWmiDefineInstance = OWmiDefineMethod.CreateInstance();

	CComVariant vtSystemSettings;
	vtSystemSettings.vt = VT_BSTR;
	vtSystemSettings.bstrVal = CComBSTR(OWmiVSSDInstance.GetObjectText().c_str());

	OWmiDefineInstance.Put(L"SystemSettings", vtSystemSettings);

	vtSystemSettings.Clear();

	vtElementName = OWmiVSSDInstance.Get(L"ElementName");
	//std::wcout << vtElementName.bstrVal << std::endl;

	vtSystemSettings = OWmiDefineInstance.Get(L"SystemSettings");
	//std::wcout << vtSystemSettings.bstrVal << std::endl;

	const auto pEnum = SWmi::Query(L"SELECT * FROM Msvm_VirtualSystemManagementService");

	ULONG ulReturn;
	CComPtr<IWbemClassObject> pVSMS;
	pEnum->Next(WBEM_INFINITE, 1, &pVSMS, &ulReturn);
	pEnum->Release();

	CComVariant vtPATH;
	pVSMS->Get(L"__PATH", 0, &vtPATH, nullptr, nullptr);

	SWmi::ExecMethod(OWmiDefineInstance, vtPATH.bstrVal);

	return 0;
}