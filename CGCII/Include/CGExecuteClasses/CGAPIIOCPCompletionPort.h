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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
namespace CGAPI
{

//-----------------------------------------------------------------------------
/**

 @class		CIOCompletionPort
 @brief		IOCP를 Wrapping한 Class이다.
 @todo		
 @ref		
 @details	\n
			IOCP 객체 IOCP의 각종 조작을 수행할 수 있다.

*///-----------------------------------------------------------------------------
class CIOCompletionPort
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CIOCompletionPort();
	virtual	~CIOCompletionPort();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 'IOCP'가 생성되었는가 확인한다. @return true 생성되었다. @return false 생성되지 않았다.
			bool				IsCreated() const				{	return m_hCompletionPort!=NULL;}
	//! @brief 'IOCP'가 생성되었는가 확인한다. @return true 생성되지 않았다. @return false 생성되었다.
			bool				IsNULL() const					{	return m_hCompletionPort==NULL;}
	//! @brief 'IOCP'가 붙은 핸들 수를 얻는다. @return 붙어 있는 핸들 수
			size_t				GetAttached() const				{	return m_nAttached;}
	//! @brief 'IOCP'의 핸들을 얻는다. @return IOCP 핸들
			HANDLE				GetIOCPHandle() const			{	return m_hCompletionPort;}
			
	//! @brief 'IOCP를 생성한다. @return true 성공 @return false 실패
			bool				CreateCompletionPort();
	//! @brief 'IOCP를 생성한다. @return true 성공 @return false 실패
			bool				CreateCompletionPort(_In_ HANDLE _hFile, _In_ uintptr_t _CompletionKey, _In_ uint32_t _ConcurrentThreadCount=0);
	//! @brief 'IOCP를 파괴한다. @return true 성공 @return false 실패
			bool				DestroyCompletionPort();

	//! @brief 'IOCP에 걸린 모든 I/O를 취소한다. @return true 성공 @return false 실패
			bool				CancelIO();
	//! @brief 'IOCP에 걸린 I/O를 취소한다. @return true 성공 @return false 실패
			bool				CancelIO(_In_ HANDLE p_hHandle);

	//! @brief 'IOCP에 핸들을 붙인다. @return true 성공 @return false 실패
			bool				Attach(_In_ HANDLE _hExecutable);
	//! @brief 'IOCP에 핸들을 해제한다. @return true 성공 @return false 실패
			bool				Detach(_In_ HANDLE _hExecutable);

	//! @brief 'IOCP에 완료를 큐잉한다. @return true 성공 @return false 실패
			bool				PostCompletionStatus(_In_ uint32_t _bytesTransferred, _In_ uintptr_t _CompletionKey, _In_ ICGExecutable* _pExecutable);

	//! @brief 'IOCP에 큐잉된 완료정보를 얻어온다.
			uint32_t			GetQueued(_Out_ uint32_t& _pbytesTransfered, _Out_ LPOVERLAPPED& _pOverlapped, _In_ uint32_t _Milliseconds);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			ATOMIC<HANDLE>		m_hCompletionPort;				// I/O를 위한 CompletionPort
			ATOMIC<size_t>		m_nAttached;
};

}