//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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
namespace CGAPI
{

//-----------------------------------------------------------------------------
/**

 @class		CThreadPool
 @brief		������Ǯ Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� �ϳ��� �Լ��� ���� Thread�� �����ϵ��� �ϴ� class�̴�.
 Thread���� �����ؾ� �Ǵ� ������ ThreadRun()�Լ��� �����������ν� ����
 �Ѵ�.
 CreateThread�� ���� ������ Thread�� ThreadRon()�Լ��� ȣ���Ѵ�.
 CreateThread�Լ��� ȣ��Ǹ� OnThreadStart()�Լ��� ȣ��ǰ� ����ɶ�
 OnThreadTerminate()�Լ��� ȣ��ȴ�.
 IOCP�� ����� Network I/O�� �̰����� ���۵Ǿ���.

*///-----------------------------------------------------------------------------
class CThreadPool : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CThreadPool();
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief ������ ���ÿ� ������Ǯ�� �����Ѵ�. @param _Function ������ �Լ� @param _Arguments ����� ���޵� ���ڵ�
			template<class TFN, class... TARGS>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TARGS&&... _Arguments) : m_countThreadExist(0) { Begin(std::forward<TFN>(_Function), std::forward<TARGS>(_Arguments)...);}
	//! @brief ������ ���ÿ� ������Ǯ�� �����Ѵ�. @param _iCount ������ ������ �� @param _Function ������ �Լ� @param _Arguments ����� ���޵� ���ڵ�
			template<class TFN, class... TARGS>
			CThreadPool(int _iCount, TFN&& _Function, TARGS&&... _Arguments) : m_countThreadExist(0) { Begin(_iCount, std::forward<TFN>(_Function), std::forward<TARGS>(_Arguments)...); }

	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief ������ ���ÿ� ������Ǯ�� �����Ѵ�. @param _Function ������ �Լ� @param _Arguments ����� ���޵� ���ڵ�
			template<class TFN>
			CThreadPool(TFN&& _Function)								{	Begin(std::forward<TFN>(_Function));}
			template<class TFN, class TPARAM1>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1)					{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}
			template<class TFN, class TPARAM1, class TPARAM2>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1, TPARAM2&& p2)	{	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			CThreadPool(typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, TFN>::type&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM2&& p3){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}

	//! @brief ������ ���ÿ� ������Ǯ�� �����Ѵ�. @param _iCount ������ ������ �� @param _Function ������ �Լ� @param _Arguments ����� ���޵� ���ڵ�
			template<class TFN>
			CThreadPool(int _iCount, TFN&& _Function)					{	Begin(_iCount, std::forward<TFN>(_Function));}
			template<class TFN, class TPARAM1>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1)		{	Begin(_iCount, std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}
			template<class TFN, class TPARAM1, class TPARAM2>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2){	Begin(_iCount, std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			CThreadPool(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3){	Begin(std::forward<TFN>(_Function), _Function, std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif
	virtual	~CThreadPool();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Threa�� ����/��������
	#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
	//! @brief �����带 �����Ѵ�. @param _pFunction ������ �Լ� @param _Arguments ����� ���޵� ����
			template<class TFN, class... TARGS>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN&& _Function, TARGS&&... _Arguments);
	//! @brief �����带 �����Ѵ�. @param _iCount ������ ������ �� @param _Function ������ �Լ� @param _Arguments ����� ���޵� ����
			template<class TFN, class... TARGS>
			void				Begin(int _iCount, TFN&& _Function, TARGS&&... _Arguments);
	#elif _MSC_VER>=_MSC_VER_2010
	//! @brief �����带 �����Ѵ�. @param _pFunction ������ �Լ�
			template<class TFN>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function);
			template<class TFN, class TPARAM1>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1);
			template<class TFN, class TPARAM1, class TPARAM2>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2);
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
								Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3);
			
	//! @brief �����带 �����Ѵ�. @param _iCount ������ ������ �� @param _Function ������ �Լ�
			template<class TFN>
			void				Begin(int _iCount, TFN&& _Function)	{ for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function));}}
			template<class TFN, class TPARAM1>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1) {	for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1));}}
			template<class TFN, class TPARAM1, class TPARAM2>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2){ for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));}}
			template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
			void				Begin(int _iCount, TFN&& _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3){	for(int i=0; i<_iCount; ++i){	Begin(std::forward<TFN>(_Function), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));}}
	#else
		#error	"CGExecute: Unsupported compiler"
	#endif
	//! @brief ��� �����带 ��� ���������Ѵ�.
			void				TerminateAll();

	// 2) Thread ����
	//! @brief �������� ������ ��´�. @return ������ ����
			int					GetExistThreadCount() const				{	return m_countThreadExist;}
	//! @brief �������� ������ 0���ΰ�? @return true 0����. false 0���� �ƴϴ�.
			bool				empty() const							{	return GetExistThreadCount()==0;}
	//! @brief �������� ������ 0���� �ƴѰ�? @return true 0���� �ƴϴ�. false 0����.
			bool				exist() const							{	return GetExistThreadCount()!=0;}
			
	// Definitions)
	typedef	vector<CGPTR<CThread>>::iterator		ITERATOR;
	typedef	vector<CGPTR<CThread>>::const_iterator	CONST_ITERATOR;

	// 3) Iterator
	//! @brief �� ��ü�� ��´�.
								operator lockable&()					{	return m_vectorThread;}
	//! @brief ������ �ݺ��� ó�� �����带 ��´�. @return 'ó�� �ݺ���'
			ITERATOR			begin()									{	return m_vectorThread.begin();}
	//! @brief ������ �ݺ��� ó�� �����带 ��´�. @return 'ó�� �ݺ���'
			CONST_ITERATOR		begin() const							{	return m_vectorThread.begin();}
	//! @brief ������ �ݺ��� �� �����带 ��´�. @return '�� �ݺ���'
			ITERATOR			end()									{	return m_vectorThread.end();}
	//! @brief ������ �ݺ��� �� �����带 ��´�. @return '�� ������ �ݺ���'
			CONST_ITERATOR		end() const								{	return m_vectorThread.end();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	//! @brief ������ �Լ�
	template <class TTYPE>
	static	void				fnProcessThreadPool(CGAPI::CThreadPool* _pPool, CGAPI::CThread* _pThread, TTYPE* _pFunctor);

	//! @brief ������ ���� �� ó���� ������ �Լ�
			void				ProcessBeginThreadObject(CThread* _pThread);
	//! @brief ������ ���� �� ó���� ������ �Լ�
			void				ProcessEndThreadObject(CThread* _pThread);
private:
			LOCKABLE<vector<CGPTR<CThread>>>	m_vectorThread;
			ATOMIC<int>			m_countThreadExist;
};


template <class TTYPE>
void CGAPI::CThreadPool::fnProcessThreadPool(CGAPI::CThreadPool* _pPool, CGAPI::CThread* _pThread, TTYPE* _pFunctor)
{
	// 1) Hold
	CGPTR<CGAPI::CThread>		pThread	 = _pThread;
	CGPTR<CGAPI::CThreadPool>	pPool	 = _pPool;

	// 2) Functor ȣ���� ����ó��
	pPool->ProcessBeginThreadObject(pThread);

	// 3) Functor�� ȣ���Ѵ�.
	try
	{
		(*_pFunctor)();
	}
	catch (...)
	{
	}

	// 5) Functor�� �����.
	delete _pFunctor;

	// 4) Functor ȣ���� ����ó��
	pPool->ProcessEndThreadObject(pThread);
}

#if !defined(_MSC_VER) || _MSC_VER>=_MSC_VER_2013
template<class TFN, class... TARGS>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) �̸��� �ۼ�~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread ����
	LOCK(m_vectorThread)
	{
		// - Thread���� ������ Functor ����~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

		// - Thread�� �����Ѵ�.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - �̸��� �����Ѵ�.
		pThread->SetName(tempString);

		// - Thread List�� �߰��Ѵ�.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread�� �����Ѵ�.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Thread List���� �����Ѵ�.
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise)
			throw;
		}

	}
}

template<class TFN, class... TARGS>
void CGAPI::CThreadPool::Begin(int _iCount, TFN&& _Function, TARGS&&... _Arguments)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...))	TFUNCTOR;

	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable	 = dynamic_cast<ICGNameable*>(this);

	// 2) iCount����ŭ Thread ����
	LOCK(m_vectorThread)
	{
		for (int i=0; i<_iCount; ++i)
		{
			// - Thread���� ������ Functor ����~
			TFUNCTOR*	pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), DECAY_COPY(std::forward<TARGS>(_Arguments))...);

			// - Thread�� �����Ѵ�.
			CGPTR<CThread>	pThread = NEW<CThread>();

			// Declare)
			_CHAR	tempString[1024] = { 0 };

			// - �̸��� �ۼ�~
			CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable!=nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

			// - �̸��� �����Ѵ�.
			pThread->SetName(tempString);

			// - thread�� �ִ´�.
			m_vectorThread.push_back(pThread);

			// - AddRef
			AddRef();

			try
			{
				// - Thread�� �����Ѵ�.
				pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
			}
			catch(...)
			{
				// - Release
				NO_EXCEPTION_BEGIN
				{
					Release();
				}
				NO_EXCEPTION_END

				// - Thread List���� �����Ѵ�.
				NO_EXCEPTION_BEGIN
				{
					m_vectorThread.pop_back();
				}
				NO_EXCEPTION_END

				// Reraise)
				throw;
			}
		}
	}
}
#elif _MSC_VER>=_MSC_VER_2010
template<class TFN>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function))))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024]{};
	
	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) �̸��� �ۼ�~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread ����
	LOCK(m_vectorThread)
	{
		// - Thread���� ������ Functor ����~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)));

		// - Thread�� �����Ѵ�.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - �̸��� �����Ѵ�.
		pThread->SetName(tempString);

		// - thread�� �ִ´�.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread�� �����Ѵ�.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) �̸��� �ۼ�~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread ����
	LOCK(m_vectorThread)
	{
		// - Thread���� ������ Functor ����~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1));

		// - Thread�� �����Ѵ�.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - �̸��� �����Ѵ�.
		pThread->SetName(tempString);

		// - thread�� �ִ´�.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread�� �����Ѵ�.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1, class TPARAM2>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) �̸��� �ۼ�~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread ����
	LOCK(m_vectorThread)
	{
		// - Thread���� ������ Functor ����~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2));

		// - Thread�� �����Ѵ�.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - �̸��� �����Ѵ�.
		pThread->SetName(tempString);

		// - thread�� �ִ´�.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread�� �����Ѵ�.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}

template<class TFN, class TPARAM1, class TPARAM2, class TPARAM3>
typename std::enable_if<!std::is_arithmetic<typename std::decay<TFN>::type>::value, void>::type
CGAPI::CThreadPool::Begin(TFN _Function, TPARAM1&& p1, TPARAM2&& p2, TPARAM3&& p3)
{
	// Declare) 
	typedef decltype(std::bind(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2)))	TFUNCTOR;

	// Declare)
	_CHAR	tempString[1024] = { 0 };

	// 1) Nameable�� ��´�.
	ICGNameable*	pNameable = dynamic_cast<ICGNameable*>(this);

	// 2) �̸��� �ۼ�~
	CGSNPRINTF_S(tempString, _TRUNCATE, _CGTEXT("%s[%d]"), (pNameable != nullptr) ? pNameable->GetName() : _CGTEXT(""), static_cast<int>(GetExistThreadCount()));

	// 3) Thread ����
	LOCK(m_vectorThread)
	{
		// - Thread���� ������ Functor ����~
		TFUNCTOR*		pfunctorExecute = new TFUNCTOR(DECAY_COPY(std::forward<TFN>(_Function)), std::forward<TPARAM1>(p1), std::forward<TPARAM2>(p2), std::forward<TPARAM3>(p3));

		// - Thread�� �����Ѵ�.
		CGPTR<CThread>	pThread = NEW<CThread>();

		// - �̸��� �����Ѵ�.
		pThread->SetName(tempString);

		// - thread�� �ִ´�.
		m_vectorThread.push_back(pThread);

		// - AddRef
		AddRef();

		try
		{
			// - Thread�� �����Ѵ�.
			pThread->Begin(fnProcessThreadPool<TFUNCTOR>, this, pThread.get(), pfunctorExecute);
		}
		catch(...)
		{
			// - Release
			NO_EXCEPTION_BEGIN
			{
				Release();
			}
			NO_EXCEPTION_END

			// - Popback
			NO_EXCEPTION_BEGIN
			{
				m_vectorThread.pop_back();
			}
			NO_EXCEPTION_END

			// Reraise) 
			throw;
		}
	}
}
#else
		#error	"CGExecute: Unsupported compiler"
#endif


}
