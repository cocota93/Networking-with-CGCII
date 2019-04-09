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

 @class		ICGObjectIdentifiable
 @brief		TLS�� ����ϴ� ��ü Ǯ Ŭ�����̴�.
 @todo		
 @ref		CGFatory::CPoolObject<T>, ICGPoolable
 @details	\n
 TLS�� ����� ��ü Ǯ�� ��� ����� CGFactory::CPool`Object<T>�� �����Ѵ�.
 �ٸ� ���������� TLS�� ����� ���� �����忡�� ���� �ּ�ȭ�� �Ҵ�� ������ �ӵ��� �� �پ��.
 ������ �� ���� �޸𸮸� �Ҹ��ϹǷ� �뷮�� �ΰ��� ��� ����� ���ϴ� ���� ����.

*/
//-----------------------------------------------------------------------------
template <class TOBJECT, class TCREATE=TOBJECT>
class CPoolObjectTLS : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						ICGFactory,
	public						CGNameable::NString
{
// ****************************************************************************
// Definition)
// ----------------------------------------------------------------------------
public:
	typedef	std::function<void(TCREATE*)>	TFUNCTION;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CPoolObjectTLS(_In_opt_z_ const _CHAR* _strName=nullptr, _In_ int p_iTLSCacheSize=DEFAULT_POOL_TLS_CACH_SIZE, _In_ bool _bSustain=true, _In_ eFACTORY_TYPE _eFactoryType=eFACTORY_TYPE::POOL_USER);
	virtual	~CPoolObjectTLS();


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief Ǯ ��ü�� �ı��Ѵ�. @return true ���� @return false ���� 
	virtual	bool				Destroy() override;

	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
	virtual	size_t				Prepare(_In_ size_t _iAmount);
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
	virtual	size_t				Shrink(_In_ size_t _iAmount);
	//! @brief ������ ����� ����� ����� �Ѿ�� ���� ���ؼ��� ���� ó���ϴ� ������ �ݷ��� ó���� �Ѵ�. @param _Level ���������� ���� @return ���� ������ ��
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL);

	//! @brief Ǯ���� ��ü�� �Ҵ��� ��û�Ѵ�. @return �Ҵ�� ��ü
			TOBJECT*			Alloc(CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT);
	//! @brief Ǯ�� ��ü�� ��ȯ�Ѵ�. @param _Object ��ȯ�� ��ü
			void				Free(_In_ TOBJECT* _Object);

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetObjectSize() const override			{	return sizeof(TCREATE);}
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetStackedCount() const override;
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetExistingLimits() const override		{	return m_statisticsObject.iExistingLimits;}

	//! @brief Ǯ�� ���¸� ��´�. @return Ǯ�� ����
	virtual	eFACTORY_TYPE			GetFactoryType() const override		{	return m_statisticsObject.eFactoryType;}
	//! @brief Ǯ�� ID�� ��´�. @return Ǯ�� ID.
	virtual	int					GetFactoryID() const override			{	return m_statisticsObject.iFactoryID;}

	//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
	virtual	bool				IsEnableSustain() const override		{	return m_bEnableSustain;}
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
	virtual	void				EnableSustain(_In_ bool _bStatus=true) override;

	//! @brief ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ��� �����Ѵ�. @param _pFunction ���ο� ��ü�� �Ҵ��� �� ȣ��� �Լ�
			void				SetOnCreateNewFunction(_In_ const TFUNCTION& _pFunction);

	//! @brief ���Կ�����(Assignment�� ���� ���� �ʴ´�.)
			void				operator=(const CPoolObjectTLS<TOBJECT, TCREATE>& /*_rhs*/) _DELETE;


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// Definitions)
			struct STATISTICS_POOL;
			struct TLS_CACHE;
			struct STACK_BALANCE;

	//! @brief ��ü�� �����ϴ� ������ �����Ѵ�. @return ������ ��ü
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, TCREATE*>::type
								ProcessCreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	//! @brief ��ü�� �ı���Ű�� ������ �����Ѵ�. @param _Object �ı��� ��ü
	template <class TTOBJECT>
	typename std::enable_if<std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);
	template <class TTOBJECT>
	typename std::enable_if<!std::is_base_of<CGPool::_traits_has_pool, TTOBJECT>::value, void>::type
								ProcessDestroyObject(_In_ TCREATE* _Object);

	//! @brief ��ü�� ������ ��û�Ѵ�. @return ������ ��ü
	virtual	TCREATE*			CreateObject(CGNEW_DEBUG_INFO_PARAMETERS);

	// 2) Chunk Create/Destroy
			TCREATE*			ProcessCreateChunk();
			void				ProcessDestroyChunk(_In_ TCREATE* p_rChunk);

	// 3) Chunk Pop/Push
			TCREATE*			ProcessPopChunk();
			void				ProcessPushChunk(_In_ TCREATE* p_pChunk);

	//! @brief ��ü�� ������ �� ȣ���ϴ� �Լ� @param _Object ���� ������ ��ü
	virtual	void				OnCreateNew(TCREATE* /*_Object*/)	{}
	//! @brief ��ü�� �Ҹ����� �� ȣ���ϴ� �Լ� @param _Object �Ҹ��� ��ü
	virtual	void				OnDestroy(TCREATE* /*_Object*/)	{}

private:
	// 5) ��� ������ (Garbage Stack)
			size_t				m_TLSIndex;
			size_t				m_sizeTLSCache;
			LOCKABLE<list<TLS_CACHE>>	m_listStackTLS;
			Interlocked_self_stack<TCREATE*>	m_stackCHUNK;

	// 6) Pool Sustainment�� ���� ������
			int64_t				m_iAllocatedSmoothedAverage;
			int64_t				m_iAllocatedVariation;

	// 7) Hook Function
			TFUNCTION			m_fOnCreateNew;

	// 8) Enable Sustain
			bool				m_bEnableSustain;
};


}

#include "CGObjectClasses/CGFactoryPoolObjectTLS.inl"
