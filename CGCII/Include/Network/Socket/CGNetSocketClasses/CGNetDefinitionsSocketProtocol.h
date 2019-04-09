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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// Message Definitions
//
// ----------------------------------------------------------------------------
namespace CGMESSAGE
{
	namespace NETWORK
	{
		namespace SOCKET
		{
			const uint32_t	ACK						 = BASE |   1;
			const uint32_t	REQUEST_ACK				 = BASE |   2;
			const uint32_t	PING_REQ				 = BASE |   3;
			const uint32_t	PING_ACK				 = BASE |   4;
			const uint32_t	REQUEST_LOGIN			 = BASE |   5;
			const uint32_t	ACCEPT_LOGIN			 = BASE |   6;
			const uint32_t	REJECT_LOGIN			 = BASE |   7;

			const uint32_t	CONNECTIVE_REGISTER		 = BASE |   8;
			const uint32_t	CONNECTIVE_UNREGISTER	 = BASE |   9;
			const uint32_t	CONNECTIVE_ENABLE		 = BASE |  10;
			const uint32_t	CONNECTIVE_DISABLE		 = BASE |  11;

			const uint32_t	BINDER_REGISTER			 = BASE |  13;
			const uint32_t	BINDER_UNREGISTER		 = BASE |  14;

			const uint32_t	REMOTE_REQUEST			 = BASE |  17;
			const uint32_t	REMOTE_RESPONSE			 = BASE |  18;

			const uint32_t	ON_CONNECT				 = BASE |  19;
			const uint32_t	ON_FAILCONNECT			 = BASE |  20;
			const uint32_t	ON_DISCONNECT			 = BASE |  21;
		}
	}
}

#define	CGACCEPTOR_SET_CONNECTIVE			11
#define	CGACCEPTOR_OPEN_CONNECTIVE			12
#define	CGACCEPTOR_SET_CONNECTABLE			13
#define	CGACCEPTOR_OPEN_CONNECTABLE			14
#define	CGACCEPTOR_READY					15
#define	CGACCEPTOR_CLOSE					16
#define	CGACCEPTOR_START					17
#define	CGACCEPTOR_STOP						18
#define	CGBINDER_SET						19
#define	CGBINDER_OPEN						20

#define AF_INET_PREFER	(AF_MAX+2)
#define AF_INET6_PREFER	(AF_MAX+3)
