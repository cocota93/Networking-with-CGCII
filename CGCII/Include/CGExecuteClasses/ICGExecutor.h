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
//-----------------------------------------------------------------------------
/**

 @class		ICGExecutor
 @brief		실행을 처리하는 클래스이다.
 @todo		
 @ref		
 @details	\n
 ICGExecutable 객체를 받아 그 객체의 ProcessExecute()함수를 호출해 실행을 처리해주는 클래스이다.
 PostExecute()함수는 ICGExecutable의 요청을 받는 함수이며 Execute()함수는 전달받은 ICGExecutable 객체의 실행을 정의하는 함수이다.

*///-----------------------------------------------------------------------------
class ICGExecutor : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGObjectIdentifiable,
	virtual public				ICGStartable
{
// ****************************************************************************
// Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGExecutor()		{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	/**
	@brief	실행을 요청하는 함수
	@param	_pExecutable	실행할 펑터함수
	@param	_Para			펑터(ICGExecutable)의 ProcessExecute함수 실행 넘겨질 파라메터 값
	@return	
	@todo
	@exception
	*/
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para) PURE;

	// 2) 
	/**
	@brief	실행을 처리하는 함수
	@param	_tickdiff	최대 실행 대기 시간(이 시간 내에 처리가 되지 않으면 TIME_OUT으로 리턴한다.)
	@return	true		성공
	@return	false		실패
	*/
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) PURE;

public:
	//!	@brief '실행 객체'의 실행을 요청한다. @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TEXECUTABLE>& _pExecutable, _In_ size_t _Para=0)	{	return ProcessPostExecute(_pExecutable.get(), _Para);}

	//!	@brief '실행 객체'의 실행을 요청한다. @param _pExecutable 실행할 '실행 객체' @return true 성공 @return false 실패
	template <class TEXECUTABLE>
	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TEXECUTABLE* _pExecutable, _In_ size_t _Para=0)				{	return ProcessPostExecute(_pExecutable, _Para);}

	//!	@brief 람다 함수의 실행을 요청한다. @param _pExecutable 실행할 람다함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para=0);

	//! @brief 함수의 실행 요청한다. @param _pExecutable 실행할 함수 @return true 성공 @return false 실패
	template <class TFUNCTION>
	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para=0);

	//! @brief 멤버 함수의 실행 요청한다. @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para=0);

	//! @brief 멤버 함수의 실행 요청한다. @param _Object 대상 객체 @param _pMemberFunction 실행할 멤버 함수 @return true 성공 @return false 실패
	template <class TOBJECT>
	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para=0);
};

// For Lambda Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return ProcessPostExecute(pExecutable, _Para);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para)
{
	// 1) Lambda용 Executable을 할당받는다.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute함수를 설정한다.
	pExecutable->SetFunction(_fFunction);

	// 3) Post한다.
	return ProcessPostExecute(pExecutable, _Para);
}

// For Member Function) 
template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para)
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return ProcessPostExecute(pExecutable, _Para);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
ICGExecutor::PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para)
{
	// 1) Member함수 Function용 Executable을 할당받는다.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute 함수와 Object를를 설정한다.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post한다.
	return ProcessPostExecute(pExecutable, _Para);
}

