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
/*!
* @class NProxy
*
* @ingroup CGNet::IO::Messageable
*
* @brief 메시지 처리를 다른 쓰레드에 걸어 처리하는 Messageable 클래스
*
*     받은 Message를 Queuing하는 기능을 가진 Class이다.
*    Message를 처리하는 과정에서 받은 즉시 처리하지 않고 다른 처리하고자 할 때가 있다.
*    이럴 경우 Message를 Queuing시킨 후 나중에 다른 처리를 Queuing된 메시지를 꺼내
*    수행할 수 있도록 해준다. 
*
*    *) 이 Class는 기본적으로 Thread-Safe하게 동작하도록 설계되어 있다.
*    *) 전달된 주소는 저장하지 않는다. 따라서 주소가 전달되오지 않는 TCP나
*       Address가 정해져있는 UDP Peer에 주로 사용된다. 만약 주소가 필요하다면 QueueDgram을
*       하길 권장한다.
*
*    1) (v) OnQueuingMessage()
*       이 함수에서는 결과가 true일 경우에만 Message를 Queuing한다. 만약 false가
*       Return되게 되면 Queueing하지 않고 ProcessMessage()의 결과로 false를 Return
*       하게 된다. 즉 ProcessMessage()에서 해당 Message를 처리하지 못했다는 뜻이다
*       이 함수의 주요 역할은 Queueing해야할 함수를 골라내는 함수라고 할수 있다
*       Queuing하고 싶은 Message에 대해서만 이 함수를 재정의하여 true를 Return하면
*       된다.
*
*    2) (v) OnMessage()
*        만약 OnQueuingMessage()의 결과가 false일 경우 OnMessage()함수를 호출한다.
*       즉석에서 Message를 처리해야 할 것이 있다면 여기서 처리한다.
*
*    3) (v) OnMessageQueued()
*        ProcessQueuedMessage()함수는 Queuing된 Message를 얻어 OnMessageQueued()를
*        호출하여 Message를 넘겨줌으로써 처리를 수행하게 된다.
*        따라서 Queued된 Message을 처리할 경우 이 함수에서 정의하면 된다.
*
*   4) PopQueuedMessage()
*       Queueing된 Message들은 추후 처리를 원하는 곳에서 PopQueuedMessage()
*      함수를 호출하여 차례로 Message들을 꺼낼수 있다.
*      주의) 꺼내게 되면 꺼낸 Buffer의 Reference Counter가 감소한다.
*            따라서 꺼내어 보관한 Buffer가 소멸되면 자동으로 메모리는
*            Release된다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Messageable
{

class NQueue : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IPacketable,					// (I) Packetable
	virtual public				ICGMessageable							//     Messageable
{
// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) Push된 Message를 뽑아낸다
	//    - OnQueuingMessage()함수에서 선택되어 Message를 얻는 함수이다.
	//    - 만약 Queuing된 것이 없으면 nullptr을 Return한다.
			bool				PopQueuedMessage(CGMSG& _Msg)			{	return m_queueMessage.pop(_Msg);}

	// 2) Queuing된 Message들에 대해서 OnMessageQueued()함수를 호출한다.
			void				ProcessQueuedMessage()					{	CGMSG msg;  while(PopQueuedMessage(msg)) { OnMessageQueued(msg);}}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Queuing을 선택하는 함수.
	//    - 이 함수의 결과물이 true가 돌아오면 Queuing을 한다. 만약 false가 돌아오면 Queuing을 하지 않는다.
	virtual bool				OnQueuingMessage(CGMSG& /*_Msg*/)		{	return true;}

	// 2) Message를 처리하는 함수이다.
	//    - OnMessage에서 0아 아닌 값이 전달되면 처리된 Message으로 간주해 Queuing을 하지 않는다.
	virtual int					OnMessage(CGMSG& /*_Msg*/)				{	return 0;}

	// 3) Queued된 Message을 처리하는 함수이다.
	//    - ProcessQueuedMessage()함수를 호출하면 Queued된 Message에 대해서
	//      OnMessageQueued()함수를 호출하게 된다.
	virtual uint32_t			OnMessageQueued(CGMSG& /*_Msg*/)		{	return 0;}

	// 4) Validate Received Message
	virtual	bool				ValidateReceivedMessage(_In_ const CGMSG& /*_Msg*/){ return true; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			lockfree_queue<CGMSG> m_queueMessage;

public:
	virtual	int					ProcessMessage(CGMSG& _Msg) override;
};


inline int NQueue::ProcessMessage(CGMSG& _Msg)
{
	// Check) 제대로된 메시지인가를 확인한다.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	//-----------------------------------------------------------------
	// 1. Network용 Message로 Casting한다.
	//-----------------------------------------------------------------
	// 1) Casting
	CGNETMSG& rMessage	 = (CGNETMSG&)_Msg;

	// Check) _pBuffer가 nullptr이면 그냥 Return한다.
	RETURN_IF(rMessage.Buffer.get_reference().empty(), 0);


	//-----------------------------------------------------------------
	// 2. Queueing Check를 한다.
	//
	//    - OnQueuingMessage의 결과가 TREU이면 Queueing된다.
	//    - Queueing되면서 자동적으로 Refereunce Count가 증가한다.
	//    - 이건 추후에 Pop을 하게 되면 자동으로 또 감소할 것이다.
	//-----------------------------------------------------------------
	// Declare)
	bool	result;

	// 1) Queueing하기전 한다.
	result	 = OnQueuingMessage(rMessage);

	// Check) OnQueuingMessage()의 값이 0이 아니면Queuing한다.
	if(result!=0)
	{
		// - Message를 Queuing한다.
		m_queueMessage.push(rMessage);

		// Return) 그냥 끝낸다.
		return	1;
	}


	//-----------------------------------------------------------------
	// 3. 일단 먼저 OnMessage을 수행한다.
	//
	// - 여기까지 왔다면 Queueing안한 것이다. 따라서 그냥 OnMessage()
	//   함수를 호출해 메시지를 즉시 처리한다.
	// - 일반적으로 지연해서 처리해야할 Message의 경우 Queuing을 하고
	//   즉석에서 처리해야할 경우 즉시 OnMessage함수에서 호출하여 즉시 
	//   처리한다.
	//-----------------------------------------------------------------
	// 1) OnMessage함수를 호출한다.
	return	OnMessage(rMessage);
}


}
}
}