#include "Wmi.h"
#include <iostream>
#include <atlbase.h>

using namespace Jade;

int main()
{
	const Wmi OWmi(L"\\\\.\\root\\virtualization\\v2", nullptr, nullptr);

	const auto OWmiVSSD = OWmi.GetClass(L"Msvm_VirtualSystemSettingData");
	const auto OWmiVSSDInstance = OWmiVSSD.CreateInstance();

	CComVariant vtElementName;
	vtElementName.vt = VT_BSTR;
	vtElementName.bstrVal = CComBSTR(L"WMI Library Test");

	OWmiVSSDInstance.Put(L"ElementName", vtElementName);

	vtElementName.Clear();

	const auto OWmiVSMS = OWmi.GetClass(L"Msvm_VirtualSystemManagementService");

	const auto pEnum = OWmi.Query(L"SELECT * FROM Msvm_VirtualSystemManagementService");
	
	ULONG ulReturn;
	CComPtr<IWbemClassObject> pVSMS;
	pEnum->Next(WBEM_INFINITE, 1, &pVSMS, &ulReturn);
	pEnum->Release();

	CComVariant pPATH;
	pVSMS->Get(L"__PATH", 0, &pPATH, nullptr, nullptr);

	const auto OWmiDefineMethod = OWmiVSMS.GetMethod(L"DefineSystem", pPATH.bstrVal);
	const auto OWmiDefineInstance = OWmiDefineMethod.CreateInstance();

	CComVariant vtSystemSettings;
	vtSystemSettings.vt = VT_BSTR;
	vtSystemSettings.bstrVal = OWmiVSSDInstance.GetXML();

	OWmiDefineInstance.Put(L"SystemSettings", vtSystemSettings);

	vtSystemSettings.Clear();

	vtElementName = OWmiVSSDInstance.Get(L"ElementName");
	//std::wcout << vtElementName.bstrVal << std::endl;

	vtSystemSettings = OWmiDefineInstance.Get(L"SystemSettings");
	//std::wcout << vtSystemSettings.bstrVal << std::endl;

	OWmi.ExecMethod(OWmiDefineInstance);

	return 0;
}