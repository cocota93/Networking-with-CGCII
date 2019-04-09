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
//-----------------------------------------------------------------------------
/**

 @class		ICGFactory
 @brief		Ǯ(Factory)�� ����� �Ǵ� �������̽� Ŭ�����̴�.
 @todo		
 @ref		OBJECT_ID, ICGMessageable, ICGNameable
 @details	\n
 Ǯ�� ����� �Ǵ� �������̽� Ŭ������ Ǯ�� ���� ������ ��������� ������.
 ICGFactory�� ��ӹ����� Ǯ �����ڿ� ��ϵǾ� �����ȴ�.
 
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
	// 1) ��� ���� ���� �Լ�-Get
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

	// 2) ��� ���� ���� �Լ�-Set
			void				Statistics_OnNew()						{ ++m_statisticsObject.qwAlloc_Create; ++m_statisticsObject.iExisting; ++m_statisticsObject.iInUsing; }
			void				Statistics_OnDelete()					{ ++m_statisticsObject.qwFree_Delete;  --m_statisticsObject.iExisting; --m_statisticsObject.iInUsing; }

	// 3) ��� ����
	const CGStatistics::FACTORY& GetStatistics() const					{ return m_statisticsObject; }


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	//! @brief _iAmount��ŭ�� ��ü�� �̸� �غ��� ���´�. @param _iAmount �غ��� ���� @return ���� �غ�� ��
	virtual	size_t				Prepare(_In_ size_t _iAmount) PURE;
	//! @brief _iAmount��ŭ�� ��� ��ü�� �����Ѵ�. @param _iAmount ������ ���� @return ���� ������ ��
	virtual	size_t				Shrink(_In_ size_t _iAmount) PURE;
	//! @brief ������ ����� ����� ����� �Ѿ�� ���� ���ؼ��� ���� ó���ϴ� ������ �ݷ��� ó���� �Ѵ�. @param _Level ���������� ���� @return ���� ������ ��
	virtual	void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level= eFACTORY_SUSTAIN_TYPE::NORMAL) PURE;

	//! @brief ��ü �� �޸� ũ�⸦ ��´�. @return ��ü �� �޸� ũ��
	virtual	size_t				GetObjectSize() const PURE;
	//! @brief ����� ��´�. @return ���
	virtual	size_t				GetStackedCount() const PURE;
	//! @brief �ִ� ����� ��´�. @return �ִ� ���
	virtual	int64_t				GetExistingLimits() const PURE;

	//! @brief Ǯ�� ���¸� ��´�. @return Ǯ�� ����
	virtual	eFACTORY_TYPE		GetFactoryType() const PURE;
	//! @brief Ǯ�� ID�� ��´�. @return Ǯ�� ID.
	virtual	int					GetFactoryID() const PURE;

	//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
	virtual	bool				IsEnableSustain() const PURE;
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
	virtual	void				EnableSustain(_In_ bool _bStatus=true) PURE;
	//! @brief �����ݷ����� �Ұ����ϰ� �Ѵ�.
			void				DisableSustain()						{	EnableSustain(false);}

protected:
	//! @brief Ǯ�� Ǯ �����ڿ� ����Ѵ�.
			void				RegisterFactory();
	//! @brief Ǯ�� Ǯ �����ڿ��� ��������Ѵ�.
			void				UnregisterFactory();
	//! @brief Ǯ�� �ı��Ѵ�.
			void				DestroyFactory();

	// @brief ��� ������ �����Ѵ�.
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
