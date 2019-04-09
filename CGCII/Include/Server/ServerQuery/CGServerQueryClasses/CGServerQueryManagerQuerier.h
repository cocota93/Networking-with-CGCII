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
// CGServerQuery::ManagerQuerier
//
// 1. CGServerQuery::ManagerQuerier란!
//    1) DB Querier를 등록하여 관리하고 있는 관리자 객체이다.
//    2) 이는 내부적으로 유일하게 생성되는 싱글톤 객체이다.
//    3) Querier 객체의 등록과 등록해제는 내부적으로 자동적으로 처리된다.
//    4) ManagerQuerier의 경우 생성된 Querier를 얻어내거나 관리할 때 사용된다.
//
// 2. CGServerQuery::ManagerQuerier의 핵심! Function의 기능 설명
//    1) Iteration 처리
//	     for loop문을 사용하여 모든 Querier 객체에 접근하고자 할때 사용되는 것으로
//       형식은 일반적인 stl의 container와 유사하게 begin()과 end() 함수를 사용한다.
//
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{

class ManagerQuerier :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	virtual public				NCGDispatchable,
	virtual public				ICGMessageable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
			typedef	circular_list<ICGServerQuerier*>::const_iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			ManagerQuerier();
	virtual ~ManagerQuerier();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Iterator용.
			ITERATOR			begin()									{	return m_listQuerier.begin();}
			ITERATOR			end()									{	return m_listQuerier.end();}
			int					GetCount()								{	return (int)m_listQuerier.size();}

								operator CGD::lockable&()				{	return m_listQuerier;}


	// 2) Init Instance/RunExecutor
	static	CGPTR<ManagerQuerier> GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(ManagerQuerier* p_pInstance);
	static	void				ResetInstance();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Pool List.
			LOCKABLE<circular_list<ICGServerQuerier*>>	m_listQuerier;
			int					m_iDBQuerierSerial;
	// 2) Register/Unregister
			void				Register(ICGServerQuerier* p_pQuerier);
			void				Unregister(ICGServerQuerier* p_pQuerier);

	// 3) Instance
	static	CGOWN<ManagerQuerier> m_pInstance;
	static	void				InitInstance();
	static	LOCKABLE<>			m_csCreate;

public:
	// 4) Destroy
			void				Destroy();

	// 5) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	// Friends)
	friend	ICGServerQuerier;
};


}