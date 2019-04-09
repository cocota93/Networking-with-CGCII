//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server Log Classes                             *
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
// CCGFile
//
// 1. CCGFile은~
//     Log처리를 위한 것이다.
//
//-----------------------------------------------------------------------------
#define	MAX_LENGTH_OF_FILENAME	1024

class CCGFile : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable							// (I) Executable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGFile();
	virtual ~CCGFile();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Open/Close
			bool				Open(_In_z_ const _CHAR* _strFileName);
			bool				Open(_In_z_ const _CHAR_SUB* _strFileName);
			bool				Close();

	// 2) Write File한다.
			bool				Write(_In_ const CCGBuffer& _pBuffer);
			bool				Write(_In_z_ const _CHAR* _strFormat, ...);
			bool				Write(_In_z_ const _CHAR_SUB* _strFormat, ...);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Buffer
			LOCKABLE<>			m_csBuffer;
			CCGBuffer			m_bufferWriting;
			int					m_iWritingCount;
			circular_list<CCGBuffer> m_queueBuffer;

	// 2) File
			HANDLE				m_hFile;
			_CHAR				m_strFileName[MAX_LENGTH_OF_FILENAME];

	// 3) CGFile
			class CExecutorWriteReserve;

protected:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};
