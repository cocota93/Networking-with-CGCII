//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             Server DB Classes                             *
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
// CGServerQuery::DBSystem::RequestorQueue::CBatchDispatch
//
// 1. CGServerQuery::DBSystem::RequestorQueue::CBatchDispatch��!
//    1) CGServerQuery::DB::CRequestorConcurrent�� ��ӹ޾� �Ϸ�� ȣ��Ǵ� ProcessCompleteQuery()
//       �Լ��� �������� Ŭ�����̴�.
//    2) Query�� �Ϸ�Ǹ� Dispatchable�� ��ϵ� ��� ������ Message�� �����Ѵ�.
//       ������ Message�� SetMessage()�Լ��� ����Ͽ� ������ �� �ִ�.
//
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DBSystem
{
namespace RequestorBatch
{

template<class TMESSAGE>
class CDispatch : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						NRequestorBatch,
	public						NCGDispatchable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CDispatch()													{}
	virtual ~CDispatch()												{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				SetMessage(const TMESSAGE& p_rMessage)	{	m_Message=p_rMessage;}
			const TMESSAGE&		GetMessage() const						{	return m_Message;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteQuery()					{	Dispatch(m_Message);}

	// 2) Message
			TMESSAGE			m_Message;
};


}
}
}