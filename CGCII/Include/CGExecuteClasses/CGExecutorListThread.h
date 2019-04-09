//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

namespace CGExecutor
{

//-----------------------------------------------------------------------------
/**

 @class		CListThread
 @brief		CGExecutor::CList<TEXECUTOR>에 쓰레드를 합한 클래스이다.
 @todo		
 @ref		
 @details	\n
 CGExecutor::CList<TEXECUTOR>의 Execute()함수를 쓰레드풀에서 실행해준다.

*///-----------------------------------------------------------------------------
template <class TEXECUTOR=ICGExecutor>
class CListThread : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CList<TEXECUTOR>,
	public						NThread
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	//! @brief 기본생성자
	CListThread() : NThread()	{	SetObjectType(eOBJECT_TYPE::EXECUTOR_LIST_THREAD);}
	//! @brief 실행 간격의 설정과 함께 생성한다. @param _tickdiff '실행 간격'
			CListThread(bool _bEnableSkipFrame) : NThread(_bEnableSkipFrame)	{}
	//! @brief 객체이름과 함께 생성한다. @param _Name '객체 이름' @param _tickdiff '실행 간격'
			CListThread(_In_ const _CHAR* _Name, bool _bEnableSkipFrame=false) : NThread(_Name, _bEnableSkipFrame) {}
	//! @brief 객체이름과 함께 생성한다. @param _Name '객체 이름' @param _tickdiff '실행 간격'
			CListThread(_In_ const _CHAR_SUB* _Name, bool _bEnableSkipFrame=false) : NThread(_Name, _bEnableSkipFrame) {}
	virtual	~CListThread() {}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//!	@brief 실행자를 닫는다. @return true 성공 @return false 실패
	virtual	bool				Stop() override							{	CList<TEXECUTOR>::Stop(); NThread::Stop(); return true;}
};


}
