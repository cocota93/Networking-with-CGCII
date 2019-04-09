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
// CCGChildLogView
//
// 1. CCGChildLogView란!
//    1) Socket의 상태정보를 표시하는 Dialog
//    2) DoModal()로 띄우는 것으로 작성하였다.
// 
// 
//-----------------------------------------------------------------------------
class CGSERVERMFCCONTROL_EXT_CLASS CCGChildLogView : 
	public						CCGChildDialog,
	public						ICGLog
{
	DECLARE_DYNAMIC(CCGChildLogView)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGChildLogView(CWnd* pParent=nullptr);   // standard constructor
	virtual ~CCGChildLogView();


// ****************************************************************************
// Definitions
// ----------------------------------------------------------------------------
	struct LOGLIST_INFO
	{
	public:
		TCHAR				stName[MAX_NAME_LENGTH];
		CCGListBoxLog*		plistLog;
		CGPTR<ICGLogFilter>	pLogFilter;

		int					iCount;

		circular_list<CGMSG_LOG>	queueString[2];
		circular_list<CGMSG_LOG>*	pqueueStringStack;
		circular_list<CGMSG_LOG>*	pqueueStringProcess;
	public:
		LOGLIST_INFO() : pqueueStringStack(&queueString[0]), pqueueStringProcess(&queueString[1])	{}
	};


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

public:
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg	void				OnDestroy();
	afx_msg void				OnLbnSelchangeListLog();
	afx_msg void				OnLbnDblclkListLog();
	afx_msg void				OnLbnErrspaceListLog();
	afx_msg void				OnLbnSelcancelListLog();
	afx_msg void				OnNMThemeChangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg	LRESULT				OnCGMessageNotify(WPARAM _wParam, LPARAM _lParam);
	afx_msg	LRESULT				OnAddString(WPARAM _wParam, LPARAM _lParam);
	afx_msg void				OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnTcnSelchangingTabInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void				OnBnClickedNewLog();
	afx_msg void				OnBnClickedEditFilter();
	afx_msg void				OnBnClickedLogClose();
	afx_msg void				OnBnClickedLogSave();
	afx_msg void				OnBnClickedLogSaveSelected();



// ****************************************************************************
// CGMessage) 
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessMessage(CGMSG& _Msg);

			int					OnMessage_Log(CGMSG_LOG& _Msg);


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) 생성한다.
			BOOL				CreateChild(const void* _pInfo=nullptr, CWnd* _pWnd=nullptr);

	// 2) Log를 추가한다.
			void				AddString(CCGListBoxLog* _lParam, CCGListBoxLog::ITEM_LOG* _pItem);

	// 3) Log를 추가/삭제
			void				AddLogList(const TCHAR* _strName, ICGLogFilter* _pLogFilter, bool _bFocus=false);
			void				RemoveLogList(const TCHAR* _strName);
			void				RemoveLogList(int _iTab);
			void				SetLogFilter(const TCHAR* _strName, ICGLogFilter* _pLogFilter);
			void				SetLogFilter(int iTab, ICGLogFilter* _pLogFilter);
			void				ResetLogFilter(const TCHAR* _strName);
			void				ResetLogFilter(int iTab);

	// 4) Text Color
			void				SetTextColor(eLOG_TYPE _LogType, COLORREF p_refColor, BOOL p_bBold=FALSE)	{	m_rgbText[static_cast<int>(_LogType)]=p_refColor; m_bBold[static_cast<int>(_LogType)]=p_bBold;}
			COLORREF			GetTextColor(eLOG_TYPE _LogType)	{	return m_rgbText[static_cast<int>(_LogType)];}
			COLORREF			GetTextBold(eLOG_TYPE _LogType)		{	return m_bBold[static_cast<int>(_LogType)];}

	// 5) Trace Function
	virtual	void				ProcessLog(CGLOG_RECORD* _pLogRecord) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) MFC Control
			CTabCtrl			m_tabLog;
			CCGListBoxLog		m_listLog;
			COLORREF			m_colorTextLast;
			BOOL				m_bBoldLast;

			struct ITEM_LOG
			{
			public:
				CGPTR<CGLOG_RECORD>		pLogRecord;
				CGPTR<CCGListBoxLog::ITEM_LOG>	pItem;

			public:
				ITEM_LOG(CGLOG_RECORD* _pLogRecord, CCGListBoxLog::ITEM_LOG* _pItem) : pLogRecord(_pLogRecord), pItem(_pItem)	{}
			};

			struct QUEUE_LOG
			{
			public:
				circular_list<ITEM_LOG>		pqueue;
				int							count[static_cast<int>(eLOG_TYPE::MAX)];
			public:
				QUEUE_LOG();
				void	ResetCount();
			};

			LOCKABLE<>			m_csqueueString;
			QUEUE_LOG			m_queueString[2];
			QUEUE_LOG*			m_pqueueStringStack;
			QUEUE_LOG*			m_pqueueStringProcess;

	// 2) LogList List
			LOCKABLE<vector<LOGLIST_INFO>> m_vectorLogList;

	// Statistics) 
			int					m_countLog[static_cast<int>(eLOG_TYPE::MAX)];
			COLORREF			m_rgbText[static_cast<int>(eLOG_TYPE::MAX)];
			BOOL				m_bBold[static_cast<int>(eLOG_TYPE::MAX)];

protected:
			void				ShowList(int _iTab, int p_iCmdShow);
			void				ProcessAddString(ITEM_LOG& _ItemLog);

			void				EnableRedraw();
			void				DisableRedraw();

	virtual void				ProcessDispose() override	{}
};
