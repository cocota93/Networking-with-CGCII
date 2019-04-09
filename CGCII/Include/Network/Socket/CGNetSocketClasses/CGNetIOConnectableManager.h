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
// CGNet::IO::IConnectManager
//
// 1. CGNet::IO::IConnectManager은~
//    1) Connect Interface를 가진 Interface Class이다.
//    2) 단순히 Connect()를 수행하기 위한 Interface들로만 되어 있다.
//
// 2. Public 함수.
//    1) AddConnectable(...)/RemoveConnectable(...)
//       - IConnectable을 추가하고 삭제하는 함수이다.
//
//    2) DisconnectAll()
//       - 모든 Socket을 Graceful Close를 수행한다. 내부적으로 각 Socket에
//         shutdown()을 수행한다.
//       - Graceful close는 물리적으로 접속이 끊혔지만 접속된 상태로 남아있는
//         Socket은 동작을 하지 않을 수 있다.
//       - 접속을 완료하는 과정에서 TIME_WAIT 상태가 유지됨으로써 많은 Socket을
//         유지하게 될 가능성이 있다.
//
//    3) CloseAll()
//       - 모든 Socket에 대해 Abortive Close를 수행한다. 내부적으로 Linger옵션을
//         Abortive로 설정후 closesocket()을 수행한다.
//       - 함수 호출 즉시 Socket의 접속이 종료되며 모든 Socket관련 할당이 해제된다.
//       - 일반적으로 접속이 종료된 많은 Socket을 유지하기가 위험한 Server에서
//         많이 사용된다.
//
//    4) GetCount();
//       - 관리하고 있는 IConnectable 객체의 수를 돌려준다.
//
//    5) AllocIterator()
//       - 저장된 Connectable의 포인터를 순회하며 직접 얻고 싶을 때 이 함수를
//         호출하여 Iterator를 얻을 수 있다.
//       - 일반적으로 Iterator를 얻게되면 내부 List에 Lock이 걸리게 된다.
//       - 사용 종료 후 얻은 Iterator가 소멸되면 Lock이 해제되게 된다.
//       - AllocIterator()함수를 통해 얻어진 Iterator는 할당 직후 제일 처음
//         Socket에 위치해 있다. 그리고 GetNext()함수를 호출하여 다음 IConnectable을
//         지적할 수 있다.
//       - 끝에 도달하게 되면 nullptr을 가지게 된다.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnectableManager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
public:
	class	CONNECTABLE_ITERATOR;

// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Connectable의 Add/Remove
	virtual	bool				AddConnectable(_In_ IConnectable* _pConnectable) PURE;
	virtual	bool				RemoveConnectable(_In_ IConnectable* _pConnectable) PURE;

	// 2) Disconnect All Accepted Socket
	virtual	void				DisconnectAllConnectable() PURE;
	virtual	void				CloseAllConnectable(uint32_t p_dwFlag=0) PURE;

	// 3) Connectable 수
	virtual	int					GetCount() const PURE;

	// 4) Iterator얻기
	virtual	CGPTR<CONNECTABLE_ITERATOR>	AllocIterator() PURE;
};


class IConnectableManager::CONNECTABLE_ITERATOR : virtual public ICGReferenceable
{
public:
	virtual	void			Reset() PURE;
	virtual	IConnectable*	GetPre() PURE;
	virtual	IConnectable*	GetNext() PURE;
};


}
}