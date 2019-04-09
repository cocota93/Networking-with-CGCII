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
// CCGChildSchedulableList
//
// 1. CCGChildSchedulableList란!
//    1) Thread List를 출력하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGChildSchedulableList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildSchedulableList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildSchedulableList(CGExecutor::CSchedulable* _pexecutorSchedulable=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildSchedulableList();


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
	afx_msg void				OnLvnItemchangedListSchedulable(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnNMDblclkListThread(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg	void				OnBnClickedUnregisterSchedulable();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGExecutor::CSchedulable* _pexecutorSchedulable=nullptr, CWnd* _pWnd=nullptr);

			void				SetSchedulableList(CGExecutor::CSchedulable* _pexecutorSchedulable);

			void				UpdateSchedulableList();
			void				UpdateSchedulableList(int _Index, TICK::time_point _tickNow);
			void				ClearSchedulableList();

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listSchedulable;

			CGPTR<CGExecutor::CSchedulable>	m_pexecutorSchedulable;
			LOCKABLE<>			m_csmanagerThread;

			BOOL				m_bEnableControl;
};
