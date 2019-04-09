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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once


//-----------------------------------------------------------------------------
// Definitions) 
//-----------------------------------------------------------------------------
// Prototype)
class ICGMessageable;

//-----------------------------------------------------------------------------
// 1. CGMSG- UI Notify¿ë
//-----------------------------------------------------------------------------
typedef struct CGMSG_UI : public CGMSG
{
public:
			CGMSG_UI()					{}
			CGMSG_UI(ICGMessageable* _pSource, uint32_t _Message, WPARAM _wParam=0, LPARAM _lParam=0) : CGMSG(_Message), pSource(_pSource), wParam(_wParam), lParam(_lParam)  	{}
public:
			ICGMessageable*		pSource;
			WPARAM				wParam;
			LPARAM				lParam;
} *LPCGMSG_UI;


//-----------------------------------------------------------------------------
// 2. Attribute
//-----------------------------------------------------------------------------
#define	ATTRIBUTE_READ					0x10000000
#define	ATTRIBUTE_WRITE					0x20000000

struct CGMSG_ATTRIBUTE : public CGMSG
{
public:
	CGMSG_ATTRIBUTE() : CGMSG(CGMESSAGE::ATTRIBUTE::BASE)			{}
	CGMSG_ATTRIBUTE(uint32_t p_dwAttribute) : CGMSG(CGMESSAGE::ATTRIBUTE::BASE), dwAttributeID(p_dwAttribute) {}
	CGMSG_ATTRIBUTE(uint32_t message, uint32_t p_dwAttribute) : CGMSG(message), dwAttributeID(p_dwAttribute) {}
public:
	uint32_t			dwAttributeID;
};

template <class TVALUE>
struct CGMSG_ATTRIBUTE_VALUE : public CGMSG_ATTRIBUTE
{
public:
	CGMSG_ATTRIBUTE_VALUE()			{}
	CGMSG_ATTRIBUTE_VALUE(uint32_t p_dwAttribute) : CGMSG_ATTRIBUTE(p_dwAttribute) {}
	CGMSG_ATTRIBUTE_VALUE(uint32_t p_dwAttribute, TVALUE p_Value) : CGMSG_ATTRIBUTE(p_dwAttribute), Value(p_Value) {}
public:
	TVALUE				Value;
};


//-----------------------------------------------------------------------------
// 3. Command
//-----------------------------------------------------------------------------
template<class TPARAM>
class CGMSG_COMMAND_PARAM : public CGMSG_COMMAND
{
public:
	CGMSG_COMMAND_PARAM(uint32_t _Message, uint32_t _Command, TPARAM* _pSource=nullptr) : CGMSG_COMMAND(_Message, _Command), sParam(_pSource) {}

public:
	TPARAM				sParam;
};

template<class TPARAM>
class CGMSG_COMMAND_PARAM_PTR : public CGMSG_COMMAND
{
public:
	CGMSG_COMMAND_PARAM_PTR(uint32_t _Message, uint32_t _Command, TPARAM* _pSource=nullptr) : CGMSG_COMMAND(_Message, _Command), pParam(_pSource) {}

public:
	CGPTR<TPARAM>		pParam;
};

template<class TSOURCE>
class CGMSG_COMMAND_PTRLIST : public CGMSG_COMMAND
{
public:
	CGMSG_COMMAND_PTRLIST(uint32_t _Message, uint32_t p_dwCommand) : CGMSG_COMMAND(_Message, p_dwCommand) { vectorSource.reserve(32);}

public:
	vector<CGPTR<TSOURCE>>	vectorSource;

	void				Add(TSOURCE* _pSource)	{	vectorSource.push_back(_pSource);}
};


//-----------------------------------------------------------------------------
// 4. 
//-----------------------------------------------------------------------------
const int	CGFUNCTION_ATTACH			 = 1;
const int	CGFUNCTION_DETACH			 = 2;
										 
const int	CGFUNCTION_FIND				 = 3;
const int	CGFUNCTION_FIND_BY_NAME		 = 4;
const int	CGFUNCTION_FIND_BY_TYPE		 = 5;
const int	CGFUNCTION_FIND_BY_INDEX	 = 6;
const int	CGFUNCTION_SEARCH_BY_TYPE	 = 7;
										 
namespace CGCOMMAND						 
{										 
	const int	PARENT					 = 1;
	const int	PARENT_TRANSFORM_MATRIX	 = 2;
	const int	WORLD_TRANSFORM_MATRIX	 = 3;
	const int	LOCAL_TRANSFORM_MATRIX	 = 4;
	const int	SOURCE					 = 5;
	const int	SOURCE_TRANSFORM_MATRIX	 = 6;
	const int	TARGET					 = 7;
	const int	TARGET_TRANSFORM_MATRIX	 = 8;
	const int	TARGET_CAMERA			 = 9;
	const int	TARGET_LIGHT			 = 10;

	const int	APPLIER_EFFECT			 = 16;
	const int	APPLIER_TEXTURE			 = 17;
	const int	APPLIER_MATERIAL		 = 18;
	const int	APPLIER					 = 19;

	const int	RESOURCE				 = 24;
	const int	RESOURCE_MESH			 = 25;
	const int	RESOURCE_keyFRAME		 = 26;
	const int	RESOURCE_TEXTURE		 = 27;
}

template<typename TSOURCE>
class CGMSG_COMMAND_PARAM_PTR_TYPE : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_COMMAND_PARAM_PTR_TYPE(uint32_t _Message, uint32_t _Command, int _Type, TSOURCE* _pSource=nullptr) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(_Message, _Command), iType(_Type), pSource(_pSource) {}

public:
	int					iType;
	CGPTR<TSOURCE>		pSource;
};


template<typename TSOURCE>
class CGMSG_FIND_BY_NAME : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_FIND_BY_NAME(uint32_t _Command, _In_z_ const _CHAR* _strName, uint32_t _Mask=0xffffffff, bool _bRecursive=true) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_FUNCTION, _Command), strName(_strName), Mask(_Mask), bRecursive(_bRecursive) {}

public:
	const _CHAR*		strName;
	uint32_t			Mask;
	bool				bRecursive;
};

template<typename TSOURCE>
class CGMSG_FIND_BY_TYPE : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_FIND_BY_TYPE(uint32_t _Type, bool _bRecursive=true) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::MEMBER_FUNCTION, CGFUNCTION_FIND_BY_TYPE), dwType(_Type), bRecursive(_bRecursive) {}

public:
	uint32_t			dwType;
	bool				bRecursive;
};

template<typename TSOURCE>
class CGMSG_FIND_BY_INDEX : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_FIND_BY_INDEX(int _Index, bool _bRecursive=true) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::MEMBER_FUNCTION, CGFUNCTION_FIND_BY_INDEX), iIndex(_Index), bRecursive(_bRecursive) {}

public:
	int					iIndex;
	bool				bRecursive;
};

template<typename TSOURCE>
class CGMSG_SEARCH_BY_NAME : public CGMSG_COMMAND_PTRLIST<TSOURCE>
{
public:
	CGMSG_SEARCH_BY_NAME(uint32_t _Command, _In_z_ const _CHAR* _strName, uint32_t _Mask, bool _bRecursive=true) : CGMSG_COMMAND_PTRLIST<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_FUNCTION, _Command), strName(_strName), Mask(_Mask), bRecursive(_bRecursive) {}

public:
	const _CHAR*		strName;
	uint32_t			Mask;
	bool				bRecursive;
};

template<typename TSOURCE>
class CGMSG_SEARCH_BY_TYPE : public CGMSG_COMMAND_PTRLIST<TSOURCE>
{
public:
	CGMSG_SEARCH_BY_TYPE(uint32_t _Command, uint32_t _Type, uint32_t _Mask=0xffffffff, bool _bRecursive=true) : CGMSG_COMMAND_PTRLIST<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_FUNCTION, _Command), dwType(_Type), dwMask(_Mask), bRecursive(_bRecursive) {}

public:
	uint32_t			dwType;
	uint32_t			dwMask;
	bool				bRecursive;
};
				  

//-----------------------------------------------------------------------------
// 5. Set/Reset/Get
//-----------------------------------------------------------------------------
template<class TSOURCE>
class CGMSG_SET : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_SET(int _Index, TSOURCE* _Object) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_SET, _Index, _Object), bResult(false) {}

public:
	bool				bResult;
};

template<class TSOURCE>
class CGMSG_RESET : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_RESET(int _Index) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_RESET, _Index), bResult(false) {}

public:
	bool				bResult;
};

template<class TSOURCE>
class CGMSG_GET : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_GET(int _Index) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_GET, _Index) {}

public:
};
			  
template<class TSOURCE>
class CGMSG_FUNCTION : public CGMSG_COMMAND_PARAM<TSOURCE>
{
public:
	CGMSG_FUNCTION(uint32_t _Command, const TSOURCE& _Source) : CGMSG_COMMAND_PARAM<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_FUNCTION, _Command, _Source) {}
};

template<typename TSOURCE>
class CGMSG_FUNCTION_PTR : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_FUNCTION_PTR(uint32_t _Command, TSOURCE* _pSource=nullptr) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::MEMBER_FUNCTION, _Command, _pSource)	{}
};


template<typename TSOURCE>
class CGMSG_AUTOMATION : public CGMSG_COMMAND_PARAM<TSOURCE>
{
public:
	CGMSG_AUTOMATION(uint32_t _Command, const TSOURCE& _Source) : CGMSG_COMMAND_PARAM<TSOURCE>(CGMESSAGE::AUTOMATION::BASE, _Command, _Source) {}
};

template<typename TSOURCE>
class CGMSG_AUTOMATION_PTR : public CGMSG_COMMAND_PARAM_PTR<TSOURCE>
{
public:
	CGMSG_AUTOMATION_PTR(uint32_t _Command, TSOURCE* _pSource=nullptr) : CGMSG_COMMAND_PARAM_PTR<TSOURCE>(CGMESSAGE::AUTOMATION::BASE, _Command, _pSource)	{}
};

				   
//-----------------------------------------------------------------------------
// 6. INIT by String
//-----------------------------------------------------------------------------
struct SETTING_VALUE
{
public:
	const _CHAR*	strKey;
	const _CHAR*	strValue;

	vector<SETTING_VALUE>	vectorChild;

public:
	SETTING_VALUE();
	SETTING_VALUE(const _CHAR* _strSetting);

	void			Initialize(const _CHAR* _strSetting);
	const SETTING_VALUE* Find(const _CHAR* _strSetting) const;
};


//-----------------------------------------------------------------------------
// 7. INIT by String
//-----------------------------------------------------------------------------
namespace CGMESSAGE
{
	const uint32_t	STRING	 = (CODE_TYPE::INIT | CODE_TYPE::TAIL_0 | 1);
}

struct CGMSG_STRING : public CGMSG
{
public:
	CGMSG_STRING() : CGMSG(CGMESSAGE::STRING), strValue(nullptr)	{}
	CGMSG_STRING(LPCOLESTR _strSetting) : CGMSG(CGMESSAGE::STRING), strValue(_strSetting) {}
	CGMSG_STRING(uint32_t _message) : CGMSG(_message), strValue(nullptr) {}
	CGMSG_STRING(uint32_t _message, LPCOLESTR _strSetting) : CGMSG(_message), strValue(_strSetting) {}

public:
	LPCOLESTR	strValue;
};


//-----------------------------------------------------------------------------
// 8. CONTEXT
//-----------------------------------------------------------------------------
class CContext
{
public:
			_STRING				strKey;
			_STRING*			strValue;
			CContext*			pParent;
			bool				bValid;
			std::map<_STRING, CContext>	mapNode;

public:
	CContext();
	CContext(const char* _strKey, const char* _strValue, CContext* _pParent = nullptr);
	CContext(const wchar_t* _strKey, const wchar_t* _strValue, CContext* _pParent = nullptr);
	CContext(const _STRING& _strKey);
	CContext(const _STRING_SUB& _strKey);
	CContext(const CContext& _Copy);
	CContext(CContext&& _Move);
	~CContext();

public:
			bool				read_from_JSON_file(const char* _strFileName);
			bool				read_from_JSON_file(const wchar_t* _strFileName);
			bool				read_from_JSON_string(const char* _strData);
			bool				read_from_JSON_string(const wchar_t* _strData);
			bool				read_from_INI_file(const char* _strFileName);
			bool				read_from_INI_file(const wchar_t* _strFileName);
			bool				read_from_Registery();
			bool				write_to_INI_file(const char* _strFileName);
			bool				write_to_INI_file(const wchar_t* _strFileName);
			bool				write_to_JSON_file(const char* _strFileName);
			bool				write_to_JSON_file(const wchar_t* _strFileName);
			bool				write_to_Registery();

			CContext&			insert(const char* _key, const char* _value = nullptr);
			CContext&			insert(const wchar_t* _key, const wchar_t* _value = nullptr);
			bool				erase(const char* _key);
			bool				erase(const wchar_t* _key);

			CContext&			find(const char* _key);
			const CContext&		find(const char* _key) const;
			CContext&			find(const wchar_t* _key);
			const CContext&		find(const wchar_t* _key) const;

			void				clear();
			void				swap(CContext& _rhs)	{ strKey.swap(_rhs.strKey); SWAP(strValue, _rhs.strValue); SWAP(pParent, _rhs.pParent); SWAP(bValid, _rhs.bValid); mapNode.swap(_rhs.mapNode);}

			CContext&			operator [] (char* _key);
			const CContext&		operator [] (char* _key) const;
			CContext&			operator [] (const char* _key);
			const CContext&		operator [] (const char* _key) const;
			CContext&			operator [] (wchar_t* _key);
			const CContext&		operator [] (wchar_t* _key) const;
			CContext&			operator [] (const wchar_t* _key);
			const CContext&		operator [] (const wchar_t* _key) const;

			CContext&			operator =	(const char* _rhs);
			CContext&			operator =	(const wchar_t* _rhs);
			CContext&			operator =	(const _STRING& _rhs);
			CContext&			operator =	(const _STRING_SUB& _rhs);
			CContext&			operator =	(char _rhs);
			CContext&			operator =	(unsigned char _rhs);
			CContext&			operator =	(int16_t _rhs);
			CContext&			operator =	(uint16_t _rhs);
			CContext&			operator =	(int32_t _rhs);
			CContext&			operator =	(uint32_t _rhs);
			CContext&			operator =	(int64_t _rhs);
			CContext&			operator =	(uint64_t _rhs);
			CContext&			operator =	(float _rhs);
			CContext&			operator =	(double _rhs);

			CContext&			operator =  (const CContext& _rhs);
			CContext&			operator =  (CContext&& _rhs);

								operator const _CHAR*() const;
								operator _STRING() const;
								operator _STRING_SUB() const;
								operator char() const;
								operator unsigned char() const;
								operator int16_t() const;
								operator uint16_t() const;
								operator int32_t() const;
								operator uint32_t() const;
								operator int64_t() const;
								operator uint64_t() const;
								operator float() const;
								operator double() const;

private:
	void		_Validate();
};


class CONTEXT_REF
{
public:
			CONTEXT_REF() : m_pRef(nullptr)										{}
			CONTEXT_REF(CContext& _Ref) : m_pRef(&_Ref)							{}
			CONTEXT_REF(CContext* _pRef) : m_pRef(_pRef)						{}

			CContext*			get() const										{	return m_pRef;}

			bool				read_from_JSON_file(const char* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->read_from_JSON_file(_strFileName);}
			bool				read_from_JSON_file(const wchar_t* _strFileName){	if(m_pRef==nullptr) return false; return m_pRef->read_from_JSON_file(_strFileName);}
			bool				read_from_JSON_string(const char* _strData)		{	if(m_pRef==nullptr) return false; return m_pRef->read_from_JSON_string(_strData);}
			bool				read_from_JSON_string(const wchar_t* _strData)	{	if(m_pRef==nullptr) return false; return m_pRef->read_from_JSON_string(_strData);}
			bool				read_from_INI_file(const char* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->read_from_INI_file(_strFileName);}
			bool				read_from_INI_file(const wchar_t* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->read_from_INI_file(_strFileName);}
			bool				write_to_INI_file(const char* _strFileName)		{	if(m_pRef==nullptr) return false; return m_pRef->write_to_INI_file(_strFileName);}
			bool				write_to_INI_file(const wchar_t* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->write_to_INI_file(_strFileName);}
			bool				write_to_JSON_file(const char* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->write_to_JSON_file(_strFileName);}
			bool				write_to_JSON_file(const wchar_t* _strFileName)	{	if(m_pRef==nullptr) return false; return m_pRef->write_to_JSON_file(_strFileName);}

			CContext&			insert(const char* _key, const char* _value = nullptr) { if (m_pRef == nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->insert(_key, _value); }
			CContext&			insert(const wchar_t* _key, const wchar_t* _value = nullptr) { if (m_pRef == nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->insert(_key, _value); }
			bool				erase(const char* _key)							{	if(m_pRef==nullptr) return false; return m_pRef->erase(_key);}
			bool				erase(const wchar_t* _key)						{	if(m_pRef==nullptr) return false; return m_pRef->erase(_key);}

			CContext&			find(const char* _key)							{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->find(_key);}
			const CContext&		find(const char* _key) const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->find(_key);}
			CContext&			find(const wchar_t* _key)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->find(_key);}
			const CContext&		find(const wchar_t* _key) const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return m_pRef->find(_key);}

			void				clear()											{	if(m_pRef==nullptr) return; m_pRef->clear();}
			void				swap(CONTEXT_REF& _rhs)							{	SWAP(m_pRef, _rhs.m_pRef);}

			CContext&			operator [] (char* _key)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			const CContext&		operator [] (char* _key) const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			CContext&			operator [] (const char* _key)					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			const CContext&		operator [] (const char* _key) const			{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			CContext&			operator [] (wchar_t* _key)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			const CContext&		operator [] (wchar_t* _key) const				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			CContext&			operator [] (const wchar_t* _key)				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}
			const CContext&		operator [] (const wchar_t* _key) const			{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (*m_pRef)[_key];}

			CONTEXT_REF&		operator =	(const CONTEXT_REF& _rhs)			{	m_pRef=_rhs.m_pRef; return *this;}
			CContext&			operator =	(const char* _rhs)					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(const wchar_t* _rhs)				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(const _STRING& _rhs)				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(const _STRING_SUB& _rhs)			{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(char _rhs)							{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(unsigned char _rhs)				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(int16_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(uint16_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(int32_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(uint32_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(int64_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(uint64_t _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(float _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =	(double _rhs)						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}

			CContext&			operator =  (const CContext& _rhs)				{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}
			CContext&			operator =  (CContext&& _rhs)					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); (*m_pRef)=_rhs; return *m_pRef;}

								operator CContext&() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator const _CHAR*() const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator _STRING() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (const _STRING&)*m_pRef;}
								operator _STRING_SUB() const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return (const _STRING_SUB&)*m_pRef;}
								operator char() const							{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator unsigned char() const					{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator int16_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator uint16_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator int32_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator uint32_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator int64_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator uint64_t() const						{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator float() const							{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
								operator double() const							{	if(m_pRef==nullptr) throw CGException::CThrow_NoInitialized(); return *m_pRef;}
public:
			CContext*			m_pRef;
};

class CGMSG_CONTEXT : public CGMSG
{
public:
			CGMSG_CONTEXT() : CGMSG(CGMESSAGE::SYSTEM::CONTEXT), Setting(_Setting) {}

public:
			void				clear()							{	clear_setting(); clear_result();}
			void				clear_setting()					{	_Setting.clear(); }
			void				clear_result()					{	_Result.clear(); }
			void				swap(CGMSG_CONTEXT& _Context)	{	SWAP(message, _Context.message); SWAP(pSource, _Context.pSource); pLog.swap(_Context.pLog); _Setting.swap(_Context._Setting); _Result.swap(_Context._Result);}

public:
			CONTEXT_REF			Setting;
			CGPTR<ICGMessageable>	pLog;
private:
			CContext			_Setting;
			CContext			_Result;
};

