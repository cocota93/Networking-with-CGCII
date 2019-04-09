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
// CCGChildConnectiveConnectorControl
//
// 1. CCGChildConnectiveConnectorControl란!
//    1) Connective Connector의 기본 조작용 콘트롤
// 
// 
//-----------------------------------------------------------------------------
class CGNETSOCKETMFCCONTROL_EXT_CLASS CCGChildConnectiveConnectorControl : public CCGChildDialog
{
	DECLARE_DYNAMIC(CCGChildConnectiveConnectorControl)

public:
			CCGChildConnectiveConnectorControl(CGNet::IO::Connective::Connector::NTCP* p_pconnectiveConnector=nullptr, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildConnectiveConnectorControl();


// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();

	afx_msg void				OnBnClickedButtonConnect1();
	afx_msg void				OnBnClickedButtonConnect10();
	afx_msg void				OnBnClickedButtonConnect100();
	afx_msg void				OnBnClickedButtonConnectMassive();
	afx_msg void				OnBnClickedButtonDisconnectAll();
	afx_msg void				OnBnClickedButtonDisconnect();

	afx_msg	LRESULT				OnCGMessageNotify(WPARAM p_wParam, LPARAM p_lParam);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			BOOL				CreateChild(CGNet::IO::Connective::Connector::NTCP* p_pConnectiveConnector=nullptr, CWnd* _pWnd=nullptr);

			void				ConnectN(int p_n);
			void				Disconnect();
			void				DisconnectAll();
			void				SetConnectiveConnector(CGNet::IO::Connective::Connector::NTCP* p_pConnectiveConnector);

			void				SetAddress(const wchar_t* _strAddress, int p_iPort);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			LOCKABLE<CGPTR<CGNet::IO::Connective::Connector::NTCP>>	m_pconnectiveConnector;
			std::wstring		m_strAddress;
			int					m_iPort;
};
