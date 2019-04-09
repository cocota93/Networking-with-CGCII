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
// CGNet::IO::IConnective(연결 중계기)
//
// 1. IConnective은~
//    1) 많은 Connectable의 연결을 수행을 처리해주는 기능을 수행을 정의한다.
//    2) Connectable을 상속받은 객체를 연결을 해준다.
//    3) 대표적인 것으로 TCP의 Acceptor와 Connetor가 있다.
//       Connective::Acceptor는 연결을 받아 IConnectable을 연결시켜주는 것이고
//       Connective::Connector는 클라이언트로 연결을 시도해주는 것이다.
//    4) 이 클래스를 상속받아 생성된 객체는 모두 Connective::Manager에 등록되며
//       Connective::Manager에서 찾아 사용할 수 있다.
//    5) 이 클래스는 Nameable을 상속받아 기본적으로 이름을 가진다.
//
// 2. 가상 함수.
//    1) ProcessConnectiveConnect()
//       - 접속처리과 되는 과정을 정의하는 함수.
//
//    2) ProcessConnectiveDisconnect()
//       - 접속해제되는 과정을 수행하는 함수.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnective :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGNameable,							// (I) Nameable
	virtual public				ICGReferenceable,						// (I) Reference Count
	virtual public				CGNet::IO::Statistics::NConnective		// (@) 통계
{
// ****************************************************************************
// Constructor) 
// ----------------------------------------------------------------------------
public:
			IConnective()		{}
	virtual	~IConnective()		{}


// ****************************************************************************
// Interfaces) 
// ----------------------------------------------------------------------------
public:
	// 1) Status
	virtual	bool				IsEnable() const PURE;
			bool				IsDisable() const						{	return !IsEnable();}

	// 2) Start Object
			template <class TSTART>
			CGPTR<TSTART>		GetStartObject() const					{	return dynamic_pointer_cast<TSTART>(m_pobjectStart); }
			void				SetStartObject(ICGReferenceable* _pObj)	{	m_pobjectStart= _pObj;}

	// 3) On Complete
	virtual	void				ProcessConnectiveConnect(_In_ CGNet::IO::IConnectable* _pConnectable, _In_ uintptr_t _Return) PURE;
	virtual	void				ProcessConnectiveDisconnect(_In_ CGNet::IO::IConnectable* _pConnectable) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			void				RegisterConnective()					{	CGNet::IO::Connective::Manager::GetInstance()->Register(this);}
			void				UnregisterConnective()					{	CGNet::IO::Connective::Manager::GetInstance()->Unregister(this);}

protected:
			CGPTR<ICGReferenceable>	m_pobjectStart;
};


}
}