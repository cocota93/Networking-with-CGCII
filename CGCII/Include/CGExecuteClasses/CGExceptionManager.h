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

namespace CGException
{

//-----------------------------------------------------------------------------
/**

 @class		Manager
 @brief		���� �������̴�.
 @todo		
 @ref		
 @details	\n
 Access Violation�� ���� SEH�� ���� �߻��ϴ� Exception�� �����ϴ� �Ŵ����̴�.
 �Ϲ������� ���ܰ� �߻����� �� ������ ����� ������ �����Ѵ�.
 ���������� ���� �ּҿ��� �߻��ϴ� ���ܿ� ���ؼ��� �ߺ������� Dump�� ������ �ʴ´�.
 SetDumpCountLimit()�� ����� ����� �ִ��� Dump���� ������ �� �ִ�.
 (�⺻���� DEFAULT_MAX_EXCEPTIONLIMIT:4096��)
 SetDumpType()�� ����Ͽ� ����� Dump�� ������ ������ �� �ִ�.
 (�⺻���� DEFAULT_MINIDUMP_TYPE:MINIDUMP_TYPE_MINI)

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
	//! @brief SEH ���� ���θ� �����Ѵ�. @param _bEnable SEH ���� ����
			void				EnableSEH(bool _bEnable=true);
	//! @brief SEH�� ����.
			void				DisableSEH();
	//! @brief SEH�� ���� ���θ� Ȯ���Ѵ�. @return true ���� @return false �Ұ���
			bool				IsSEHEnabled() const;
	//! @brief ���� �����忡 SEH �ڵ��� �����ϵ��� �����Ѵ�.
			void				SetSEHToThread();
	//! @brief �߸��� ���� �ڵ鷯�� �����Ѵ�.
			void				SetInvalidParameterHandle();

	// 2) Dump Type (Mini Dump�� Type)
	//! @brief �̴� ���� ���¸� �����Ѵ�. @param _typeDump �̴� ���� ����
			void				SetDumpType(MINIDUMP_TYPE _typeDump)	{	m_typeDumpType=_typeDump;}
	//! @brief ������ �̴� ���� ���¸� ��´�.@ return ������ �̴� ���� ����
			MINIDUMP_TYPE		GetDumpType() const						{	return m_typeDumpType;}

	// 3) Dump Limit (������ �ִ� Dump file�� ����)
	//! @brief �ִ� �̴� ���� ���� �����Ѵ�. @param _iLimit �ִ� �̵� ���� ��
			void				SetDumpCountLimit(size_t _iLimit)		{	m_countDumpLimit=_iLimit;}
	//! @brief ������ �ִ� �̴� ���� ���� ��´�. @ eturn �ִ� �̵� ���� ��	
			size_t				GetDumpCountLimit() const				{	return m_countDumpLimit;}

	// 4) MiniDump Path (������ Dump file�� ���)
	//! @brief �̴� ������ ����� �н��� �����Ѵ�.
			void				SetMiniDumpPath(const _CHAR* p_strPath)	{	m_strDumpPath = p_strPath; }
			const _STRING&	GetMiniDumpPath() const					{	return m_strDumpPath; }

	// 4) Dump Count(���� ����� Dump file�� ����)
	//! @brief ���� ����� �̴� ���� ���� ��´�. @return �̵� ���� ��
			size_t				GetDumpCount() const					{	return m_countDumpNow;}

	// 5) Iterator��.
	//! @brief �� ��ü�� ��´�.
								operator lockable&()					{	return m_mapDump;}
	//! @brief ���� ���� �ݺ���. @return ù��° ���� �ݺ���
			ITERATOR			begin()									{	return m_mapDump.begin();}
	//! @brief ������ ���� �ݺ���. @return ������ ���� �ݺ���
			ITERATOR			end()									{	return m_mapDump.end();}


	// 6) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '���� ������ �̱��� ��ü'�� �����Ѵ�. @ param _pInstance ������ '���� ������ �̱��� ��ü'
	static	void				SetInstance(Manager* _pInstance);
	//! @brief '���� ������ �̱��� ��ü'�� �����Ѵ�.
	static	void				ResetInstance();

	// 7) ProcessExceptionMessage;
			void				DispatchAllExceptionMessage();


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	//! @brief ���ܰ� �߻��Ǿ��� �� ó�� ������ ������ �Լ�
	virtual	void				ProcessException(LPEXCEPTION_POINTERS _pException);

	//! @brief �߸��� ���ڰ� �߻����� �� ó�� ������ ������ �Լ�
	virtual	void				ProcessInvalidParameter(const wchar_t* _expression, const wchar_t* _function, const wchar_t* _file, unsigned int _line, uintptr_t _pReserved);
	

// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) EnableSEH
			bool				m_bEnableSEH;

	// 2) Dump ����
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
	//! @brief ������ �����Ѵ�. @param _strDumpFile ���� ���� �̸� @param _pException ���� ����
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

