// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "RTXCModuleInterface.tlb" no_namespace named_guids raw_interfaces_only

#include "mfcdual.h"

#include "RTXCMisc.h"
#include "RTXCAPIInc.h"

#define RTX_MODULE_IDENTIFIER_HELLO_RTX2						_T("Tencent.RTX.hello_rtx2")
#define RTX_MODULE_NAME_HELLO_RTX2							_T("a")
#define RTX_MODULE_DESCRIPTION_HELLO_RTX2						_T("b")
#define RTX_APP_NAME_HELLO_RTX2								_T("hello_rtx2App")

extern HMODULE g_hhello_rtx2Module;
inline CString Gethello_rtx2ModulePath()
{
	static CString strPath;

	if (strPath == _T(""))
	{
		ASSERT(g_hhello_rtx2Module != NULL);
		strPath = GetModulePath(g_hhello_rtx2Module);
	}

	return strPath;
}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

