//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               MFC Controls                                *
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
// CCGChildExecutorList
//
// 1. CCGChildExecutorList란!
//    1) Thread List를 출력하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGChildExecutorList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildExecutorList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildExecutorList(CGExecutor::Manager* _pExecutor=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildExecutorList();


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

private:
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnLvnItemchangedListExecutor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListExecutor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//afx_msg	void				OnBnClickedForceException();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGExecutor::Manager* _pExecutorManager=nullptr, CWnd* _pWnd=nullptr);

			void				SetExecutorManager(CGExecutor::Manager* _pExecutorManager);

			void				UpdateExecutorList();
			void				UpdateExecutorList(int _Index, TICK::time_point _tickNow);
			void				ClearExecutorList();

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listExecutor;

			CGPTR<CGExecutor::Manager>	m_pmanagerExecutor;
			LOCKABLE<>			m_csmanagerExecutor;

			BOOL				m_bEnableControl;
};
