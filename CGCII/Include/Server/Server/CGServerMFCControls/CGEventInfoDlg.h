//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server MFC Controls                            *
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
// CCGChildEventList
//
// 1. CCGChildEventList란!
//    1) Event Manager를  설정하여 Event List를 관리하는 관리자.
//    2) 
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERMFCCONTROL_EXT_CLASS CCGEventInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCGEventInfoDlg)


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGEventInfoDlg(ICGEventObject* _pEvent = nullptr);   // standard constructor
	virtual ~CCGEventInfoDlg();

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL				OnInitDialog();

	DECLARE_MESSAGE_MAP()

			void				SetEventInfo(ICGEventObject* _pEventObject);
			void				EnableEventContorls(bool _bEnable=true);

			void				UpdateEventInfo					();
			void				UpdateAsEvent_Once				(CGEvent::Object::COnce* _pEventObject);
			void				UpdateAsEvent_Iterration		(CGEvent::Object::CIteration* _pEventObject);
			void				UpdateAsEvent_StartEnd			(CGEvent::Object::CStartEnd* _pEventObject);
			void				UpdateAsEvent_StartIterrationEnd(CGEvent::Object::CStartIterationEnd* _pEventObject);
			void				UpdateAsEvent_Schedule			(CGEvent::Object::CSchedule* _pEventObject);
			void				UpdateAsEvent_ScheduleFunction	(CGEvent::Object::CScheduleFunction* _pEventObject);
			void				UpdateAsEvent_Custum			(ICGEventObject* _pEventObject);
			void				UpdateEventLog					(ICGEventObject* _pEventObject);

	afx_msg	void				OnTimer(UINT_PTR nIDEvent);
	afx_msg	void				OnBnClickedOk();
	afx_msg	void				OnBnClickedCancel();

public:
			CComboBox			m_comboEventType;
			CComboBox			m_comboEventSetter;
			CListCtrl			m_listctrlEventInfo;
			CCGListBoxLog		m_listctrlEventLog;

			CDateTimeCtrl		m_datatime_SETUP_YMD;
			CDateTimeCtrl		m_datatime_SETUP_MHS;

			CDateTimeCtrl		m_datatime_LastTry_YMD;
			CDateTimeCtrl		m_datatime_LastTry_MHS;

			CDateTimeCtrl		m_datatime_LastSucceeded_YMD;
			CDateTimeCtrl		m_datatime_LastSucceeded_MHS;

			CDateTimeCtrl		m_datatime_LastFailed_YMD;
			CDateTimeCtrl		m_datatime_LastFailed_MHS;

			LOCKABLE<CGPTR<ICGEventObject>>	m_pEventObject;
};
