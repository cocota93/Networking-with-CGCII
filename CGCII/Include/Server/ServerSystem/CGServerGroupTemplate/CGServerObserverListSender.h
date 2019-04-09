//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                         Socket template Classes                           *
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

namespace CGServerObservers
{

//-----------------------------------------------------------------------------
/**

 @class		CList
 @brief		
 @todo		
 @ref		
 @details	\n
 List�� Observer Class ��ü
 Group�� �ٸ� ���� ���������� �ʴٴ� ���̴�.
 �������� Observer���� �پ ������ �� �ִ�.

*///-----------------------------------------------------------------------------
template <class _TOBSERVER>
class CListSender :
// ****************************************************************************
// Inherited Classes).
// ----------------------------------------------------------------------------
	virtual public				CGServerObservers::CList<_TOBSERVER>,	// (I) CGServerObservers::CList
	virtual public				CGNet::IO::ISender						// (I) Sender Base
{
// ****************************************************************************
// Definitnion)
// ----------------------------------------------------------------------------
public:
	typedef	CGServerObservers::CList<_TOBSERVER>					BASEOBSERVER;
	typedef	_TOBSERVER												TOBSERVER;


// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CListSender()												{}
	virtual	~CListSender()												{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief ��ü ������� �޸� ������ ������ �����Ѵ�. @param _Buffer ������ �޸� ���� @return true ���� @return false ����
	virtual	bool				Send(_In_ const CCGBuffer& _Buffer);
	//! @brief Ư�� ����� ������ ��ü ������� �޸� ������ �����Ѵ�. @param _pExcept ������ ��� @param _Buffer ������ �޸� ���� @return true ���� @return false ����
			bool				SendExcept(_In_ TOBSERVER* _pExcept, _In_ const CCGBuffer& _Buffer);
	//! @brief ������ ������ ������Ը� �޸� ������ �����Ѵ�. @param _Buffer ������ �޸� ���� @param _fPred ���� �Լ� @return true ���� @return false ����
			bool				SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TOBSERVER*)>& _fPred);
};

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::Send(_In_ const CCGBuffer& _Buffer)
{
	// Check) _Buffer->buf�� nullptr�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.buf==nullptr, false, )

	// Check) _Buffer->len�� 0�� �ƴѰ�?
	ERROR_RETURN_IF(_Buffer.len==0, false, )
	
	// 1) ��ο��� �����Ѵ�.
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter: BASEOBSERVER::m_containerObserver)
		{
			iter->Send(_Buffer);
		}
	}

	// Return) ����...
	return	true;
}

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::SendExcept(_In_ TOBSERVER* _pExcept, _In_ const CCGBuffer& _Buffer)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		auto	iter	 = BASEOBSERVER::m_containerObserver.begin();
		auto	iterEnd	 = BASEOBSERVER::m_containerObserver.end();

		for(; iter!=iterEnd; ++iter)
		{
			// Check) _pExcept�� ��� ����...
			if(*iter==_pExcept)
			{
				++iter;
				break;
			}

			// - �����Ѵ�.
			(*iter)->Send(_Buffer);
		}

		for(; iter!=iterEnd; ++iter)
		{
			// - �����Ѵ�.
			(*iter)->Send(_Buffer);
		}
	}

	// Return) ����...
	return	true;
}

template <class _TOBSERVER>
bool CListSender<_TOBSERVER>::SendConditional(_In_ const CCGBuffer& _Buffer, _In_ const std::function<bool (const TOBSERVER*)>& _fPred)
{
	LOCK(ICGServerObservers<TOBSERVER>::m_csGroup)
	{
		for(auto& iter: BASEOBSERVER::m_containerObserver)
		{
			// Check) _fPred�� false�� �������� �ʴ´�.
			CONTINUE_IF(_fPred(iter)==false);

			// - �����Ѵ�.
			iter->Send(_Buffer);
		}
	}

	// Return) ����...
	return	true;
}


}