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
// CCGChildAcceptorList
//
// 1. CCGChildAcceptorList란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildAcceptorControl : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildAcceptorControl)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildAcceptorControl(CGNet::IO::Connective::IAcceptor* p_pAcceptor=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildAcceptorControl();


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
	afx_msg void				OnBnClickedCheckAcceptorStartStop();
	afx_msg void				OnBnClickedButtonAcceptorStatus();
	afx_msg void				OnBnClickedButtonAcceptorDisconnectAll();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::Connective::IAcceptor* p_pAcceptor=nullptr, CWnd* _pWnd=nullptr);

			void				SetDefaultPort(uint16_t _Port);
			void				SetConnective(CGNet::IO::IConnective* p_pConnective);
			void				SetAcceptor(CGNet::IO::Connective::IAcceptor* p_pAcceptor);
			void				UpdateAcceptorStatus();

			void				EnableControl(BOOL _bEnable=TRUE);

			CGPTR<CGNet::IO::Connective::IAcceptor>	GetAcceptor();

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CComboBox			m_comboBindAddress;
			uint16_t			m_wDefaultPort;

			CEdit				m_editBindPort;
			CButton				m_checkReady;
			CButton				m_buttonStatus;
			CButton				m_buttonDisconnectAll;

			CGPTR<CGNet::IO::Connective::IAcceptor>	m_pAcceptor;
			LOCKABLE<>			m_csAcceptor;
			eSOCKET_STATE		m_statusPre;

			BOOL				m_bEnableControl;

			bool				ListenAcceptor();
			
			CCGDialogConnectiveStatus	m_dlgConnectiveStatus;
};
