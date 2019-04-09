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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGNet::IO::Binder::Manager
//
// 1. CGNet::IO::Binder::Manager는~
//    모든 Bind되는 Socket을 관리하는 Manager이다.
//    CGNet::IO::IBinder를 상속받아 Bind한 객체는 이 Manager에 등록되어 관린된다.
//    일반적으로 CGNet::IO::IBinder를 상속받는 객체는 접속이 필요한 Client TCP Socket,
//    혹은 UDP Socket들이다.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Binder
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
			typedef	circular_list<CGNet::IO::IBinder*>::const_iterator	ITERATOR;


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
	// 1) Iterator용.
			ITERATOR			begin()									{	return m_listBinder.begin();}
			ITERATOR			end()									{	return m_listBinder.end();}
			int					GetCount() const;

								operator CGD::lockable&()				{	return m_listBinder;}

	// 2) Init Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	static	void				SetInstance(_In_ Manager* p_pInstance);
	static	void				ResetInstance();


// ****************************************************************************
// Implementations) 
// ----------------------------------------------------------------------------
private:
	// 1) Pool List.
			LOCKABLE<circular_list<CGNet::IO::IBinder*>>	m_listBinder;
private:
	// 2) Register/Unregister
			void				Register(_In_ CGNet::IO::IBinder* _pBinder);
			void				Unregister(_In_ CGNet::IO::IBinder* _pBinder);

	// 3) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

public:
	// 4) Destroy
			void				Destroy();

	// Friend)
	friend	CGNet::IO::IBinder;
};


}
}
}