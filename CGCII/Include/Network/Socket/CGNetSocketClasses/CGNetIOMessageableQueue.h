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
* @brief �޽��� ó���� �ٸ� �����忡 �ɾ� ó���ϴ� Messageable Ŭ����
*
*     ���� Message�� Queuing�ϴ� ����� ���� Class�̴�.
*    Message�� ó���ϴ� �������� ���� ��� ó������ �ʰ� �ٸ� ó���ϰ��� �� ���� �ִ�.
*    �̷� ��� Message�� Queuing��Ų �� ���߿� �ٸ� ó���� Queuing�� �޽����� ����
*    ������ �� �ֵ��� ���ش�. 
*
*    *) �� Class�� �⺻������ Thread-Safe�ϰ� �����ϵ��� ����Ǿ� �ִ�.
*    *) ���޵� �ּҴ� �������� �ʴ´�. ���� �ּҰ� ���޵ǿ��� �ʴ� TCP��
*       Address�� �������ִ� UDP Peer�� �ַ� ���ȴ�. ���� �ּҰ� �ʿ��ϴٸ� QueueDgram��
*       �ϱ� �����Ѵ�.
*
*    1) (v) OnQueuingMessage()
*       �� �Լ������� ����� true�� ��쿡�� Message�� Queuing�Ѵ�. ���� false��
*       Return�ǰ� �Ǹ� Queueing���� �ʰ� ProcessMessage()�� ����� false�� Return
*       �ϰ� �ȴ�. �� ProcessMessage()���� �ش� Message�� ó������ ���ߴٴ� ���̴�
*       �� �Լ��� �ֿ� ������ Queueing�ؾ��� �Լ��� ��󳻴� �Լ���� �Ҽ� �ִ�
*       Queuing�ϰ� ���� Message�� ���ؼ��� �� �Լ��� �������Ͽ� true�� Return�ϸ�
*       �ȴ�.
*
*    2) (v) OnMessage()
*        ���� OnQueuingMessage()�� ����� false�� ��� OnMessage()�Լ��� ȣ���Ѵ�.
*       �Ｎ���� Message�� ó���ؾ� �� ���� �ִٸ� ���⼭ ó���Ѵ�.
*
*    3) (v) OnMessageQueued()
*        ProcessQueuedMessage()�Լ��� Queuing�� Message�� ��� OnMessageQueued()��
*        ȣ���Ͽ� Message�� �Ѱ������ν� ó���� �����ϰ� �ȴ�.
*        ���� Queued�� Message�� ó���� ��� �� �Լ����� �����ϸ� �ȴ�.
*
*   4) PopQueuedMessage()
*       Queueing�� Message���� ���� ó���� ���ϴ� ������ PopQueuedMessage()
*      �Լ��� ȣ���Ͽ� ���ʷ� Message���� ������ �ִ�.
*      ����) ������ �Ǹ� ���� Buffer�� Reference Counter�� �����Ѵ�.
*            ���� ������ ������ Buffer�� �Ҹ�Ǹ� �ڵ����� �޸𸮴�
*            Release�ȴ�.
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
	// 1) Push�� Message�� �̾Ƴ���
	//    - OnQueuingMessage()�Լ����� ���õǾ� Message�� ��� �Լ��̴�.
	//    - ���� Queuing�� ���� ������ nullptr�� Return�Ѵ�.
			bool				PopQueuedMessage(CGMSG& _Msg)			{	return m_queueMessage.pop(_Msg);}

	// 2) Queuing�� Message�鿡 ���ؼ� OnMessageQueued()�Լ��� ȣ���Ѵ�.
			void				ProcessQueuedMessage()					{	CGMSG msg;  while(PopQueuedMessage(msg)) { OnMessageQueued(msg);}}


// ****************************************************************************
// Frameworks) 
// ----------------------------------------------------------------------------
protected:
	// 1) Queuing�� �����ϴ� �Լ�.
	//    - �� �Լ��� ������� true�� ���ƿ��� Queuing�� �Ѵ�. ���� false�� ���ƿ��� Queuing�� ���� �ʴ´�.
	virtual bool				OnQueuingMessage(CGMSG& /*_Msg*/)		{	return true;}

	// 2) Message�� ó���ϴ� �Լ��̴�.
	//    - OnMessage���� 0�� �ƴ� ���� ���޵Ǹ� ó���� Message���� ������ Queuing�� ���� �ʴ´�.
	virtual int					OnMessage(CGMSG& /*_Msg*/)				{	return 0;}

	// 3) Queued�� Message�� ó���ϴ� �Լ��̴�.
	//    - ProcessQueuedMessage()�Լ��� ȣ���ϸ� Queued�� Message�� ���ؼ�
	//      OnMessageQueued()�Լ��� ȣ���ϰ� �ȴ�.
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
	// Check) ����ε� �޽����ΰ��� Ȯ���Ѵ�.
	#ifdef _VALIDATE_RECEIVE_MESSAGE
	CGASSERT(ValidateReceivedMessage(_Msg), 0);
	#endif

	//-----------------------------------------------------------------
	// 1. Network�� Message�� Casting�Ѵ�.
	//-----------------------------------------------------------------
	// 1) Casting
	CGNETMSG& rMessage	 = (CGNETMSG&)_Msg;

	// Check) _pBuffer�� nullptr�̸� �׳� Return�Ѵ�.
	RETURN_IF(rMessage.Buffer.get_reference().empty(), 0);


	//-----------------------------------------------------------------
	// 2. Queueing Check�� �Ѵ�.
	//
	//    - OnQueuingMessage�� ����� TREU�̸� Queueing�ȴ�.
	//    - Queueing�Ǹ鼭 �ڵ������� Refereunce Count�� �����Ѵ�.
	//    - �̰� ���Ŀ� Pop�� �ϰ� �Ǹ� �ڵ����� �� ������ ���̴�.
	//-----------------------------------------------------------------
	// Declare)
	bool	result;

	// 1) Queueing�ϱ��� �Ѵ�.
	result	 = OnQueuingMessage(rMessage);

	// Check) OnQueuingMessage()�� ���� 0�� �ƴϸ�Queuing�Ѵ�.
	if(result!=0)
	{
		// - Message�� Queuing�Ѵ�.
		m_queueMessage.push(rMessage);

		// Return) �׳� ������.
		return	1;
	}


	//-----------------------------------------------------------------
	// 3. �ϴ� ���� OnMessage�� �����Ѵ�.
	//
	// - ������� �Դٸ� Queueing���� ���̴�. ���� �׳� OnMessage()
	//   �Լ��� ȣ���� �޽����� ��� ó���Ѵ�.
	// - �Ϲ������� �����ؼ� ó���ؾ��� Message�� ��� Queuing�� �ϰ�
	//   �Ｎ���� ó���ؾ��� ��� ��� OnMessage�Լ����� ȣ���Ͽ� ��� 
	//   ó���Ѵ�.
	//-----------------------------------------------------------------
	// 1) OnMessage�Լ��� ȣ���Ѵ�.
	return	OnMessage(rMessage);
}


}
}
}