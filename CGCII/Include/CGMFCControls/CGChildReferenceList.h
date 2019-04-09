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
// CCGChildFactoryList
//
// 1. CCGChildFactoryList란!
//    1) Factory의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGChildReferenceList : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildReferenceList)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildReferenceList(ICGReferenceable* p_pRefernece=nullptr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCGChildReferenceList();


// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL				OnInitDialog();


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
	DECLARE_MESSAGE_MAP()

private:
	afx_msg	void				OnDestroy();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg void				OnLvnItemchangedListReference(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(ICGReferenceable* _Object=nullptr, CWnd* _pWnd=nullptr);

			void				SetObject(ICGReferenceable* _Object);

			void				UpdateReferenceList();
			void				ClearReferenceList();

			void				UpdateReference(int _Index);

			void				EnableControl(BOOL _bEnable=TRUE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CGPTR<ICGReferenceable> m_pObject;
			LOCKABLE<>			m_csObject;

			CListCtrl			m_listReference;

			BOOL				m_bEnableControl;
};
