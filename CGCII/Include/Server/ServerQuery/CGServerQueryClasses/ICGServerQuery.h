//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Query Classes                            *
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
// ICGServerQuery
//
// 1. ICGServerQuery란!
//    1) 단위 Query의 요청 정보와 결과 정보를 가지는 객체
//
//-----------------------------------------------------------------------------
class ICGServerQuery : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGServerQuery() : m_dwAttribute(0)							{	m_hEvent=CreateEvent(NULL, FALSE, FALSE, NULL);}
	virtual ~ICGServerQuery()											{	SAFE_CLOSEHANDLE(m_hEvent);}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Requestor
			void				SetRequestor(ICGServerQueryRequestor* _pR){	m_pRequestor=_pR;}
			void				ResetRequestor()						{	m_pRequestor.reset();}
			CGPTR<ICGServerQueryRequestor> GetRequestor() const			{	return m_pRequestor;}

	// 2) Event
			HANDLE				GetEvent() const						{	return m_hEvent;}

	// 3) Attribute
			void				SetAttribute(uint32_t _dwAttribute)		{	m_dwAttribute=_dwAttribute;}
			uint32_t			GetAttribute() const					{	return m_dwAttribute;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Requestor
			CGPTR<ICGServerQueryRequestor>	m_pRequestor;

	// 2) 속성 (Dummy 속성이다.)
			uint32_t			m_dwAttribute;

	// 2) Event
	//    - Session을 얻어오는 과정에서 필요에 따라 사용된다.
			HANDLE				m_hEvent;
};
