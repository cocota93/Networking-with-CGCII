//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Factory Classes                              *
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
// Definitions for CGBufferClasses
//
//-----------------------------------------------------------------------------
class CCGBuffer;

namespace CGD
{

// CRC)
class CRC		
{
public:
	CRC() : m_pCRC(&CGEDC::DefaultCRC) {}
	CRC(CGEDC::CCRC* p) : m_pCRC(p) {}
public:
	CGEDC::CCRC*		m_pCRC;
};

// T) Compress
struct COMPRESS
{
public:
	CCGBuffer			m_buffer;
public:
	COMPRESS(const CCGBuffer& _Buffer) : m_buffer(_Buffer) {}
	COMPRESS(const CGD::buffer& _Buffer) : m_buffer(_Buffer) {}
	COMPRESS(int _Size, const void* _Buffer) : m_buffer(const_cast<void*>(_Buffer), _Size)	{}
};

struct SET_LENGTH
{
};

struct END_MESSSAGE
{
};

struct SET_LENGTH_CRC : public CRC
{
	SET_LENGTH_CRC() {}
	SET_LENGTH_CRC(CGEDC::CCRC* p) : CRC(p) {}
};

template <class S>
void*				_append_CRC(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _In_ const CGD::CRC& _CRC);
template <class S>
size_t				_append_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _Inout_ const CGD::buffer& _Original);
CCGBuffer			_extract_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ CGD::buffer* _Source);
CCGBuffer			_extract_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ CGD::ptr* _Source);
CCGBuffer			_front_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::buffer* _Source, _Inout_ int& _Offset);
CCGBuffer			_front_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::ptr* _Source, _Inout_ int& _Offset);


// Class for PUSH_FRONT)

// Class for PUSH_BACK)
template<>			class _AB<CRC>					{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const CRC& data)				{ return _append_CRC(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};
template<>			class _AB<COMPRESS>				{	public:	typedef	size_t t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const COMPRESS& data)			{ return _append_compress<S>(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data.m_buffer);}};
template<>			class _AB<SET_LENGTH>			{	public:	typedef	void t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SET_LENGTH& )			{ _CGD_BOUND_INFO_PASS; s->TEMPLATE front<uint32_t>()=s->len;}};
template<>			class _AB<END_MESSSAGE>			{	public:	typedef	void t;				template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SET_LENGTH& )			{ _CGD_BOUND_INFO_PASS; s->TEMPLATE front<uint32_t>()=s->len;}};
template<>			class _AB<SET_LENGTH_CRC>		{	public:	typedef	void *t;			template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s, const SET_LENGTH_CRC& data)	{ s->TEMPLATE front<uint32_t>()=s->len+sizeof(SIZE_OF_CRC); return _append_CRC(_CGD_BOUND_INFO_PASS _CGD_COMMA s, data);}};

// Class for POP_FRONT)
template<>			class _BF<COMPRESS>				{	public:	typedef	CCGBuffer t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* s)								{ return _extract_compress(_CGD_BOUND_INFO_PASS _CGD_COMMA s);}};

// Class for front)
template<>			class _RH<COMPRESS>				{	public:	typedef	CCGBuffer t;		template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* s, int& _Offset)			{ return _front_compress(_CGD_BOUND_INFO_PASS _CGD_COMMA s, _Offset);}};


inline void* _append_CRC(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ CGD::buffer* _Source, _In_ const CGD::CRC& _CRC)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) 
	ERROR_THROW_IF(_Source==nullptr, CGException::CThrow_InvalidArgument(), );

	// Check) _CRC.m_pCRC이 nullptr이면 안됀다.
	CGD_ASSERT(_CRC.m_pCRC!=nullptr, );

	// Check) 
	ERROR_THROW_IF(_CRC.m_pCRC==nullptr, CGException::CThrow_InvalidArgument(), );

	// 1) 위치를 얻는다.
	void* temp=reinterpret_cast<void*>(_Source->buf+_Source->len);

	// 2) CRC를 추가한다.
	_Source->TEMPLATE _append<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA _CRC.m_pCRC->get_CRC((LPBYTE)_Source->buf, _Source->len));

	// Return) 
	return temp;
}

template <class S>
inline size_t _append_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ S* _Source, _Inout_ const CGD::buffer& _Original)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) _Buffer이 nullptr이면 안된다.
	CGD_ASSERT(_Original.buf!=nullptr, );

	// Check) _Buffer이 nullptr이면 안된다.
	if(_Original.buf==nullptr) throw std::invalid_argument("buffer pointer is nullptr (" __FUNCTION__ ")");

	// Declare) 
	size_t	sizeCompressed	 = UINT_MAX;

	// Declare) 
	int	iResult;

	// 1) 압축한다.
	iResult	 = CGCompress::Compress(_Source->back()+sizeof(uint32_t)+sizeof(uint32_t), &sizeCompressed, _Original.buf, _Original.len);

	// Check) 
	if(iResult!=0) throw std::domain_error("Compression fail!! (" __FUNCTION__ ")");

	// 2) 압축된 데이터의 크기를 써넣는다.
	_Source->TEMPLATE _append_general<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA static_cast<uint32_t>(sizeCompressed));

	// 3) 원본 데이터의 크기를 써넣는다.
	_Source->TEMPLATE _append_general<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA static_cast<uint32_t>(_Original.len));

	// 4) 저장된 데이터 크기만큼 버퍼를 늘린다.(압축된 데이터 크기와 동일하다.)
	_Source->_append_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA sizeCompressed);

	// Return) 
	return	sizeCompressed;
}

inline CCGBuffer _extract_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ CGD::buffer* _Source)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) Buffer의 길이가 sizeof(uint32_t)+sizeof(uint32_t)보다 커야한다.
	if((sizeof(uint32_t)+sizeof(uint32_t))>_Source->len) throw std::length_error("Buffer is too short!! [0] (" __FUNCTION__ ")");

	// Declar) 
	int	tempOffset	 = 0;

	// 1) [압축된_크기]를 얻는다.
	size_t	sizeCompressed = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// Check) [압축된_크기]가 _Source->len보다 크면 안된다
	if(sizeCompressed>_Source->len) throw std::length_error("buffer overflow!! [1] (" __FUNCTION__ ")");
	
	// 2) [복원_크기]를 얻는다.
	size_t	sizeOriginal	 = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// 3) [복원_크기]만큼의 [복원_버퍼]를 할당받는다.
	CCGBuffer	_Dest	 = MEM_POOL_ALLOC(sizeOriginal);
	size_t		length	 = _Dest.len;

	// Declare) 
	int	iResult;

	// 3) [복원_버퍼]에 압축을 푼다.
	iResult	 = CGCompress::Uncompress(_Dest.buf, &length, _Source->TEMPLATE _front(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset), sizeCompressed);

	// Check) 압축 풀기이 실패했으면 Exception을 던진다.
	if(iResult != 0) throw std::domain_error("Uncompression fail!! (" __FUNCTION__ ")");

	// 4) Pop Front
	_Source->_extract_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset+sizeCompressed);

	// 5) Length Udpate
	_Dest.len	 = static_cast<uint32_t>(length);
	
	// Return) 
	return	_Dest;
}

inline CCGBuffer _extract_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ CGD::ptr* _Source)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK(_Source->m_ptr>=_bound.bound_lower && (_Source->m_ptr+sizeof(uint32_t)+sizeof(uint32_t))<=_bound.bound_upper);

	// Declar) 
	int	tempOffset	 = 0;

	// 1) [압축된_크기]를 얻는다.
	size_t	sizeCompressed = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK((_Source->m_ptr+sizeof(uint32_t)+sizeof(uint32_t)+sizeCompressed)<=_bound.bound_upper);

	// 2) [복원_크기]를 얻는다.
	size_t	sizeOriginal	 = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// 3) [복원_크기]만큼의 [복원_버퍼]를 할당받는다.
	CCGBuffer	_Dest	 = MEM_POOL_ALLOC(sizeOriginal);
	size_t		length	 = _Dest.len;

	// Declare) 
	int	iResult;

	// 3) [복원_버퍼]에 압축을 푼다.
	iResult	 = CGCompress::Uncompress(_Dest.buf, &length, _Source->TEMPLATE _front(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset), sizeCompressed);

	// Check) 압축 풀기이 실패했으면 Exception을 던진다.
	if(iResult != 0) throw std::domain_error("Uncompression fail!! (" __FUNCTION__ ")");

	// 4) Pop Front
	_Source->_extract_skip(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset+sizeCompressed);

	// 5) Length Udpate
	_Dest.len	 = static_cast<uint32_t>(length);
	
	// Return) 
	return	_Dest;
}


inline CCGBuffer _front_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::buffer* _Source, _Inout_ int& _Offset)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK(_Source->buf>=_bound.bound_lower && (_Source->buf+sizeof(uint32_t)+sizeof(uint32_t))<=_bound.bound_upper);

	// Check) Buffer의 길이가 sizeof(uint32_t)+sizeof(uint32_t)보다 커야한다.
	if(static_cast<int>(sizeof(uint32_t)+sizeof(uint32_t))>static_cast<int>(_Source->len))
	{
		throw	std::length_error("Buffer is too short!! [0] (" __FUNCTION__ ")");
	}

	// Declar) 
	int	tempOffset	 = _Offset;

	// 1) [압축된_크기]를 얻는다.
	size_t	sizeCompressed = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK((_Source->buf+sizeof(uint32_t)+sizeof(uint32_t)+sizeCompressed)<=_bound.bound_upper);

	// Check) [압축된_크기]가 _Source->len보다 크면 안된다
	if(sizeCompressed>_Source->len) throw std::length_error("buffer overflow!! [1] (" __FUNCTION__ ")");
	
	// 2) [복원_크기]를 얻는다.
	size_t	sizeOriginal	 = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// 3) [복원_크기]만큼의 [복원_버퍼]를 할당받는다.
	CCGBuffer	_Dest	 = MEM_POOL_ALLOC(sizeOriginal);
	size_t		length	 = _Dest.len;

	// Declare) 
	int	iResult;

	// 3) [복원_버퍼]에 압축을 푼다.
	iResult	 = CGCompress::Uncompress(_Dest.buf, &length, _Source->_front(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset), sizeCompressed);

	// Check) 압축 풀기이 실패했으면 Exception을 던진다.
	if(iResult != 0) throw std::domain_error("Uncompression fail!! (" __FUNCTION__ ")");

	// 4) Offset을 Udpate한다.
	_Offset	 = static_cast<int>(tempOffset+sizeCompressed);

	// 5) Length Udpate
	_Dest.len	 = static_cast<uint32_t>(length);

	// Return) 
	return	_Dest;
}

template <class S>
inline CCGBuffer _front_compress(_CGD_BOUND_INFO_PARAM _CGD_COMMA _In_ const CGD::ptr* _Source, _Inout_ int& _Offset)
{
	// Check) 
	CGD_ASSERT(_Source!=nullptr, );

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK(_Source->m_ptr>=_bound.bound_lower && (_Source->m_ptr+sizeof(uint32_t)+sizeof(uint32_t))<=_bound.bound_upper);

	// Declar) 
	int	tempOffset	 = _Offset;

	// 1) [압축된_크기]를 얻는다.
	size_t	sizeCompressed = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// Check) 압축 head부분의 Upper와 Lower Bound Check)
	_CGD_BUFFER_BOUND_CHECK((_Source->m_ptr+sizeof(uint32_t)+sizeof(uint32_t)+sizeCompressed)<=_bound.bound_upper);
	
	// 2) [복원_크기]를 얻는다.
	size_t	sizeOriginal	 = static_cast<size_t>(_Source->TEMPLATE _front<uint32_t>(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset));

	// 3) [복원_크기]만큼의 [복원_버퍼]를 할당받는다.
	CCGBuffer	_Dest	 = MEM_POOL_ALLOC(sizeOriginal);
	size_t		length	 = _Dest.len;

	// Declare) 
	int	iResult;

	// 3) [복원_버퍼]에 압축을 푼다.
	iResult	 = CGCompress::Uncompress(_Dest.buf, &length, _Source->TEMPLATE _front(_CGD_BOUND_INFO_PASS _CGD_COMMA tempOffset), sizeCompressed);

	// Check) 압축 풀기이 실패했으면 Exception을 던진다.
	if(iResult != 0) throw std::domain_error("Uncompression fail!! (" __FUNCTION__ ")");

	// 4) Offset을 Udpate한다.
	_Offset	 = static_cast<int>(tempOffset+sizeCompressed);

	// 5) Length Udpate
	_Dest.len	 = static_cast<uint32_t>(length);

	// Return) 
	return	_Dest;
}


}
