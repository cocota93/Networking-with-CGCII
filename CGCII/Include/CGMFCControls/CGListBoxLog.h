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
class CGMFCCONTROL_EXT_CLASS CCGListBoxLog : public CListBox
{
	DECLARE_DYNAMIC(CCGListBoxLog)

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGListBoxLog();
	virtual ~CCGListBoxLog();


// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:
	struct ITEM_LOG : virtual public ICGReferenceable
	{
	public:
				_CHAR		strHead[24];
				COLORREF	colorText;
				BOOL		bBold;
				CGPTR<CGLOG_RECORD>	pLogRecord;
	};


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			int					AddString(ITEM_LOG* _pItemLog);
			int					AddString(CGLOG_RECORD* _pLogRecord, COLORREF _colorText, BOOL _bBold);
			int					AddString(const TIME::SYSTEM::time_point& _timeLog, LPCTSTR _strMessage, COLORREF _colorText, BOOL _bBold);
			int					AddString(LPCTSTR _strHead, LPCTSTR _strMessage, COLORREF _colorText, BOOL _bBold);

			bool				UpdateString(int _index, const TIME::SYSTEM::time_point& _timeLog, LPCTSTR _lpszMessage, COLORREF _colorText, BOOL _bBold);
			bool				UpdateString(int _index, LPCTSTR _strHead, LPCTSTR _lpszMessage, COLORREF _colorText, BOOL _bBold);
			void				DeleteItemAfter(int _index);

// ****************************************************************************
// MFC) Virtual Functions
// ----------------------------------------------------------------------------
protected:
	virtual BOOL				PreCreateWindow(CREATESTRUCT& cs);
	virtual void				DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void				DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	virtual void				MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);


// ****************************************************************************
// MFC) Windows Message
// ----------------------------------------------------------------------------
protected:
	DECLARE_MESSAGE_MAP()


// ****************************************************************************
// Implementation
// ----------------------------------------------------------------------------
public:

};

