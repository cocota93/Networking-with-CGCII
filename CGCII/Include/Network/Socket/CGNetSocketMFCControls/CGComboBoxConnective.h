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
// ----------------------------------------------------------------------------
//
// CCGComboBoxConnective
//
// 1. CCGComboBoxConnective란!
//    1) Graph를 그려주는 Library이다.
//    2) AddGraph를 통해 원하는 수만큼의 Graph를 동적으로 추가가 가능하다.
//       - 이때 line의 색깔과 vertical scale을 설정한다.
//       - 이때 Graph Index를 얻을 수 있다.
//       - 이 Graph Index를 Remove를 하면 변할 수도 있다.
//    3) Vertical/Horizontal Scale을 설정할 수 있다.
//    4) AppendData를 통해 데이타를 추가할 수 있다.
//    5) Scroll함수를 통해 출력되는 그래프를 옮길 수 있다.
//
//
// ----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGComboBoxConnective : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public		CComboBox
{
	DECLARE_DYNAMIC(CCGComboBoxConnective)


// ****************************************************************************
// Constructor/Destructors
// ----------------------------------------------------------------------------
public:
			CCGComboBoxConnective();
	virtual ~CCGComboBoxConnective();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				SetConnectiveManager(CGNet::IO::Connective::Manager* p_pConnectiveManager);
			CGPTR<CGNet::IO::Connective::Manager>	GetConnectiveManager();
			void				UpdateConnectiveList();

			void				AddTargetWnd(CWnd* _pWnd);
			void				RemoveTargetWnd(CWnd* _pWnd);

			CGPTR<CGNet::IO::IConnective>	GetCurrentConnective();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			CGPTR<CGNet::IO::Connective::Manager>	m_pmangerConnective;
			LOCKABLE<>			m_csmangerConnective;


// ****************************************************************************
// MFC) 
// ----------------------------------------------------------------------------
protected:
	virtual BOOL				Create(uint32_t dwStyle, const RECT& rect, CWnd* pParentWnd, uint32_t nID);
	virtual BOOL				OnChildNotify(uint32_t message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnActivate(uint32_t nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg	void				OnDestroy();
	afx_msg void				OnCbnSelchange();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			circular_list<CWnd*> m_listWndTarget;
			LOCKABLE<>			m_cslistWndTarget;

			void				SendMessageToTarget(WPARAM p_dwMessage, LPARAM p_lParam);
};


