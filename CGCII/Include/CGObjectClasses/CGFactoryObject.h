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

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		CObject
 @brief		�Ϲݿ� Factroy
 @todo		
 @ref		CGFactory::CPoolBuffer
 @details	\n
 �޸� ��ü Ǯ�� �⺻���� ���� CGFactory::CPoolMemory�� �����ϴ�.
 CGFactory::CPoolMemory�� ��� �޸��� ������ �ʱ�ȭ�Ҽ� �� �������� �̰��� �ʱ�ȭ�� ���شٴ� �͸� �ٸ���.
 ���� �޸� ��ü�� �űԷ� ������ �Ҵ����� �� �ش� �޸𸮸� �ʱ�ȭ���ֱ� ���� �Լ��� ������ �� �ִ�.

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
	//! @brief '�̱��� ��ü'�� ��´�. ���� ���� �� '�̱��� ��ü'�� �ʱ�ȭ�Ѵ�.
	static	CGPTR<CObject<TOBJECT>>	GetInstance(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief Ǯ ��ü�� �ı��Ѵ�. @return true ���� @return false ���� 
	virtual	bool				Destroy() override;

	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
	virtual	size_t				Prepare(_In_ size_t /*_iAmount*/)	{	return 0;}
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
	virtual	size_t				Shrink(_In_ size_t /*_iAmount*/)	{	return 0;}
	//! @brief ������ ����� ����� ����� �Ѿ�� ���� ���ؼ��� ���� ó���ϴ� ������ �ݷ��� ó���� �Ѵ�. @param _Level ���������� ���� @return ���� ������ ��
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL)	{	NO_WARNING(_Level);}

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetObjectSize() const				{	return sizeof(TOBJECT);}
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetStackedCount() const				{	return 0;}
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetExistingLimits() const			{	return 0;}

	//! @brief Ǯ�� ���¸� ��´�. @return Ǯ�� ����
	virtual	eFACTORY_TYPE		GetFactoryType() const				{	return m_statisticsObject.eFactoryType;}
	//! @brief Ǯ�� ID�� ��´�. @return Ǯ�� ID.
	virtual	int					GetFactoryID() const				{	return m_statisticsObject.iFactoryID;}

	//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
	virtual	bool				IsEnableSustain() const				{	return false;}
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
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

	// - �⺻ �̸� ���ڿ��� �����.
	CGSNPRINTF_S(temp, _TRUNCATE, _CGTEXT("%hs"), typeid(TOBJECT).name());

	// - �⺻ �̸��� �����Ѵ�.
	SetName(temp);

	// 3) Factory Type�� �����Ѵ�.
	m_statisticsObject.eFactoryType = eFACTORY_TYPE::ALLOCATOR_SYSTEM;

	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Allocator(%s) is created ") _CGFUNCTION, GetName());

	// 4) Factory Manager�� ����Ѵ�.
	RegisterFactory();
}

template <class TOBJECT>
CObject<TOBJECT>::~CObject()
{
	// Trace) 
	CGLOG_INFO_LOW(DEFAULT_LOGGER, _CGTEXT("(Info) CGFactory: Allocator(%s:%I64d) is destroyed ") _CGFUNCTION, GetName(), static_cast<int64_t>(GetObjectSize()));

	// 1) Factory Manager�� ��������Ѵ�.
	UnregisterFactory();
}

template <class TOBJECT>
bool CObject<TOBJECT>::Destroy()
{
	// 1) Instance�� Reset�Ѵ�.
	m_pInstance.reset();
	
	// Return) 
	return true;
}

template <class TOBJECT>
inline CGPTR<CObject<TOBJECT>>	CObject<TOBJECT>::GetInstance(CGNEW_DEBUG_INFO_PARAMETERS)
{
	// Check) ���� �����Ǿ� ���� ������ ���� �����Ѵ�.
	if (m_pInstance.empty())
	{
		static	LOCKABLE<> csCreate;

		LOCK(csCreate)
		{
			// Check) �̹� �����Ǿ� ������ �׳� ������.
			RETURN_IF(m_pInstance.exist(), m_pInstance);

			// 1) �űԷ� �����Ѵ�.
			m_pInstance	 = _CGNEW_RAW<CObject<TOBJECT>>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING);
		}
	}

	// Return) ���� Instance�� �����Ѵ�.
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

