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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CCGComboBoxConnective
//
// 1. CCGComboBoxConnective��!
//    1) Graph�� �׷��ִ� Library�̴�.
//    2) AddGraph�� ���� ���ϴ� ����ŭ�� Graph�� �������� �߰��� �����ϴ�.
//       - �̶� line�� ����� vertical scale�� �����Ѵ�.
//       - �̶� Graph Index�� ���� �� �ִ�.
//       - �� Graph Index�� Remove�� �ϸ� ���� ���� �ִ�.
//    3) Vertical/Horizontal Scale�� ������ �� �ִ�.
//    4) AppendData�� ���� ����Ÿ�� �߰��� �� �ִ�.
//    5) Scroll�Լ��� ���� ��µǴ� �׷����� �ű� �� �ִ�.
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


