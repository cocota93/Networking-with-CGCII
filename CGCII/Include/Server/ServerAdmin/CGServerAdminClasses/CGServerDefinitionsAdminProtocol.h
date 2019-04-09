//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Admin Classes                            *
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
//-----------------------------------------------------------------
//
//
// Message Definitions
//
//
//-----------------------------------------------------------------
namespace CGMESSAGE
{
	namespace ADMIN
	{
		const uint32_t	SEND_HOST_INFO				 = BASE+  1;
		const uint32_t	SEND_HOST_SETTING			 = BASE+  2;
		const uint32_t	SEND_SYSTEM_INFO			 = BASE+  3;
		const uint32_t	SEND_SERVER_INFO			 = BASE+  4;
		const uint32_t	SEND_SERVER_SETTING			 = BASE+  5;
		const uint32_t	SEND_SERVICE_INFO			 = BASE+  6;
		const uint32_t	SEND_ADMINSERVER_ADDRESS	 = BASE+  7;
															  
		const uint32_t	SERVER_SETTING_LIST			 = BASE+ 11;
		const uint32_t	SERVER_SETTING_REGISTER		 = BASE+ 12;
		const uint32_t	SERVER_SETTING_UNREGISTER	 = BASE+ 13;
		const uint32_t	SERVER_SETTING_UPDATE		 = BASE+ 14;
		const uint32_t	SERVER_SETTING_REVERSION	 = BASE+ 15;
															  
		const uint32_t	HOST_LIST					 = BASE+ 21;
		const uint32_t	HOST_REGISTER				 = BASE+ 22;
		const uint32_t	HOST_UNREGISTER				 = BASE+ 23;
		const uint32_t	HOST_UPDATE					 = BASE+ 24;
		const uint32_t	HOST_CONNECTED				 = BASE+ 25;
		const uint32_t	HOST_DISCONNECTED			 = BASE+ 26;
															  
		const uint32_t	CLIENT_ENTER				 = BASE+ 31;
		const uint32_t	CLIENT_LEAVE				 = BASE+ 32;
		const uint32_t	CLIENT_UPDATE				 = BASE+ 33;
															  
		const uint32_t	REQUEST_VERSION_UPDATE		 = BASE+ 41;
															  
		const uint32_t	SERVER_LIST					 = BASE+ 51;
		const uint32_t	SERVER_ENTER				 = BASE+ 52;
		const uint32_t	SERVER_ENTER2				 = BASE+ 53;
		const uint32_t	SERVER_LEAVE				 = BASE+ 54;
		const uint32_t	SERVER_UPDATE				 = BASE+ 55;
		const uint32_t	SERVER_MOVE					 = BASE+ 56;
															  
		const uint32_t	SERVICE_STATE_UPDATE		 = BASE+ 61;
		const uint32_t	REQUEST_INIT_SERVICE		 = BASE+ 62;
		const uint32_t	REQUEST_DESTROY_SERVICE		 = BASE+ 63;
		const uint32_t	REQUEST_KILL_SERVICE		 = BASE+ 64;
		const uint32_t	REQUEST_START_SERVICE		 = BASE+ 65;
		const uint32_t	REQUEST_STOP_SERVICE		 = BASE+ 66;
		const uint32_t	REQUEST_PAUSE_SERVICE		 = BASE+ 67;
		const uint32_t	REQUEST_CONTINUE_SERVICE	 = BASE+ 68;
															  
		const uint32_t	SERVER_STATUS_UPDATE		 = BASE+ 71;
		const uint32_t	HOST_STATUS_UPDATE			 = BASE+ 72;
		const uint32_t	UPDATE_TRAFFIC_INFO			 = BASE+ 73;
															  
		const uint32_t	ADD_CONNECTIVE_INFO			 = BASE+ 81;
		const uint32_t	REMOVE_CONNECTIVE_INFO		 = BASE+ 82;
		const uint32_t	UPDATE_CONNECTIVE_INFO		 = BASE+ 83;
		const uint32_t	UPDATE_CONNECTIVE_STATUS	 = BASE+ 84;
															  
		const uint32_t	ADD_BINDER_INFO				 = BASE+ 91;
		const uint32_t	REMOVE_BINDER_INFO			 = BASE+ 92;
		const uint32_t	UPDATE_BINDER_INFO			 = BASE+ 93;
		const uint32_t	UPDATE_BINDER_STATUS		 = BASE+ 94;
															  
		const uint32_t	ADD_EVENT_INFO				 = BASE+ 101;
		const uint32_t	REMOVE_EVENT_INFO			 = BASE+ 102;
		const uint32_t	UPDATE_EVENT_INFO			 = BASE+ 103;
		const uint32_t	UPDATE_EVENT_STATUS			 = BASE+ 104;
															  
		const uint32_t	ADD_POOL_INFO				 = BASE+ 111;
		const uint32_t	REMOVE_POOL_INFO			 = BASE+ 112;
		const uint32_t	UPDATE_POOL_INFO			 = BASE+ 113;
		const uint32_t	UPDATE_POOL_STATUS			 = BASE+ 114;
															  
		const uint32_t	ADD_FACTORY_INFO			 = BASE+ 121;
		const uint32_t	REMOVE_FACTORY_INFO			 = BASE+ 122;
		const uint32_t	UPDATE_FACTORY_INFO			 = BASE+ 123;
		const uint32_t	UPDATE_FACTORY_STATUS		 = BASE+ 124;
															  
		const uint32_t	LOGIN_REQUEST				 = BASE+ 131;
		const uint32_t	LOGIN_ACCEPT				 = BASE+ 132;
		const uint32_t	LOGIN_REJECT				 = BASE+ 133;
															  
		const uint32_t	REQUEST_ACCEPTOR_INFO		 = BASE+ 141;
		const uint32_t	REQUEST_UDPSOCKET_INFO		 = BASE+ 142;
		const uint32_t	REQUEST_TRAFFICE_INFO		 = BASE+ 143;
															  
															  
		const uint32_t	REQUEST_CONNECT_TO_ADMIN	 = BASE+ 151;
															  
		const uint32_t	EXCEPTION_DUMP				 = BASE+ 161;
															  
		const uint32_t	SYSTEM_STATUS_INFO			 = BASE+ 171;
															  
		const uint32_t	UPDATE_SERVICE_STATUS		 = BASE+ 181;
															  
		const uint32_t	SEND_CONTROL_INFO			 = BASE+ 191;
															  
		const uint32_t	SERVICE_CONNECTED			 = BASE+ 201;
		const uint32_t	SERVICE_CERTIFIED			 = BASE+ 202;
		const uint32_t	SERVICE_DISCONNECTED		 = BASE+ 203;
		
		const uint32_t	REQUEST_LOG					 = BASE+ 211;

		const uint32_t	SUCCESS						 = BASE+ 221;
		const uint32_t	ERROR_						 = BASE+ 231;
	}
};


namespace CGServerAdmin
{

struct LOGIN_ACCEPT
{
public:
	SOCKADDR_CGNETWORK	sockaddrServer;

};

}