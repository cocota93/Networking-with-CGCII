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
// CCGDialogConnectableStatus
//
// 1. CCGDialogConnectableStatus란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGDialogThreadStatus : public CDialog
{
	DECLARE_DYNAMIC(CCGDialogThreadStatus)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGDialogThreadStatus(CGAPI::ManagerThread* _pThreadManager=nullptr, CGExecutor::Manager* _pExecutorManager=nullptr, CGExecutor::Default* _pDefaultExecutor=nullptr, CWnd* _pParent = nullptr);   // standard constructor
	virtual ~CCGDialogThreadStatus();


// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateModaless(CGAPI::ManagerThread* _pThreadManager=nullptr, CGExecutor::Manager* _pExecutorManager=nullptr, CGExecutor::Default* _pDefaultExecutor=nullptr, CWnd* _pParent=nullptr);

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT _nState, CWnd* _pWndOther, BOOL _bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR _nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);
	afx_msg void				OnTcnSelchangeTabMenu(NMHDR* _pNMHDR, LRESULT *pResult);
	afx_msg void				OnTcnSelchangingTabMenu(NMHDR* _pNMHDR, LRESULT *pResult);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CComboBox			m_comboUpdateInterval;
	static int					m_iUpdateInverval;

			CTabCtrl			m_tabMenu;

			CCGChildThreadList	m_ChildThreadList;
			CCGChildExecutorList m_ChildExecutorList;
			CCGChildSchedulableList m_ChildSchedulableList;

			LOCKABLE<CGPTR<CGAPI::ManagerThread>>	m_pmanagerThead;
			CGPTR<CGExecutor::Manager>				m_pmanagerExecutor;
			CGExecutor::Default*					m_pDefaultExecutor;

			void				SetManager(CGAPI::ManagerThread* _pThreadManager, CGExecutor::Manager* _pExecutorManager, CGExecutor::Default* _pDefaultExecutor);
			void				ResetThreadList();
			void				SetUpdateInterval(int _iInterval);
			void				UpdateThreadStatus();

			void				SetViewStatus(bool _bStatus);
};
