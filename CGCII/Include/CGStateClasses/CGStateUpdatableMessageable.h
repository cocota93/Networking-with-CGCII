//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               State Classes                               *
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
// CGFSM::State::CMessagable
//
// 1. CGFSM::State::CMessagable�̶�...?
//    1) FSM�� State�� Message�� �޾� ó���ϴ� State�� �ǹ��Ѵ�.
//    2) ���� State Ŭ������ ICGMessageable�� ��ӹ��� Ŭ�����̴�.
//
// 2. CGNetPacketMap�� �ٽ�! Function�� ��� ����
//    1) ó���Լ��� �⺻���� I/Oó���� ���� ó���Լ����̴�.
//					���������� ���� I/O�� ó���ϱ� ���� �ʿ��� �Լ��鿡 ���ؼ� ������ ���̴�.
//    2) �����Լ���	Socket�� �� ������ �����ϴ� �Լ����̴�.
//    3) User�Լ���	�����Ǹ� ���� ������� �Լ��̴�. ���α׷��Ӱ� �� �κе��� ������
//					������ Socket�� ���ӿ� �°� ����� �ȴ�.
//
// 3. ���� ����
//  Run�� �׻� ���� �ð����� ������ ���� I/O�� ���� ó���� �ݵ��� ���־�� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
namespace CGState
{

template <class _TSTATE_ID=_STRING>
class CUpdatableMessagable :
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	public						CUpdatable<_TSTATE_ID>,					// (@) StateProcess
	virtual public				ICGMessageable							// (I) ICGMessageable
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	_TSTATE_ID			TSTATE_ID;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CUpdatableMessagable()										{}
			CUpdatableMessagable(const TSTATE_ID& _idState) : CUpdatable<TSTATE_ID>(_idState)	{}
	virtual	~CUpdatableMessagable()										{}
};


}
