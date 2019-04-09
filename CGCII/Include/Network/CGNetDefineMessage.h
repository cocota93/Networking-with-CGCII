//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Network Base Classes                            *
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
//----------------------------------------------------------------------------
//  Disable Warnning
//
// 1) Warnning C4250 Disable
//    - C4250은 다중 상속의 virtual 상속된 interface에 대해서 어떤 것을 선택
//      했는지에 대해서 표시해주는 Warnning이다. 이 부분에 대한 표시가
//      필요 없으므로 이 부분은 Disable한다.
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// 1. CGMSG- Network용
//-----------------------------------------------------------------------------
struct CGNETMSG : public CGMSG_BUFFER
{
public:
	CGNETMSG() : CGMSG_BUFFER(CGMESSAGE::SYSTEM::MESSAGE)	{}
	CGNETMSG(uint32_t _message, void* _pSource=nullptr) : CGMSG_BUFFER(_message, _pSource)	{}
	CGNETMSG(uint32_t _message, void* _pSource, const SOCKADDR_CGNETWORK* _pSockAddr) : CGMSG_BUFFER(_message, _pSource), pSockAddr(_pSockAddr)	{}
	CGNETMSG(uint32_t _message, void* _pSource, const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGMSG_BUFFER(_message, _pSource, _Buffer), pSockAddr(_pSockAddr)	{}
	CGNETMSG(uint32_t _message, const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGMSG_BUFFER(_message, _Buffer), pSockAddr(_pSockAddr)	{}
	CGNETMSG(const CGMSG_BUFFER& _Msg, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGMSG_BUFFER(_Msg), pSockAddr(_pSockAddr)	{}
	CGNETMSG(const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGMSG_BUFFER(CGMESSAGE::SYSTEM::MESSAGE, _Buffer), pSockAddr(_pSockAddr)	{}
public:
	const SOCKADDR_CGNETWORK*	pSockAddr;
};

struct CGNETMSG_RESULT : public CGNETMSG
{
public:
	CGNETMSG_RESULT() : CGNETMSG(), Result(eOBJECT_RESULT::UNDEFINED)	{}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, uint32_t _message, void* _pSource=nullptr) : CGNETMSG(_message, _pSource), Result(_Result)	{}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, uint32_t _message, void* _pSource, const SOCKADDR_CGNETWORK* _pSockAddr) : CGNETMSG(_message, _pSource, _pSockAddr), Result(_Result) {}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, uint32_t _message, void* _pSource, const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGNETMSG(_message, _pSource, _Buffer, _pSockAddr), Result(_Result) {}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, uint32_t _message, const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGNETMSG(_message, _Buffer, _pSockAddr), Result(_Result) {}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, const CGMSG_BUFFER& _Msg, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGNETMSG(_Msg, _pSockAddr), Result(_Result) {}
	CGNETMSG_RESULT(eOBJECT_RESULT _Result, const CCGBuffer& _Buffer, const SOCKADDR_CGNETWORK* _pSockAddr=nullptr) : CGNETMSG(CGMESSAGE::SYSTEM::MESSAGE, _Buffer, _pSockAddr), Result(_Result) {}
public:
		eOBJECT_RESULT	Result;
};


#define	CGMESSAGE_TYPE_SUB_BUFFER_NETWORK				CGMESSAGE_TYPE_SUB(CGMESSAGE::SYSTEM::MESSAGE, static_cast<CGMSG_BUFFER&>(_Msg).Buffer.front<uint32_t>(4) & CGMESSAGE::SYSTEM::MASK)
#define	CGMESSAGE_TYPE_SUB_BUFFER_NETWORK_TYPE(type)	CGMESSAGE_TYPE_SUB(CGMESSAGE::SYSTEM::MESSAGE, static_cast<type>(static_cast<uint32_t>(((CGMSG_BUFFER&)_Msg).Buffer.front<type>(4)) & CGMESSAGE::SYSTEM::MASK))
