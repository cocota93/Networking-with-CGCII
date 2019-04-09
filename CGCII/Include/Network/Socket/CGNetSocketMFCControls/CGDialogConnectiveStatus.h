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
// CDialogAcceptorStatus
//
// 1. CDialogAcceptorStatus란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGDialogConnectiveStatus : public CDialog
{
	DECLARE_DYNAMIC(CCGDialogConnectiveStatus)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGDialogConnectiveStatus(CGNet::IO::Connective::Manager* p_pmangerAcceptor=nullptr, CWnd* pParent=nullptr);	// standard constructor
			CCGDialogConnectiveStatus(CGNet::IO::IConnective* p_pConnective, CWnd* pParent=nullptr);
	virtual ~CCGDialogConnectiveStatus();


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

public:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeConnective();
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CComboBox			m_comboUpdateInterval;
			CComboBox			m_comboConnective;
	static int					m_iUpdateInverval;
			CCGChildConnectableManager	m_ChildConnectableManager;

			CGPTR<CGNet::IO::Connective::Manager>	m_pmangerConnective;
			CGPTR<CGNet::IO::IConnective>	m_pConnective;
			LOCKABLE<>			m_csConnective;
			

			void				SetConnective(CGNet::IO::IConnective* p_pConnective);
			void				ResetConnectiveList();
			void				SetUpdateInterval(int p_iInterval);
			void				UpdateConnectiveStatus();

			void				SetViewStatus(bool p_bStatus);

public:
			BOOL				CreateModaless(CGNet::IO::Connective::Manager* p_pmangerAcceptor=nullptr, CWnd* p_pParent=nullptr);
			BOOL				CreateModaless(CGNet::IO::IConnective* p_pConnective=nullptr, CWnd* p_pParent=nullptr);
};
