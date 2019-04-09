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
// CCGChildConnectiveList
//
// 1. CCGChildConnectiveList란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildConnectiveList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildConnectiveList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildConnectiveList(CGNet::IO::Connective::Manager* p_pConnectiveManager=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildConnectiveList();


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
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnLvnItemchangedListConnective(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListConnective(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::Connective::Manager* p_pConnectiveManager=nullptr, CWnd* _pWnd=nullptr);

			void				SetConnectiveManager(CGNet::IO::Connective::Manager* p_pConnectiveManager);

			void				UpdateConnectiveList();
			void				UpdateConnective(int _Index);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listConnective;

			CGPTR<CGNet::IO::Connective::Manager>	m_pmanagerConnective;
			LOCKABLE<>			m_csmanagerConnective;

			void				SetConnectiveStatus();
			bool				ListenAcceptor();

			CGPTR<CGNet::IO::IConnective>	VarifyConnective(CGNet::IO::IConnective* p_pConnective);
};
