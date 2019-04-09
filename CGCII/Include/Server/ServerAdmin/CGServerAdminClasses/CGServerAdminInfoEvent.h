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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
//
//
// 1. CGServerAdmin::CTCPAdmin��!
//    1) Administration Server�� ����Ǿ� ���� Server�� ���� ������ �������ְ�
//       �� ���޵Ǿ���� ����� ó���ϴ� ������ �ϴ� Socket�Դϴ�.
//    2) �⺻���� Server Hardware����/System Info��� Traffiac ��Ȳ
//       Acceptor�� ����ó�� ����, UDP Socket�� ���ۻ��� ���� ������ �ݴϴ�.
//    3) Event Manager�� �����Ͽ� Event Manager�� ���¸� �����ϰ� Administration 
//       Server�κ��� ���޹��� ����� ó���մϴ�.
//
//
// 2. CGServerAdmin::CTCPAdmin�� �ٽ�! Function�� ��� ����
//
// 3. ���� ����
//    * Ư���� ���� ������ ����.
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