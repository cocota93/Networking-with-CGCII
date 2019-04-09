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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::DB::NRequestorConcurrent
//
// 1. CGServerQuery::DB::NRequestorConcurrent란!
//    1) Query를 일괄처리하기 위한 Querier이다.
//    2) RequestQueue()함수로 Query를 누적된 Query들은 RequestQuery()를 통해
//       동시에 Query를 수행하도록 건다.
//    3) 등록되었던 모든 Query의 수행이 종료되면 ProcessCompleteQuery()함수가 
//       호출 된다.
//
// 3. 주의 사항
//    - RequestQuery()이후에 RequestQuery()로 누적된 Query는 다음 Batch에
//      실행된다.
//
//-----------------------------------------------------------------------------
namespace CGServerQuery
{
namespace DBSystem
{

class NRequestorConcurrent :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						CRequestor					//     Reference Count
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NRequestorConcurrent()	{}
	virtual ~NRequestorConcurrent()	{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Process Request Query
	virtual	bool				ProcessBeginQuery();

	// 2) Process Notify Complete Query
	virtual	void				ProcessNotifyCompleteQuery(ICGServerQuery* p_pQuery);

	// 3) Process Complete Query
	virtual	void				ProcessCompleteQuery()					{}

	// 4) Lock
	int					m_countLock;
};

inline bool CGServerQuery::DBSystem::NRequestorConcurrent::ProcessBeginQuery()
{
	// Declare) 
	int	bCompletion;

	// 1) 모든 Query를 Query건다.
	LOCK(m_queueQuery)
	{
		// - Lock count를 1로 설정한다.
		m_countLock	 = 1;

		for(auto& iter:m_queueQuery)
		{
			// - Request Query를 수행한다.
			iter.pQuerier->ProcessPostRequestQuery(iter.pQuery);

			// - Lock count를 증가시킨다.
			++m_countLock;
		}

		// - 모두 지운다.
		m_queueQuery.clear();

		// - Lock count를 1 줄인다.
		bCompletion	 = --m_countLock;
	}

	// Check)
	if(bCompletion ==0)
	{
		ProcessCompleteQuery();
	}

	// Return) 
	return	true;
}

inline void CGServerQuery::DBSystem::NRequestorConcurrent::ProcessNotifyCompleteQuery(ICGServerQuery* /*p_pQuery*/)
{
	// Declare) 
	int	bCompletion;

	LOCK(m_queueQuery)
	{
		// 1) Lock Count를 줄인다.
		bCompletion	 = --m_countLock;
	}

	// 3) Query를 모두 완료했으면 ProcessCompleteQuery를 호출한다.
	if(bCompletion==0)
	{
		ProcessCompleteQuery();
	}
}


}
}