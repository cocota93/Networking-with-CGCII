//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               File Classes                                *
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
//
// CGArchive::CFile
//
// 1. CGArchive::CFile란!
//    1) File을 Access하기 위한 Class이다.
//    2) 기본적으로 ICGArchive를 상속받은 Class이다.
//
// 2. CGArchive::CFile Function
//    1) Open/Close	File을 열고 다는 함수이다.
//    2) Read/Write	열린 파일을 Read/Write를 수행하는 함수이다.
//
// 3. 주의 사항
//	  1) Open이 되지 않았을 때는 기본적으로 return값이 FALSE로 돌아온다.
//	  2) 하지만 Read와 Write의 실패의 경우 Exception을 던지믈 그것을 주의해야 한다.
//
//-----------------------------------------------------------------------------
#define	MAX_LENGTH_OF_FILENAME	1024

namespace CGArchive
{

class CFile :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGArchive,								//     Archive
	virtual	public				ICGExecutable							//     Completor
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CFile();
			CFile(_In_z_ const _CHAR* _strFileName, _In_ bool bSave=false);
			CFile(_In_z_ const _CHAR_SUB* _strFileName, _In_ bool bSave=false);
	virtual ~CFile();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
			bool				Open(_In_z_ const _CHAR* _strFileName, _In_ bool bSave=false);
			bool				Open(_In_z_ const _CHAR_SUB* _strFileName, _In_ bool bSave=false);
			bool				OpenForLoad(_In_z_ const _CHAR* _strFileName);
			bool				OpenForLoad(_In_z_ const _CHAR_SUB* _strFileName);
			bool				OpenForSave(_In_z_ const _CHAR* _strFileName);
			bool				OpenForSave(_In_z_ const _CHAR_SUB* _strFileName);
			void				Close();
			
	virtual	uint32_t			GetStatus() const								{	return m_dwStatus;}
	virtual	uint32_t			SetStatus(_In_ uint32_t _Status);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	// 1) Open
			bool				ProcessOpen(_In_z_ const _CHAR* _strFileName, _In_ uint32_t p_dwDesiredAccess=GENERIC_READ, _In_ uint32_t p_dwShareMode=FILE_SHARE_READ, _In_opt_ LPSECURITY_ATTRIBUTES p_lpSecurityAttributes=nullptr, _In_ uint32_t p_dwCreationDisposition=OPEN_EXISTING, _In_ uint32_t p_dwFlagsAndAttributes=FILE_ATTRIBUTE_NORMAL, _In_opt_ HANDLE p_hTemplateFile=nullptr);

	// 2) ProcessRead/ProcessWrite
	virtual size_t				ProcessRead(_Inout_ CCGBuffer& _Buffer);
	virtual size_t				ProcessWrite(_In_ const CCGBuffer& _Buffer);

	virtual size_t				RequestProcessWrite(_In_reads_bytes_(_Bytes) const void* _pData, _In_ size_t _Bytes);

	// 3) I/O가 완료 되었을 때 불려지는 함수.
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

protected:
	// 4) File Attribute
			HANDLE				m_hFile;
			_CHAR				m_strFileName[MAX_LENGTH_OF_FILENAME];

	// 5) Status(Read or Write)
			uint32_t				m_dwStatus;

	// 6) For Write
			size_t				m_dwPosition;
			list<CCGBuffer>		m_listQueued;
			CCGBuffer			m_bufferSended;
			LOCKABLE<>			m_csBuffer;
};


}