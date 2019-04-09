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
// CCGDialogReferenceStatus
//
// 1. CCGDialogReferenceStatus란!
//    1) Socket의 상태를 표시해 주는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGDialogReferenceStatus : public CDialog
{
	DECLARE_DYNAMIC(CCGDialogReferenceStatus)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGDialogReferenceStatus(ICGReferenceable* p_pRefernece=nullptr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCGDialogReferenceStatus();


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
			BOOL				CreateModaless(ICGReferenceable* p_pRefernece=nullptr, CWnd* _pParent=nullptr);

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CComboBox			m_comboUpdateInterval;
	static int					m_iUpdateInverval;
			CCGChildReferenceList m_ChildReferneceList;

			LOCKABLE<CGPTR<ICGReferenceable>>	m_pObject;

			void				SetObject(ICGReferenceable* p_pRefernece);
			void				ResetObject();

			void				SetUpdateInterval(int _iInterval);
			void				UpdateThreadStatus();

			void				SetViewStatus(bool _bStatus);
};
