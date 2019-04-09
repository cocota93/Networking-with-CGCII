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

 @class		CIOCompletionPort
 @brief		IOCP�� Wrapping�� Class�̴�.
 @todo		
 @ref		
 @details	\n
			IOCP ��ü IOCP�� ���� ������ ������ �� �ִ�.

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
	//! @brief 'IOCP'�� �����Ǿ��°� Ȯ���Ѵ�. @return true �����Ǿ���. @return false �������� �ʾҴ�.
			bool				IsCreated() const				{	return m_hCompletionPort!=NULL;}
	//! @brief 'IOCP'�� �����Ǿ��°� Ȯ���Ѵ�. @return true �������� �ʾҴ�. @return false �����Ǿ���.
			bool				IsNULL() const					{	return m_hCompletionPort==NULL;}
	//! @brief 'IOCP'�� ���� �ڵ� ���� ��´�. @return �پ� �ִ� �ڵ� ��
			size_t				GetAttached() const				{	return m_nAttached;}
	//! @brief 'IOCP'�� �ڵ��� ��´�. @return IOCP �ڵ�
			HANDLE				GetIOCPHandle() const			{	return m_hCompletionPort;}
			
	//! @brief 'IOCP�� �����Ѵ�. @return true ���� @return false ����
			bool				CreateCompletionPort();
	//! @brief 'IOCP�� �����Ѵ�. @return true ���� @return false ����
			bool				CreateCompletionPort(_In_ HANDLE _hFile, _In_ uintptr_t _CompletionKey, _In_ uint32_t _ConcurrentThreadCount=0);
	//! @brief 'IOCP�� �ı��Ѵ�. @return true ���� @return false ����
			bool				DestroyCompletionPort();

	//! @brief 'IOCP�� �ɸ� ��� I/O�� ����Ѵ�. @return true ���� @return false ����
			bool				CancelIO();
	//! @brief 'IOCP�� �ɸ� I/O�� ����Ѵ�. @return true ���� @return false ����
			bool				CancelIO(_In_ HANDLE p_hHandle);

	//! @brief 'IOCP�� �ڵ��� ���δ�. @return true ���� @return false ����
			bool				Attach(_In_ HANDLE _hExecutable);
	//! @brief 'IOCP�� �ڵ��� �����Ѵ�. @return true ���� @return false ����
			bool				Detach(_In_ HANDLE _hExecutable);

	//! @brief 'IOCP�� �ϷḦ ť���Ѵ�. @return true ���� @return false ����
			bool				PostCompletionStatus(_In_ uint32_t _bytesTransferred, _In_ uintptr_t _CompletionKey, _In_ ICGExecutable* _pExecutable);

	//! @brief 'IOCP�� ť�׵� �Ϸ������� ���´�.
			uint32_t			GetQueued(_Out_ uint32_t& _pbytesTransfered, _Out_ LPOVERLAPPED& _pOverlapped, _In_ uint32_t _Milliseconds);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
			ATOMIC<HANDLE>		m_hCompletionPort;				// I/O�� ���� CompletionPort
			ATOMIC<size_t>		m_nAttached;
};

}