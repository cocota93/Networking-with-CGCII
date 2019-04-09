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
// CGServerQuery::DB::NRequestorConcurrent
//
// 1. CGServerQuery::DB::NRequestorConcurrent��!
//    1) Query�� �ϰ�ó���ϱ� ���� Querier�̴�.
//    2) RequestQueue()�Լ��� Query�� ������ Query���� RequestQuery()�� ����
//       ���ÿ� Query�� �����ϵ��� �Ǵ�.
//    3) ��ϵǾ��� ��� Query�� ������ ����Ǹ� ProcessCompleteQuery()�Լ��� 
//       ȣ�� �ȴ�.
//
// 3. ���� ����
//    - RequestQuery()���Ŀ� RequestQuery()�� ������ Query�� ���� Batch��
//      ����ȴ�.
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

	// 1) ��� Query�� Query�Ǵ�.
	LOCK(m_queueQuery)
	{
		// - Lock count�� 1�� �����Ѵ�.
		m_countLock	 = 1;

		for(auto& iter:m_queueQuery)
		{
			// - Request Query�� �����Ѵ�.
			iter.pQuerier->ProcessPostRequestQuery(iter.pQuery);

			// - Lock count�� ������Ų��.
			++m_countLock;
		}

		// - ��� �����.
		m_queueQuery.clear();

		// - Lock count�� 1 ���δ�.
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
		// 1) Lock Count�� ���δ�.
		bCompletion	 = --m_countLock;
	}

	// 3) Query�� ��� �Ϸ������� ProcessCompleteQuery�� ȣ���Ѵ�.
	if(bCompletion==0)
	{
		ProcessCompleteQuery();
	}
}


}
}