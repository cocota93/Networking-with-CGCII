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
// CCGChildTrafficInfo
//
// 1. CCGChildTrafficInfo란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildTrafficInfo : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildTrafficInfo)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
		CCGChildTrafficInfo(const CGNet::IO::Statistics::TRAFFIC_INFO* p_pInfo=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildTrafficInfo();


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

public:
	afx_msg void				OnBnClickedCheckSend();
	afx_msg void				OnBnClickedCheckReceive();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(const CGNet::IO::Statistics::TRAFFIC_INFO* p_pInfo=nullptr, CWnd* _pWnd=nullptr);

			void				UpdateTrafficInfo();

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			TICK::time_point	m_tickLast;

			uint64_t			m_countSended;
			uint64_t			m_countReceived;
			uint64_t			m_countSendedByte;
			uint64_t			m_countReceivedByte;
			uint64_t			m_countSendIOCall;
			uint64_t			m_countReceiveIOCall;


			CCGStaticGraph		m_graphTraffic;
			CSliderCtrl			m_sliderScaleTraffic;

			const CGNet::IO::Statistics::TRAFFIC_INFO*	m_pstatistics;
};
