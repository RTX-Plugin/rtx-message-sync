#pragma once

// hello_rtx2Module.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Chello_rtx2Module command target

class Chello_rtx2Module : public CCmdTarget
{
	DECLARE_DYNCREATE(Chello_rtx2Module)
	DECLARE_EVENT_RECEIVER(Chello_rtx2Module)

	Chello_rtx2Module();           // protected constructor used by dynamic creation

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Chello_rtx2Module)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Chello_rtx2Module();

	// Generated message map functions
	//{{AFX_MSG(Chello_rtx2Module)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	BEGIN_DUAL_INTERFACE_PART(RTXCModule, IRTXCPlugin)
		STDMETHOD(get_Identifier)(BSTR *pVal)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
				
			return pThis->get_Identifier(pVal);
		}

		STDMETHOD(get_Name)(BSTR *pVal)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
				
			return pThis->get_Name(pVal);
		}

		STDMETHOD(get_ModuleSite)(IDispatch* *pVal)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
		
			return pThis->get_ModuleSite(pVal);
		}

		STDMETHOD(OnLoad)(IDispatch* RTXCModuleSite)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
			
			return pThis->OnLoad(RTXCModuleSite);
		}

		STDMETHOD(OnAccountChange)()
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
				
			return pThis->OnAccountChange();
		}
		
		STDMETHOD(OnInvoke)(VARIANT Receiver, VARIANT Parameter, VARIANT Extra, VARIANT* Result)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
				
			return pThis->OnInvoke(Receiver, Parameter, Extra, Result);
		}
		
		STDMETHOD(OnUnload)(enum RTXC_MODULE_UNLOAD_REASON Reason)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)
				
			return pThis->OnUnload(Reason);
		}

		STDMETHOD(get_Info)(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal)
		{
			METHOD_PROLOGUE(Chello_rtx2Module, RTXCModule)

			return pThis->get_Info(Field, pVal);
		}
	END_DUAL_INTERFACE_PART(RTXCModule)	
	
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(Chello_rtx2Module)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(Chello_rtx2Module)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	IRTXCRootPtr m_ptrRoot;
	IRTXCModuleSitePtr m_ptrModuleSite;
	IRTXCPresencePtr m_ptrPresence;

	CRTXCEventSinkRoot m_RootEventSink;

	void OnLoginResult(RTXC_LOGIN_RESULT Result);

	CRTXCEventSinkPresence m_PresenceEventSink;

	void OnPresenceChange(BSTR Account, RTX_PRESENCE RTXPresence);

	CRTXCEventSinkModuleSite m_ModuleSiteEventSink;

	void OnDataReceived(LPCTSTR Key);
	void OnViewData(LPCTSTR Key);
	void OnSendDataResult(RTXC_MODULE_SEND_DATA_RESULT Result, const VARIANT* Extra);

	HRESULT get_Identifier(BSTR* pVal);
	HRESULT get_Name(BSTR* pVal);

	HRESULT get_ModuleSite(IDispatch* *pVal);

	HRESULT OnLoad(IDispatch* RTXCModuleSite);
	
	HRESULT OnAccountChange();

	HRESULT OnInvoke(VARIANT Receiver, VARIANT Parameter, VARIANT Extra, VARIANT* Result);
	
	HRESULT OnUnload(enum RTXC_MODULE_UNLOAD_REASON Reason);

	HRESULT get_Info(enum RTXC_PLUGIN_INFO_FIELD Field, BSTR *pVal);
	HRESULT OnMsgCountChange(long Count, VARIANT_BOOL Forbid, 
							  LPCTSTR Identifier, LPCTSTR Key, BSTR Sender);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
