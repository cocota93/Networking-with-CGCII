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
// CCGChildConnectableManager
//
// 1. CCGChildConnectableManager란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildConnectableManager : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildConnectableManager)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildConnectableManager(CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildConnectableManager();


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
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg void				OnBnClickedButtonDisconnect();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonClearGhost();
	afx_msg void				OnLvnItemchangedListConnectable(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListConnectable(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::IConnectableManager* p_pConnectableManager=nullptr, CWnd* _pWnd=nullptr);

			void				SetConnectableManager(CGNet::IO::IConnectableManager* p_pConnectableManager);
			void				UpdateConnectableList();
			void				ClearConnectableList();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listConnectable;

			CGPTR<CGNet::IO::IConnectableManager>	m_pConnectableManager;
			LOCKABLE<>			m_csConnectableManager;

			void				EnableControls(bool p_bStatus);

			void				AddConnectable(int _Index, CGNet::IO::IConnectable* pConnectable);
			void				UpdateConnectable(int _Index);

			CGPTR<CGNet::IO::IConnectable>	VarifyConnectable(CGNet::IO::IConnectable* _pConnectable);
};
