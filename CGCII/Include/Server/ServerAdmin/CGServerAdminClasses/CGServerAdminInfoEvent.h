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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
//
//
// 1. CGServerAdmin::CTCPAdmin란!
//    1) Administration Server와 연결되어 현재 Server의 각종 정보를 전송해주고
//       또 전달되어오는 명령을 처리하는 역할을 하는 Socket입니다.
//    2) 기본적인 Server Hardware상태/System Info등과 Traffiac 상황
//       Acceptor의 접속처리 상태, UDP Socket의 전송상태 등을 전송해 줍니다.
//    3) Event Manager와 연동하여 Event Manager에 상태를 전송하고 Administration 
//       Server로부터 전달받은 명령을 처리합니다.
//
//
// 2. CGServerAdmin::CTCPAdmin의 핵심! Function의 기능 설명
//
// 3. 주의 사항
//    * 특별한 주의 사항은 없음.
//
//
// ----------------------------------------------------------------------------
namespace CGServerAdmin
{

class CEvent
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CEvent();
	virtual ~CEvent();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
			EVENT_INFO			m_EventInfo;



};


}