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
#include "afxwin.h"
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
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGDialogConnectableStatus : public CDialog
{
	DECLARE_DYNAMIC(CCGDialogConnectableStatus)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGDialogConnectableStatus(CGNet::IO::IConnectable* _pConnectable=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGDialogConnectableStatus();


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
	afx_msg void				OnBnClickedButtonUpdate();
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();
	afx_msg void				OnBnClickedButtonDisconnect();
	afx_msg void				OnBnClickedButtonClose();
	afx_msg void				OnBnClickedButtonReferenceList();
	afx_msg void				OnCbnSelchangeComboUpdateInterval();
	afx_msg	void				OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg void				OnBnClickedCheckMessageSend();
	afx_msg void				OnBnClickedCheckMessageReceived();
	afx_msg void				OnBnClickedCheckBytesSend();
	afx_msg void				OnBnClickedCheckBytesReceive();
	afx_msg void				OnBnClickedCheckIOSend();
	afx_msg void				OnBnClickedCheckIOReceive();
	afx_msg void				OnBnClickedCheckIOSendEff();
	afx_msg void				OnBnClickedCheckIOReceiveEff();
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			TICK::time_point	m_tickLast;

			LONGLONG			m_countMessageSended;
			LONGLONG			m_countMessageReceived;
			LONGLONG			m_countMessageSendedByte;
			LONGLONG			m_countMessageReceivedByte;
			LONGLONG			m_countIOSended;
			LONGLONG			m_countIOReceived;

			CCGStaticGraph		m_graphMessage_Traffic;
			CSliderCtrl			m_sliderScaleMessage_Traffic;
			CCGStaticGraph		m_graphBytes_Traffic;
			CSliderCtrl			m_sliderScaleBytes_Traffic;
			CCGStaticGraph		m_graphIO;
			CSliderCtrl			m_sliderScaleIO;
			CCGStaticGraph		m_graphIO_Eff;
			CSliderCtrl			m_sliderScaleIO_Eff;

			CGPTR<CGNet::IO::IConnectable>	m_pConnectable;
			LOCKABLE<>			m_csConnectable;

			CComboBox			m_comboUpdateInterval;
	static	int					m_iUpdateInverval;

			void				SetConnectable(CGNet::IO::IConnectable* _pConnectable);
			void				SetUpdateInterval(int p_iInterval);
			void				UpdateConnectableStatus();

public:
			BOOL				CreateModaless(CGNet::IO::IConnectable* _pConnectable, CWnd* p_pParent);
};
