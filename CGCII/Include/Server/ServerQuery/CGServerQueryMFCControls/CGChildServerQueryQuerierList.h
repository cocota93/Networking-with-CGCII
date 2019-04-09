//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Server DB MFC Controls                           *
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
// CCGChildEventList
//
// 1. CCGChildEventList란!
//    1) Event Manager를  설정하여 Event List를 관리하는 관리자.
//    2) 
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERQUERYMFCCONTROL_EXT_CLASS CCGChildQuerierList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildQuerierList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildQuerierList(CGServerQuery::ManagerQuerier* p_pQuerierManager=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildQuerierList();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGServerQuery::ManagerQuerier* p_pQuerierManager=nullptr, CWnd* p_pWnd=nullptr);

			void				SetDBQuerierManager(CGServerQuery::ManagerQuerier* p_pQuerierManager);
			CGPTR<CGServerQuery::ManagerQuerier>	GetDBQuerierManager() const		{	return m_pQuerierManager;}


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
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);
	afx_msg void				OnBnClickedOpen();
	afx_msg void				OnBnClickedOpenWithParam();
	afx_msg void				OnBnClickedClose();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listQuerier;

			CGPTR<CGServerQuery::ManagerQuerier>	m_pQuerierManager;
			LOCKABLE<>			m_csQuerierManager;

protected:
			void				UpdateQuerierManager();
			void				UpdateQuerier(int p_iIndex);
public:
};
