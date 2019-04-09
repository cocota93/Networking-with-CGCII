//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                MFC Controls                               *
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
// CDialogObjectFactoryStatus
//
// 1. CDialogObjectFactoryStatus란!
//    1) Object Factory의 각종 통계정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGDialogObjectFactoryStatus : public CDialog
{
	DECLARE_DYNAMIC(CCGDialogObjectFactoryStatus)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGDialogObjectFactoryStatus(CGFactory::Manager* p_pManager=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGDialogObjectFactoryStatus();


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
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg void				OnBnClickedButtonPrepare();
	afx_msg void				OnBnClickedButtonShrink();
	afx_msg void				OnBnClickedButtonEnableSustain();
	afx_msg void				OnBnClickedButtonDisableSustain();
	afx_msg void				OnBnClickedCheckEnableSustainManager();
	afx_msg void				OnBnClickedCheckVisibleMemoryBlock();
	afx_msg void				OnBnClickedCheckVisibleSystem();
	afx_msg void				OnBnClickedCheckVisibleUser();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateModaless(CGFactory::Manager* p_pManager=nullptr, CWnd* _pParent=nullptr);

			void				SetUpdateInterval(int _iInterval);

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			LOCKABLE<CGPTR<CGFactory::Manager>>	m_pManager;

			bool				m_bVisiableTypeStatus[16];

			CListCtrl			m_listObjectFactory;
			CImageList			m_imageObjectFactory;
			CComboBox			m_comboUpdateInterval;
	static	int					m_iUpdateInverval;
			CProgressCtrl		m_progressMemoryUsage;


			BOOL				m_bEnableControl;

			void				ClearFactoryList();
			void				UpdateFactoryList();
			void				UpdateFactoryStatus(int _Index);
};
