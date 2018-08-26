// MFCActiveX.cpp : Implementation of CMFCActiveXApp and DLL registration.

#include "stdafx.h"
#include "MFCActiveX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMFCActiveXApp theApp;

const GUID CDECL _tlid = { 0xCA8946A9, 0xF367, 0x44BB, { 0x9E, 0x44, 0xA0, 0x3F, 0x5E, 0x9D, 0x24, 0x31 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CMFCActiveXApp::InitInstance - DLL initialization

BOOL CMFCActiveXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CMFCActiveXApp::ExitInstance - DLL termination

int CMFCActiveXApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
