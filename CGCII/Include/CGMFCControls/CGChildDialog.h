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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CCGChildDialog
//
// 1. CCGChildDialog¶õ!
//    1) 
//    2) 
// 
// 
//-----------------------------------------------------------------------------
#define	ORIGIN_CENTER_X	0x01
#define	ORIGIN_LEFT		0x02
#define	ORIGIN_RIGHT	0x03
#define	ORIGIN_FRONT	0x04
#define	ORIGIN_REAR		0x05

#define	ORIGIN_CENTER_Y	0x10
#define	ORIGIN_TOP		0x20
#define	ORIGIN_BOTTOM	0x30
#define	ORIGIN_UPON		0x40
#define	ORIGIN_BELOW	0x50

class CGMFCCONTROL_EXT_CLASS CCGChildDialog : public CGDIALOG
{
	DECLARE_DYNAMIC(CCGChildDialog)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildDialog(UINT nIDTemplate, CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildDialog();


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void				OnBnClickedOk();
	afx_msg void				OnBnClickedCancel();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				MoveToCenter(CWnd* _pWnd, int p_iOffX=0, int p_iOffY=0);
			void				Move(int p_iOffX, int p_iOffY);
			void				Move(int p_iOffX, int p_iOffY, int p_iOrigin, CWnd* _pWnd);

			void				Resize(int p_iOffX, int p_iOffY);

			void				AddTargetWnd(CWnd* _pWnd);
			void				RemoveTargetWnd(CWnd* _pWnd);

			void				SetUpdateInterval(int _iInterval);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			circular_list<CWnd*> m_listWndTarget;
			void				SendMessageToTarget(WPARAM _Message, LPARAM _lParam);



};
