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
//-----------------------------------------------------------------------------
//
// CCGChildConnectiionInfoMini
//
// 1. CCGChildConnectiionInfo란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildConnectiveInfoMini : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildConnectiveInfoMini)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildConnectiveInfoMini(const CGNet::IO::Statistics::CONNECTIVE_INFO* p_pInfo=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildConnectiveInfoMini();


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

	afx_msg void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void				OnBnClickedCheckGraphConnect();
	afx_msg void				OnBnClickedCheckGraphDisconnect();

	afx_msg void				OnTimer(UINT_PTR nIDEvent);

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::Statistics::CONNECTIVE_INFO* p_pInfo=nullptr, CWnd* _pWnd=nullptr);

			void				Start();
			void				Stop();
			void				Ready();
			void				Close();

			void				SetConnectionInfo(CGNet::IO::Statistics::CONNECTIVE_INFO* p_pStatisticsConnection);
			void				SetConnectionInfo(CGNet::IO::IConnective* p_pConnective);

			void				UpdateConnectiveInfo();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CCGStaticGraph		m_graphTCPConnect;
			CSliderCtrl			m_sliderScaleConnection;

			TICK::time_point	m_tickLast;
			LONGLONG			m_countConnect;
			LONGLONG			m_countDisconnect;

			const CGNet::IO::Statistics::CONNECTIVE_INFO*	m_pstatistics;
			LOCKABLE<>			m_csStatistics;

			void				SetSocketStatus(CGNet::IO::IConnective* p_pConnective);
};
