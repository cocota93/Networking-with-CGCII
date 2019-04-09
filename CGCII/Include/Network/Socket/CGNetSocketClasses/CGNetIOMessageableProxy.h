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
/*!
* @class NProxy
*
* @ingroup CGNet::IO::Messageable
*
* @brief ���޹��� �޽����� Proxy�� ������ ��ü�� �����Ͽ� ó���ϴ� Ŭ����
*
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
// CGNet::IO::Messageable::
//
// 1. CGNet::IO::Messageable::NProxy��!
//    1) ���� Message�� �ٸ� Messageable�� �����ϴ� Packetable�̴�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Messageable
{

template <class TPROXY>
class NProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGMessageable							//     Messageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NProxy()													{}
	virtual	~NProxy()													{}


// ****************************************************************************
// public)
// ----------------------------------------------------------------------------
public:
			void				SetProxy(_In_ TPROXY* _pProxy)			{ LOCK(m_pProxy) m_pProxy=_pProxy; }
			CGPTR<TPROXY>		GetProxy() const						{ LOCK(m_pProxy) return m_pProxy; }

			LOCKABLE<>&			GetLock()								{ return m_pProxy;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

private:
			LOCKABLE<CGPTR<TPROXY>> m_pProxy;
};

template <class TPROXY>
int NProxy<TPROXY>::ProcessMessage(CGMSG& _Msg)
{
	auto	pProxy	 = GetProxy();

	// Check) m_pMessageable�� nullptr�̸� ������.
	RETURN_IF(pProxy.empty(), 0);

	// 1) ProcessMessage()�Լ��� ȣ���Ѵ�.
	return pProxy->ProcessMessage(_Msg);
}



}
}
}
