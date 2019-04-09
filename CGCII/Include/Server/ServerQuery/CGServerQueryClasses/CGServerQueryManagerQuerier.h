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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::ManagerQuerier
//
// 1. CGServerQuery::ManagerQuerier��!
//    1) DB Querier�� ����Ͽ� �����ϰ� �ִ� ������ ��ü�̴�.
//    2) �̴� ���������� �����ϰ� �����Ǵ� �̱��� ��ü�̴�.
//    3) Querier ��ü�� ��ϰ� ��������� ���������� �ڵ������� ó���ȴ�.
//    4) ManagerQuerier�� ��� ������ Querier�� ���ų� ������ �� ���ȴ�.
//
// 2. CGServerQuery::ManagerQuerier�� �ٽ�! Function�� ��� ����
//    1) Iteration ó��
//	     for loop���� ����Ͽ� ��� Querier ��ü�� �����ϰ��� �Ҷ� ���Ǵ� ������
//       ������ �Ϲ����� stl�� container�� �����ϰ� begin()�� end() �Լ��� ����Ѵ�.
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
	// 1) Iterator��.
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