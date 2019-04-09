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
// CCGChildConnectorControlEx
//
// 1. CCGChildConnectorControlEx란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildConnectorControlEx : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildConnectorControlEx)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildConnectorControlEx(CGNet::IO::IConnector* _pConnector=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildConnectorControlEx();


// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
private:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnBnClickedCheckConnect();
	afx_msg void				OnTimer(UINT_PTR nIDEvent);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::IConnector* _pConnector=nullptr, uint16_t _Port=10000, CWnd* _pWnd=nullptr);
			void				SetConnector(CGNet::IO::IConnector* _pConnector);

			void				UpdateConnectorStatus();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			CGPTR<CGNet::IO::IConnector> m_pConnector;
			LOCKABLE<>			m_csConnector;

			CComboBox			m_comboBindAddress;
			uint16_t			m_wDefaultPort;
			uint16_t			m_wBindPort;

			eSOCKET_STATE		m_eStatusPre;
};
