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

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		CObject
 @brief		일반용 Factroy
 @todo		
 @ref		CGFactory::CPoolBuffer
 @details	\n
 메모리 객체 풀로 기본적인 것은 CGFactory::CPoolMemory와 동일하다.
 CGFactory::CPoolMemory의 경우 메모리의 내용을 초기화할수 는 없었지만 이것은 초기화를 해준다는 것만 다르다.
 따라서 메모리 객체를 신규로 생성해 할당해줄 때 해당 메모리를 초기화해주기 위한 함수를 설정할 수 있다.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT>
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
class CObject : 
	virtual public				ICGFactory,
	public						CGNameable::NString
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CObject();
	virtual	~CObject();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
public:
	//! @brief '싱글턴 객체'를 얻는다. 최초 실행 시 '싱글턴 객체'가 초기화한다.
	static	CGPTR<CObject<TOBJECT>>	GetInstance(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief 풀 객체를 파괴한다. @return true 성공 @return false 실패 
	virtual	bool				Destroy() override;

	//! @brief _iAmount만큼의 객체를 미리 준비해 놓는다. @param _iAmount 준비할 수량 @return 실제 준비된 량
	virtual	size_t				Prepare(_In_ size_t /*_iAmount*/)	{	return 0;}
	//! @brief _iAmount만큼의 재고 객체를 해제한다. @param _iAmount 해제할 수량 @return 실제 해제된 량
	virtual	size_t				Shrink(_In_ size_t /*_iAmount*/)	{	return 0;}
	//! @brief 적절한 재고량을 계산해 재고량을 넘어서는 량에 대해서는 해제 처리하는 가비지 콜렉션 처리를 한다. @param _Level 레벨해제할 수량 @return 실제 해제된 량
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL)	{	NO_WARNING(_Level);}

	//! @brief 객체 당 메모리 크기를 얻는다. @return 객체 당 메모리 크기
	virtual	size_t				GetObjectSize() const				{	return sizeof(TOBJECT);}
	//! @brief 재고량을 얻는다. @return 재고량
	virtual	size_t				GetStackedCount() const				{	return 0;}
	//! @brief 최대 재고량을 얻는다. @return 최대 재고량
	virtual	int64_t				GetExistingLimits() const			{	return 0;}

	//! @brief 풀의 형태를 얻는다. @return 풀의 형태
	virtual	eFACTORY_TYPE		GetFactoryType() const				{	return m_statisticsObject.eFactoryType;}
	//! @brief 풀의 ID를 얻는다. @return 풀의 ID.
	virtual	int					GetFactoryID() const				{	return m_statisticsObject.iFactoryID;}

	//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
	virtual	bool				IsEnableSustain() const				{	return false;}
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
	virtual	void				EnableSustain(_In_ bool _bStatus=true) { NO_WARNING(_bStatus);}

protected:
	// Static)
	static	CGOWN<CObject<TOBJECT>>	m_pInstance;
};

template <class TOBJECT>
CGOWN<CObject<TOBJECT>> CObject<TOBJECT>::m_pInstance;

template <class TOBJECT>
CObject<TOBJECT>::CObject()
{
	// Declare) 
	_CHAR	temp[MAX_NAME_LENGTH] ={0};

	// - 기본 이름 문자열을 만든다.
	CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TOBJECT).name());

	// - 기본 이름을 설정한다.
	SetName(temp);

	// 3) Factory Type을 설정한다.
	m_statisticsObject.eFactoryType = eFACTORY_TYPE::ALLOCATOR_SYSTEM;

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Allocator(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager에 등록한다.
	RegisterFactory();
}

template <class TOBJECT>
CObject<TOBJECT>::~CObject()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Allocator(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// 1) Factory Manager에 등록해제한다.
	UnregisterFactory();
}

template <class TOBJECT>
bool CObject<TOBJECT>::Destroy()
{
	// 1) Instance를 Reset한다.
	m_pInstance.reset();
	
	// Return) 
	return true;
}

template <class TOBJECT>
inline CGPTR<CObject<TOBJECT>>	CObject<TOBJECT>::GetInstance(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Check) 만약 생성되어 있지 않으면 새로 생성한다.
	if (m_pInstance.empty())
	{
		static	LOCKABLE<> csCreate;

		LOCK(csCreate)
		{
			// Check) 이미 생성되어 있으면 그냥 끝낸다.
			RETURN_IF(m_pInstance.exist(), m_pInstance);

			// 1) 신규로 생성한다.
			m_pInstance	 = _CGNEW_RAW<CObject<TOBJECT>>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
		}
	}

	// Return) 얻은 Instance를 리턴한다.
	return m_pInstance;
}

}

template <class TOBJECT>
class NCGReferenceable : public ICGReferenceable::Delete
{
public:
			NCGReferenceable(CGNEW_DEBUG_INFO_PARAMETERS)	{ m_factoryObject=CGFactory::CObject<TOBJECT>::GetInstance(CGNEW_DEBUG_INFO_PARAMETERS_PASSING); m_factoryObject->Statistics_OnNew(); }
			~NCGReferenceable()								{ if(m_factoryObject.empty()) return; m_factoryObject->Statistics_OnDelete(); m_factoryObject.reset(); }

private:
			CGPTR<CGFactory::CObject<TOBJECT>>	m_factoryObject;
};

