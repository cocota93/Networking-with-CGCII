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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGExecutor
 @brief		������ ó���ϴ� Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ICGExecutable ��ü�� �޾� �� ��ü�� ProcessExecute()�Լ��� ȣ���� ������ ó�����ִ� Ŭ�����̴�.
 PostExecute()�Լ��� ICGExecutable�� ��û�� �޴� �Լ��̸� Execute()�Լ��� ���޹��� ICGExecutable ��ü�� ������ �����ϴ� �Լ��̴�.

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
	@brief	������ ��û�ϴ� �Լ�
	@param	_pExecutable	������ �����Լ�
	@param	_Para			����(ICGExecutable)�� ProcessExecute�Լ� ���� �Ѱ��� �Ķ���� ��
	@return	
	@todo
	@exception
	*/
	virtual	bool				ProcessPostExecute(_In_ ICGExecutable* _pExecutable, _In_ size_t _Para) PURE;

	// 2) 
	/**
	@brief	������ ó���ϴ� �Լ�
	@param	_tickdiff	�ִ� ���� ��� �ð�(�� �ð� ���� ó���� ���� ������ TIME_OUT���� �����Ѵ�.)
	@return	true		����
	@return	false		����
	*/
	virtual	bool				Execute(_In_ TICK::duration _tickdiff) PURE;

public:
	//!	@brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TEXECUTABLE>& _pExecutable, _In_ size_t _Para=0)	{	return ProcessPostExecute(_pExecutable.get(), _Para);}

	//!	@brief '���� ��ü'�� ������ ��û�Ѵ�. @param _pExecutable ������ '���� ��ü' @return true ���� @return false ����
	template <class TEXECUTABLE>
	typename std::enable_if<std::is_base_of<ICGExecutable, TEXECUTABLE>::value, bool>::type 
								PostExecute(_In_ TEXECUTABLE* _pExecutable, _In_ size_t _Para=0)				{	return ProcessPostExecute(_pExecutable, _Para);}

	//!	@brief ���� �Լ��� ������ ��û�Ѵ�. @param _pExecutable ������ �����Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para=0);

	//! @brief �Լ��� ���� ��û�Ѵ�. @param _pExecutable ������ �Լ� @return true ���� @return false ����
	template <class TFUNCTION>
	typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
								PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para=0);

	//! @brief ��� �Լ��� ���� ��û�Ѵ�. @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para=0);

	//! @brief ��� �Լ��� ���� ��û�Ѵ�. @param _Object ��� ��ü @param _pMemberFunction ������ ��� �Լ� @return true ���� @return false ����
	template <class TOBJECT>
	typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
								PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para=0);
};

// For Lambda Function) 
template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && !std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return ProcessPostExecute(pExecutable, _Para);
}

template <class TFUNCTION>
typename std::enable_if<!std::is_base_of<ICGExecutable, TFUNCTION>::value && std::is_function<typename std::remove_pointer<typename std::decay<TFUNCTION>::type>::type>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TFUNCTION _fFunction, _In_ size_t _Para)
{
	// 1) Lambda�� Executable�� �Ҵ�޴´�.
	auto	pExecutable = POOL_ALLOC<CGExecutable::CFunction<std::function<decltype(_fFunction())()>>>();

	// 2) Execute�Լ��� �����Ѵ�.
	pExecutable->SetFunction(_fFunction);

	// 3) Post�Ѵ�.
	return ProcessPostExecute(pExecutable, _Para);
}

// For Member Function) 
template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
ICGExecutor::PostExecute(_In_ TOBJECT* _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para)
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object);
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return ProcessPostExecute(pExecutable, _Para);
}

template <class TOBJECT>
typename std::enable_if<std::is_class<TOBJECT>::value, bool>::type 
ICGExecutor::PostExecute(_In_ const CGPTR<TOBJECT>& _Object, _In_ intptr_t(TOBJECT::*_pMemberFunction)(), _In_ size_t _Para)
{
	// 1) Member�Լ� Function�� Executable�� �Ҵ�޴´�.
	auto	pExecutable	 = POOL_ALLOC<CGExecutable::CFunctionMember<TOBJECT>>();

	// 2) Execute �Լ��� Object���� �����Ѵ�.
	pExecutable->SetObject(_Object.get());
	pExecutable->SetFunction(_pMemberFunction);

	// 3) Post�Ѵ�.
	return ProcessPostExecute(pExecutable, _Para);
}

