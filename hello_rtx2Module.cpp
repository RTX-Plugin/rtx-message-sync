// hello_rtx2Module.cpp : implementation file
//

#include "stdafx.h"
#include "string.h"
#include "hello_rtx2.h"
#include "hello_rtx2Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Chello_rtx2Module

IMPLEMENT_DYNCREATE(Chello_rtx2Module, CCmdTarget)
DELEGATE_DUAL_INTERFACE(Chello_rtx2Module, RTXCModule)


void debuglog(const char * msg)
{
	FILE * fp=fopen("d:\\rtx_log.txt","a+");
    time_t timer;
    char time_buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(fp,"%s: %s\n", time_buffer, msg);

	fclose(fp);
}

void debugloghex(const char * msg)
{
	FILE * fp=fopen("d:\\rtx_log.txt","a+");
    for(int i=0; i< strlen(msg); i++){  
        fprintf(fp, "%x ", msg[i]);
    }  
	fprintf(fp, "\n");
	fclose(fp);
}


Chello_rtx2Module::Chello_rtx2Module()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

Chello_rtx2Module::~Chello_rtx2Module()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void Chello_rtx2Module::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(Chello_rtx2Module, CCmdTarget)
	//{{AFX_MSG_MAP(Chello_rtx2Module)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Chello_rtx2Module, CCmdTarget)
	//{{AFX_DISPATCH_MAP(Chello_rtx2Module)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(Chello_rtx2Module, CCmdTarget)
	INTERFACE_PART(Chello_rtx2Module, IID_IRTXCModule, RTXCModule)
	INTERFACE_PART(Chello_rtx2Module, IID_IRTXCPlugin, RTXCModule)
END_INTERFACE_MAP()

// {9B1FF970-CC47-4434-B641-86049AABD776}
IMPLEMENT_OLECREATE(Chello_rtx2Module, "RTXC.hello_rtx2Module", 
	0x9b1ff970, 0xcc47, 0x4434, 0xb6, 0x41, 0x86, 0x4, 0x9a, 0xab, 0xd7, 0x76)

/////////////////////////////////////////////////////////////////////////////
// Chello_rtx2Module message handlers

HRESULT Chello_rtx2Module::get_Identifier(BSTR* pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
	
	*pVal = CString(RTX_MODULE_IDENTIFIER_HELLO_RTX2).AllocSysString();
	
	return S_OK;
}

HRESULT Chello_rtx2Module::get_Name(BSTR* pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
	
	*pVal = CString(RTX_MODULE_NAME_HELLO_RTX2).AllocSysString();
	
	return S_OK;
}

HRESULT Chello_rtx2Module::get_ModuleSite(IDispatch* *pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);
				
	*pVal = (IDispatch*)m_ptrModuleSite;
	
	if (*pVal != NULL)
	{
		(*pVal)->AddRef();
		
		return S_OK;
	}
				
	return E_FAIL;
}

HRESULT Chello_rtx2Module::OnLoad(IDispatch* RTXCModuleSite)
{
	RTX_CHECK_INVALIDARG_NULL(RTXCModuleSite);
	debuglog("OnLoad");
	RTX_TRY
	{
		m_ptrModuleSite = RTXCModuleSite;
		m_ptrRoot = m_ptrModuleSite->RTXCRoot;

		m_RootEventSink.HookEvent(evt_OnLoginResult, this, &Chello_rtx2Module::OnLoginResult);
		m_RootEventSink.HookEvent(evt_OnMsgCountChange, this, &Chello_rtx2Module::OnMsgCountChange);

		VERIFY(m_RootEventSink.Advise(m_ptrRoot));

		m_ptrPresence = m_ptrRoot->Presence;

		m_PresenceEventSink.HookEvent(evt_OnPresenceChange, this, &Chello_rtx2Module::OnPresenceChange);

		VERIFY(m_PresenceEventSink.Advise(m_ptrPresence));

		m_ModuleSiteEventSink.HookEvent(evt_OnDataReceived, this, &Chello_rtx2Module::OnDataReceived);
		m_ModuleSiteEventSink.HookEvent(evt_OnViewData, this, &Chello_rtx2Module::OnViewData);
		m_ModuleSiteEventSink.HookEvent(evt_OnSendDataResult, this, &Chello_rtx2Module::OnSendDataResult);
		
		VERIFY(m_ModuleSiteEventSink.Advise(m_ptrModuleSite));	

		return S_OK;
	}
	RTX_CATCH_ALL(return E_FAIL)
}

HRESULT Chello_rtx2Module::OnAccountChange()
{
	return S_OK;
}

HRESULT Chello_rtx2Module::OnInvoke(VARIANT Receiver, 
								  VARIANT Parameter, VARIANT Extra, VARIANT* Result)
{
	return S_OK;
}

HRESULT Chello_rtx2Module::OnUnload(enum RTXC_MODULE_UNLOAD_REASON Reason)
{
	VERIFY(m_RootEventSink.Unadvise());
	m_RootEventSink.UnhookEvent(evt_OnLoginResult, this, &Chello_rtx2Module::OnLoginResult);

	VERIFY(m_PresenceEventSink.Unadvise());
	m_PresenceEventSink.UnhookEvent(evt_OnPresenceChange, this, &Chello_rtx2Module::OnPresenceChange);
	VERIFY(m_ModuleSiteEventSink.Unadvise());
	m_ModuleSiteEventSink.UnhookEvent(evt_OnDataReceived, this, &Chello_rtx2Module::OnDataReceived);
	m_ModuleSiteEventSink.UnhookEvent(evt_OnViewData, this, &Chello_rtx2Module::OnViewData);
	m_ModuleSiteEventSink.UnhookEvent(evt_OnSendDataResult, this, &Chello_rtx2Module::OnSendDataResult);

	return S_OK;
}

HRESULT Chello_rtx2Module::get_Info(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal)
{
	RTX_CHECK_INVALIDARG_NULL(pVal);

	*pVal = NULL;

	if (Field == RTXC_PLUGIN_INFO_FIELD_DESCRIPTION)
	{
		*pVal = CString(RTX_MODULE_DESCRIPTION_HELLO_RTX2).AllocSysString();
	}

	return S_OK;
}

void Chello_rtx2Module::OnLoginResult(RTXC_LOGIN_RESULT Result)
{
	debuglog("OnLoginResult.");
}

void Chello_rtx2Module::OnPresenceChange(BSTR Account, RTX_PRESENCE RTXPresence)
{

}

void Chello_rtx2Module::OnDataReceived(LPCTSTR Key)
{
	debuglog("OnDataReceived");
}

void Chello_rtx2Module::OnViewData(LPCTSTR Key)
{
	debuglog("OnViewData");
}

void Chello_rtx2Module::OnSendDataResult(RTXC_MODULE_SEND_DATA_RESULT Result, const VARIANT* Extra)
{
	debuglog("OnSendDataResult");
}

#include   <Winsock2.h>

HRESULT Chello_rtx2Module::OnMsgCountChange(long Count, VARIANT_BOOL Forbid, 
							  LPCTSTR Identifier, LPCTSTR Key, BSTR Sender)
{
	debuglog("OnMsgCountChange");
	debuglog("sender");
	char* lpszText2 = _com_util::ConvertBSTRToString(Sender);
	debugloghex(lpszText2);
	delete[] lpszText2;

	//
	char ip[32];
	int port;

	FILE * fp=fopen("d:\\rtxsync.txt","a+");
	if (fp==NULL) return S_OK;

	fscanf(fp,"%s %d",ip,&port);
	fclose(fp);	

	WORD   wVersionRequested;
	WSADATA   wsaData;
	int   err;

	wVersionRequested   =   MAKEWORD(   1,   1   );
	err   =   WSAStartup(   wVersionRequested,   &wsaData   );
	if   (   err   !=   0   )   {return S_OK;}
	if   (   LOBYTE(   wsaData.wVersion   )   !=   1   ||
               HIBYTE(   wsaData.wVersion   )   !=   1   )   {
		WSACleanup(   );
		return S_OK;  
	}

	SOCKET   sockClient=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN   addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr( ip);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(port);
	//connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

	char buf[20];
	sprintf(buf,"%d",Count);
	sendto(sockClient, buf,strlen(buf),0, (SOCKADDR*)&addrSrv,sizeof(addrSrv) );
	closesocket(sockClient);
	WSACleanup(); 

	return S_OK;
}
