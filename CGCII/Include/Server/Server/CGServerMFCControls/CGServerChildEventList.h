//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server MFC Controls                            *
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
class CGSERVERMFCCONTROL_EXT_CLASS CCGChildEventList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildEventList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildEventList(CGEvent::Manager* _pEventManager=nullptr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCGChildEventList();


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
	afx_msg void				OnBnClickedButtonDeleteEvent();
	afx_msg void				OnBnClickedButtonNewEvent();
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnBnClickedCheckDeleteDoneEvent();
	afx_msg void				OnBnClickedButtonSuspendEvent();
	afx_msg void				OnBnClickedButtonResumeEvent();
	afx_msg	void				OnNMDblclkListEvent(NMHDR* pNMHDR, LRESULT *pResult);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGEvent::Manager* _pEventManager=nullptr, CWnd* _pWnd=nullptr);

			void				SetEventManager(CGEvent::Manager* _pEventManager);
			CGPTR<CGEvent::Manager>	GetEventManager() const					{	return m_pEventManager;}

			void				UpdateEventManager();

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CListCtrl			m_listctrlEvent;

			CGPTR<CGEvent::Manager>	m_pEventManager;
			LOCKABLE<>			m_csEventManager;

			BOOL				m_bEnableControl;

protected:
			void				UpdateEvent(int p_iIndex);
};
