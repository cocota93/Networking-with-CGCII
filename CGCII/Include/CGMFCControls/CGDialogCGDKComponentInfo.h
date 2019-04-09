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
#include "afxcmn.h"
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
class CGMFCCONTROL_EXT_CLASS CCGDialogCGDKComponentInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CCGDialogCGDKComponentInfo)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	CCGDialogCGDKComponentInfo(CWnd* pParent = nullptr);
	CCGDialogCGDKComponentInfo(const std::vector<CGDK::COMPONENT>& _vectorComponents, CWnd* pParent = nullptr);
	virtual ~CCGDialogCGDKComponentInfo();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CGDK_VERSION_INFO };
#endif

// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL				OnInitDialog();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateModaless(const std::vector<CGDK::COMPONENT>& _vectorComponents, CWnd* _pParent=nullptr);

			void				EnableControl(BOOL _bEnable=TRUE);




	DECLARE_MESSAGE_MAP()


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			const std::vector<CGDK::COMPONENT>*	m_pvectorComponents;

			CListCtrl			m_listctrlComponents;
			BOOL				m_bEnableControl;

			CRichEditCtrl		m_richExplanation1;
			CRichEditCtrl		m_richExplanation2;
			CRichEditCtrl		m_richExplanation3;
};
