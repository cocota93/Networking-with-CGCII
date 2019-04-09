//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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

 @class		ICGReferenceable
 @brief		������� �Ӽ��� �������̽� Ŭ����
 @todo		
 @ref		CGPTR, CGOBJ
 @details	\n
 ������� �Ӽ��� ������ �������̽� Ŭ������ ����������  ��������� ������ �ִ�.
 �� ��������� ó�� �����ɶ��� 0���� �ʱ�ȭ �Ǹ�
 AddReference()�Լ��� ȣ���ϸ� ������� 1�� �����ϰ� �ȴ�.
 Release()�Լ��� ȣ���ϸ� ������� 1�� �����ϰ� �ȴ�.
 �� ��������� 0�� �Ǹ� OnFinalRelease/ProcessDispose�Լ��� ȣ�����ش�.
 OnFinalRelease()�Լ��� �������ϸ� ��������� 0�� �Ǿ��� �� ������ ������ �ټ� �ִ�.
 �̶� ������� ������ �����忡 �����ϰ� �����Ѵ�.

 �Ϲ������� ICGReferenceable�� �����Ҵ�� ��ü�� �ڵ��Ҵ������� ���� ���ȴ�.

*/
//-----------------------------------------------------------------------------
class ICGDisposable
{
protected:
	virtual	void				ProcessDispose() PURE;
};

class ICGReferenceable : virtual public ICGDisposable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			ICGReferenceable() : m_Counter(0), m_bDisuse(false) CGNEW_DEBUG_INFO_INITIALIZE {}
			ICGReferenceable(const ICGReferenceable&) : m_Counter(0), m_bDisuse(false) CGNEW_DEBUG_INFO_INITIALIZE {}
	virtual	~ICGReferenceable()											{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
#ifdef _DEBUG
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	_Debug_OnAddReferenceCount(count)
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT		_Debug_OnReleaseReferenceCount()
#else
	#define		DEBUG_ON_ADD_REFERENCECOUNT(count)	
	#define		DEBUG_ON_RELEASE_REFERENCECOUNT
#endif

public:
	//! @brief ��������� 0���� �����Ѵ�.(OnFinalRelease/ProcessDispose�Լ��� ȣ����� �ʴ´�.) 
			void				ResetReferenceCount()					{	m_Counter=0;}
	//! @brief ��������� ������ ������ �����Ѵ�. @param _Count ������ ������� ��
			void				SetReferenceCount(int _Count)			{	m_Counter=_Count;}

	//! @brief ��������� 1 ������Ų��. @return ������ ������� ��
			int					AddRef()								{	DEBUG_ON_ADD_REFERENCECOUNT(1); return ++m_Counter;}
	//! @brief ��������� _Count��ŭ ������Ų��.(_Count���� ������ �ȉ´�.) @param _Count ����ġ @return ������Ų ���� �������
			int					AddRef(int _Count)						{	DEBUG_ON_ADD_REFERENCECOUNT(_Count); CGASSERT_ERROR(_Count>=0); return m_Counter+=_Count;}

	//! @brief ��������� 1 ���ҽ�Ų��. ��������� 0�� �Ǹ� OnFinalRelease/ProcessDispose�� ȣ���Ѵ�. @return ���ҽ�Ų �� �������
			int					Release()								{	DEBUG_ON_RELEASE_REFERENCECOUNT; int result=--m_Counter; CGASSERT_ERROR(result>=0); if(result==0) { OnFinalRelease(); CGNEW_DEBUG_INFO_RESET(this); ProcessDispose(); } return result;}

	//! @brief ���� ��������� ��´�. @return ���� �������
			int					GetReferenceCount() const				{	return m_Counter;}

	//! @brief ��ü�� ����ϵ��� �����Ѵ�. Ǯ���� �Ҵ�� ��ü�� ��� Disuse�� �����Ǹ� Ǯ�� �ǵ��� ���� �������� �ʰ� �ٷ� �Ҹ��Ų��. 
			void				SetAsDisuse()							{	m_bDisuse = true; }
			bool				IsDisuse() const						{	return m_bDisuse;}

	//! @brief ����������: ��������� 1 ������Ų��.(AddRef�� �����ϴ�.)
			ICGReferenceable&	operator++()							{	AddRef(); return *this;}
	//! @brief ���ҿ�����: ��������� 1 ���ҽ�Ų��.(Release()�� �����ϴ�.)
			ICGReferenceable&	operator--()							{	Release(); return *this;}
	//! @brief ���ϱ� ������: ��������� rhs��ŭ ������Ų��. @param rhs ����ġ
			void				operator+=(int rhs)						{	AddRef(rhs);}

	//! @brief ���Կ�����
			ICGReferenceable&	operator=(const ICGReferenceable&)		{	return *this;}

	// Definitions) �⺻ ���� Class
			class NoAct;
			class Delete;

	// Debug)
			CGNEW_DEBUG_INFO_DECLARE


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) Release�� 0�� �Ǵ� ���� Release�� ���� �ҷ����� �Լ�.
	virtual	void				OnFinalRelease()						{}

	// Debug) Debug�� ���� ȣ��Ǵ� ���Լ��̴�.
	//        - Reference Count�� ��� �������� �����ǰ� �����ϴ� �� Ȯ���ϴ� �뵵�� �� ���Լ��� �������� �� �ִ�.
	//        - Release���� �� �Լ� ��ü�� ȣ����� �ʴ´�.
	virtual	void				_Debug_OnAddReferenceCount(int /*_count*/){}
	virtual	void				_Debug_OnReleaseReferenceCount()		{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			ATOMIC<int>			m_Counter;
			bool				m_bDisuse;
};

// Releaser) 
class ICGReferenceable::NoAct : virtual public ICGDisposable
{
public: 
	virtual ~NoAct() 
	{
	}

	virtual void ProcessDispose() override 
	{
	}
};

class ICGReferenceable::Delete : virtual public ICGDisposable
{
public:
	virtual ~Delete() 
	{
	}

	virtual void ProcessDispose() override
	{
		delete this;
	}
};
