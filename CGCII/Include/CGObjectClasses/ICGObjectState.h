//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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
/**

 @class		ICGObjectState
 @brief		���� �Ӽ��� ������ �����ϴ� �Ӽ��� ���� �������̽� Ŭ����
 @todo		
 @ref		
 @details	\n
 ��ü�� ���°��� ������ �������̽� Ŭ�����̴�.
 ���°��� eOBJECT_STATE ���̴�.
 SetStatue()�Լ��� ������ ���¸� ������ �� ������ GetStatus()�Լ��� ���� ���¸� ���� ���� �ִ�.
 �⺻���� ���´� �ʱ�ȭ(Initialize)-����(Start)-����(Stop)-�Ҹ�(Destroy)�� 4������ �⺻���� ������ ������ �̵鰣�� ���� ���µ鵵 �����Ѵ�.

  1) Initialize		eOBJECT_STATE::NONE    ->eOBJECT_STATE::INITIALIZING_PENDING ->eOBJECT_STATE::STOPPED
  2) Start			eOBJECT_STATE::STOPPED ->eOBJECT_STATE::START_PENDING        ->eOBJECT_STATE::RUNNING
  3) Stop			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::STOP_PENDING		 ->eOBJECT_STATE::STOPPED
  4) Destory		eOBJECT_STATE::STOPPED ->eOBJECT_STATE::DESTROYING_PENDING   ->eOBJECT_STATE::NONE
  5) Pause			eOBJECT_STATE::RUNNING ->eOBJECT_STATE::PAUSE_PENDING		 ->eOBJECT_STATE::PAUSED
  6) Continue		eOBJECT_STATE::PAUSED  ->eOBJECT_STATE::CONTINUE_PENDING	 ->eOBJECT_STATE::RUNNING
//

*/
//-----------------------------------------------------------------------------
class ICGObjectState : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGAttachable<ICGObjectState>
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGObjectState()	{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ��ü ���¸� ��´�. @return true ���� ��ü ����
	virtual	eOBJECT_STATE		GetObjectState() const PURE;
	//! @brief ���� ��ü ���¸� �����Ѵ�. @param _Status �����ϰ��� �ϴ� '��ü ����' @return ������ '��ü ����'
	virtual	eOBJECT_STATE		SetObjectState(_In_ eOBJECT_STATE _Status) NOEXCEPT PURE;
	//! @brief ���� ���°� _StatusCompare�� ��� _Status�� �����Ѵ�. @param _StatusCompare ���� ��ü ���� @ param _Status ������ ��ü ���� @return true ���� ���� @return false ���� ����
	virtual	bool				SetObjectStateIf(_In_ eOBJECT_STATE _StateCompare, _In_ eOBJECT_STATE _States) NOEXCEPT PURE;
};

namespace CGObject
{

bool	Initialize(ICGObjectState* _Object, CGMSG_CONTEXT& _Msg);
bool	Start(ICGObjectState* _Object, CGMSG_CONTEXT& _Msg);
bool	Stop(ICGObjectState* _Object);
bool	Destroy(ICGObjectState* _Object);
bool	Continue(ICGObjectState* _Object);
bool	Pause(ICGObjectState* _Object);

}