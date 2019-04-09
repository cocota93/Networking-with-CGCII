//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
// CGNet::IO::Connective::Manager
//
// 1. CGNet::IO::Connective::Manager��~
//    1) ������ �뷮���� �����ϴ� AcceptorȤ�� Connector�� �����ϴ� �������̴�.
//       CGNet::IO::Connective::IAcceptor Ȥ�� CGNet::IO::Connective::Connect...�� 
//       ��ӹ޾� ������ ��ü�� �ڵ������� �� �����ڿ� ��ϵȴ�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connective
{

class Manager : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	virtual public				NCGDispatchable
{
// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:
			typedef	circular_list<CGNet::IO::IConnective*>::const_iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			Manager();
	virtual	~Manager();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Iterator��.
			ITERATOR			begin()									{	return m_listConnective.begin();}
			ITERATOR			end()									{	return m_listConnective.end();}
			int					GetCount() const;

								operator CGD::lockable&()				{	return m_listConnective;}

	// 2) Init Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(_In_ Manager* p_pInstance);
	static	void				ResetInstance();


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
private:
	// 1) Pool List.
			LOCKABLE<circular_list<CGNet::IO::IConnective*>>	m_listConnective;
			int					m_iConnectiveSerial;

			void				Register(_In_ CGNet::IO::IConnective* p_pConnective);
			void				Unregister(_In_ CGNet::IO::IConnective* p_pConnective);

	// 2) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

public:
	// 3) Destroy
			void				Destroy();

	// Friend) 
	friend	CGNet::IO::IConnective;
};


}
}
}