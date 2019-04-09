//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                  MFC Controls for Network Socket Classes                  *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CCGChildBinderControl dialog
//
// 1. CCGChildBinderControl란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildBinderControl : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildBinderControl)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildBinderControl(CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildBinderControl();


// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedCheckBind();
	afx_msg void				OnBnClickedButtonBinderStatus();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::IBinder* _pBinder=nullptr, CWnd* _pWnd=nullptr);

			void				SetDefaultPort(uint16_t _Port);
			void				SetBinder(CGNet::IO::IBinder* _pBinder);
			void				UpdateBinderStatus();

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CComboBox			m_comboBindAddress;
			uint16_t			m_wDefaultPort;

			CButton				m_checkBind;
			CButton				m_buttonStatus;

			CGPTR<CGNet::IO::IBinder>	m_pBinder;
			LOCKABLE<>			m_csBinder;

			bool				Bind();
};
