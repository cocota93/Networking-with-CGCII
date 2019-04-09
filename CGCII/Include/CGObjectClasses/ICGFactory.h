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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGFactory
 @brief		풀(Factory)의 기반이 되는 인터페이스 클래스이다.
 @todo		
 @ref		OBJECT_ID, ICGMessageable, ICGNameable
 @details	\n
 풀의 기반이 되는 인터페이스 클래스로 풀에 대한 관리와 통계정보를 가진다.
 ICGFactory을 상속받으면 풀 관리자에 등록되어 관리된다.
 
*/
//-----------------------------------------------------------------------------
class ICGFactory : 
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGNameable,
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGFactory()		{ ResetStatistics();}
	virtual	~ICGFactory()		{}
	

// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	// 1) 통계 정보 관련 함수-Get
			int64_t				Statistics_GetAllocatedCreate() const	{ return m_statisticsObject.qwAlloc_Create; }
			int64_t				Statistics_GetAllocatedStack() const	{ return m_statisticsObject.qwAlloc_Stacked; }
			int64_t				Statistics_GetAllocated() const			{ return (m_statisticsObject.qwAlloc_Stacked+m_statisticsObject.qwAlloc_Create); }
			int64_t				Statistics_GetFreedStack() const		{ return m_statisticsObject.qwFree_Stacked; }
			int64_t				Statistics_GetFreedDelete() const		{ return m_statisticsObject.qwFree_Delete; }
			int64_t				Statistics_GetFreed() const				{ return (m_statisticsObject.qwFree_Stacked+m_statisticsObject.qwFree_Delete); }
			int64_t				Statistics_GetDisused() const			{ return m_statisticsObject.qwFree_Disuse; }
			int64_t				Statistics_GetExistingLimits() const	{ return m_statisticsObject.iExistingLimits; }
			int64_t				Statistics_GetExisting() const			{ return m_statisticsObject.iExisting; }
			int64_t				Statistics_GetInUsing() const			{ return m_statisticsObject.iInUsing; }

	// 2) 통계 정보 관련 함수-Set
			void				Statistics_OnNew()						{ ++m_statisticsObject.qwAlloc_Create; ++m_statisticsObject.iExisting; ++m_statisticsObject.iInUsing; }
			void				Statistics_OnDelete()					{ ++m_statisticsObject.qwFree_Delete;  --m_statisticsObject.iExisting; --m_statisticsObject.iInUsing; }

	// 3) 통계 정보
	const CGStatistics::FACTORY& GetStatistics() const					{ return m_statisticsObject; }


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t _iAmount) PURE;
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t _iAmount) PURE;
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL) PURE;

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetObjectSize() const PURE;
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetStackedCount() const PURE;
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetExistingLimits() const PURE;

	//! @brief 풀의 형태를 얻는다. @return 풀의 형태
	virtual	eFACTORY_TYPE		GetFactoryType() const PURE;
	//! @brief 풀의 ID를 얻는다. @return 풀의 ID.
	virtual	int					GetFactoryID() const PURE;

	//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
	virtual	bool				IsEnableSustain() const PURE;
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
	virtual	void				EnableSustain(_In_ bool _bStatus=true) PURE;
	//! @brief 가비콜렉션을 불가능하게 한다.
			void				DisableSustain()						{	EnableSustain(false);}

protected:
	//! @brief 풀을 풀 관리자에 등록한다.
			void				RegisterFactory();
	//! @brief 풀을 풀 관리자에서 등록해제한다.
			void				UnregisterFactory();
	//! @brief 풀을 파괴한다.
			void				DestroyFactory();

	// @brief 통계 정보를 리셋한다.
			void				ResetStatistics();

protected:
	// Statistics) 
			CGStatistics::FACTORY	m_statisticsObject;

protected:
			LOCKABLE<CGPTR<CGFactory::Manager>> m_pManager;
	friend	CGFactory::Manager;
};

inline void ICGFactory::ResetStatistics()
{
	// 1) Reset object statistics
	m_statisticsObject.qwAlloc_Stacked	 = 0;
	m_statisticsObject.qwAlloc_Create	 = 0;
	m_statisticsObject.qwFree_Stacked	 = 0;
	m_statisticsObject.qwFree_Delete	 = 0;
	m_statisticsObject.qwFree_Disuse	 = 0;
	m_statisticsObject.iExistingLimits	 = INT64_MAX;
	m_statisticsObject.iExisting		 = 0;
	m_statisticsObject.iInUsing			 = 0;
}
