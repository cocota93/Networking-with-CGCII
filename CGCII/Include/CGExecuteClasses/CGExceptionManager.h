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

namespace CGException
{

//-----------------------------------------------------------------------------
/**

 @class		Manager
 @brief		예외 관리자이다.
 @todo		
 @ref		
 @details	\n
 Access Violation과 같은 SEH에 의해 발생하는 Exception을 관리하는 매니저이다.
 일반적으로 예외가 발생했을 때 덤프를 남기는 역할을 수행한다.
 내부적으로 같은 주소에서 발생하는 예외에 대해서는 중복적으로 Dump를 남기지 않는다.
 SetDumpCountLimit()를 사용해 남기는 최대의 Dump수를 설정할 수 있다.
 (기본값은 DEFAULT_MAX_EXCEPTIONLIMIT:4096개)
 SetDumpType()를 사용하여 남기는 Dump의 내용을 설정할 수 있다.
 (기본값은 DEFAULT_MINIDUMP_TYPE:MINIDUMP_TYPE_MINI)

*///-----------------------------------------------------------------------------
class Manager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	public						NCGDispatchable,
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
		typedef	std::map<void*, CGException::CGDUMP_INFO>::const_iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			Manager(MINIDUMP_TYPE _typeDump=DEFAULT_MINIDUMP_TYPE, size_t p_iDumpMaxCount=DEFAULT_MAX_EXCEPTIONLIMIT);
	virtual ~Manager();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) SEH Enable/Disable
	//! @brief SEH 가능 여부를 설정한다. @param _bEnable SEH 가능 여부
			void				EnableSEH(bool _bEnable=true);
	//! @brief SEH을 끈다.
			void				DisableSEH();
	//! @brief SEH을 가능 여부를 확인한다. @return true 가능 @return false 불가능
			bool				IsSEHEnabled() const;
	//! @brief 현재 쓰레드에 SEH 핸들이 가능하도록 설정한다.
			void				SetSEHToThread();
	//! @brief 잘못된 인자 핸들러를 설정한다.
			void				SetInvalidParameterHandle();

	// 2) Dump Type (Mini Dump의 Type)
	//! @brief 미니 덤프 형태를 설정한다. @param _typeDump 미니 덤프 형태
			void				SetDumpType(MINIDUMP_TYPE _typeDump)	{	m_typeDumpType=_typeDump;}
	//! @brief 설정된 미니 덤프 형태를 얻는다.@ return 설정된 미니 덤프 형태
			MINIDUMP_TYPE		GetDumpType() const						{	return m_typeDumpType;}

	// 3) Dump Limit (저장할 최대 Dump file의 갯수)
	//! @brief 최대 미니 덤프 수를 설정한다. @param _iLimit 최대 미디 덤프 수
			void				SetDumpCountLimit(size_t _iLimit)		{	m_countDumpLimit=_iLimit;}
	//! @brief 설정된 최대 미니 덤프 수를 얻는다. @ eturn 최대 미디 덤프 수	
			size_t				GetDumpCountLimit() const				{	return m_countDumpLimit;}

	// 4) MiniDump Path (저장할 Dump file의 경로)
	//! @brief 미니 덤프가 저장될 패스를 설정한다.
			void				SetMiniDumpPath(const _CHAR* p_strPath)	{	m_strDumpPath = p_strPath; }
			const _STRING&	GetMiniDumpPath() const					{	return m_strDumpPath; }

	// 4) Dump Count(현재 저장된 Dump file의 갯수)
	//! @brief 현재 저장된 미니 덤프 수를 얻는다. @return 미디 덤프 수
			size_t				GetDumpCount() const					{	return m_countDumpNow;}

	// 5) Iterator용.
	//! @brief 락 객체를 얻는다.
								operator lockable&()					{	return m_mapDump;}
	//! @brief 최초 덤프 반복자. @return 첫번째 덤프 반복자
			ITERATOR			begin()									{	return m_mapDump.begin();}
	//! @brief 마지막 덤프 반복자. @return 마지막 덤프 반복자
			ITERATOR			end()									{	return m_mapDump.end();}


	// 6) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '예외 관리자 싱글턴 객체'를 설정한다. @ param _pInstance 설정할 '예외 관리자 싱글턴 객체'
	static	void				SetInstance(Manager* _pInstance);
	//! @brief '예외 관리자 싱글턴 객체'를 리셋한다.
	static	void				ResetInstance();

	// 7) ProcessExceptionMessage;
			void				DispatchAllExceptionMessage();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	//! @brief 예외가 발생되었을 때 처리 내용을 정의한 함수
	virtual	void				ProcessException(LPEXCEPTION_POINTERS _pException);

	//! @brief 잘못된 인자가 발생했을 때 처리 내용을 정의한 함수
	virtual	void				ProcessInvalidParameter(const wchar_t* _expression, const wchar_t* _function, const wchar_t* _file, unsigned int _line, uintptr_t _pReserved);
	

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) EnableSEH
			bool				m_bEnableSEH;

	// 2) Dump 관련
			size_t				m_countDumpLimit;
			size_t				m_countDumpNow;
			MINIDUMP_TYPE		m_typeDumpType;
			LOCKABLE<std::map<void*, CGException::CGDUMP_INFO>>	m_mapDump;
			circular_list<void*> m_listExceptionEvent;
			_STRING				m_strDumpPath;

	// 3) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

public:
	// 4) Destroy
	virtual	bool				Destroy() override;

protected:
	//! @brief 덤프를 생성한다. @param _strDumpFile 덤프 파일 이름 @param _pException 예외 정보
			bool				CreateDump(_In_z_ const _CHAR* _strDumpFile, LPEXCEPTION_POINTERS _pException);

	static	void				TranslatorFunction(uint32_t, LPEXCEPTION_POINTERS _pException);
	static	void				InvalidParameterHandler(const wchar_t * _expression, const wchar_t* _function, const wchar_t * _file, unsigned int _line, uintptr_t _pReserved);
};


// ----------------------------------------------------------------------------
//
//  Functions
//
// ----------------------------------------------------------------------------
void			EnableSEH(bool bEnable=true);
void			DisableSEH();
bool			IsSEHEnabled();
void			SetSEHToThread();
bool			SnapDump(_In_opt_z_ const _CHAR* _strDumpFile=nullptr, MINIDUMP_TYPE _typeDump=DEFAULT_MINIDUMP_TYPE);
bool			SnapDump(_In_opt_z_ const _CHAR_SUB* _strDumpFile, MINIDUMP_TYPE _typeDump=DEFAULT_MINIDUMP_TYPE);

}

