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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

// extract) 
template<>	class _BF<CCGBuffer>
{	
public:
	typedef	CCGBuffer t;
	template<class S>
	static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA S* _s)
	{
		return CCGBuffer::_extract_CCGBuffer(_s _CGD_COMMA _CGD_BOUND_INFO_PASS);
	}
};
// front)
template<>	class _RH<CCGBuffer>
{	
public:
	typedef	CCGBuffer t;
	template<class S> static t _do(_CGD_BOUND_INFO_PARAM _CGD_COMMA const S* _s, int& _Offset)
	{
		S tempBuffer=*_s +(size_t)_Offset;
		auto temp= CCGBuffer::_extract_CCGBuffer(tempBuffer _CGD_COMMA _CGD_BOUND_INFO_PASS);
		_Offset = (int)(tempBuffer.get_front_ptr() - _s->get_front_ptr()); 
		return temp;
	}
};

inline bool CCGBuffer::_is_buffer_overflow() const
{
	// Check) 
	RETURN_IF(m_reference.empty(), false);

	// Check) Check Lower Bound
	RETURN_IF(buf>=m_reference->buf, false)
		
	// Check) Check Upper Bound
	RETURN_IF((buf+len)<=(m_reference->buf+m_reference->len), false);

	// Return) Success!
	return	true;
}

inline bool CCGBuffer::_validate_message() const
{
	// Check) 
	CGD_ASSERT(buf!=nullptr, );
	CGD_ASSERT(len!=0, );

	// 1) Message ũ�⸦ Ȯ���Ѵ�.
	CGD::buffer	tempBuf	 = *static_cast<const CGD::buffer*>(this);

	while(tempBuf.len != 0)
	{
		int32_t		sizeOfMessage	 = *reinterpret_cast<int32_t*>(tempBuf.buf);

		//-----------------------------------------------------------------
		// ����) �߸��� Message Size
		//
		//  ���� ���⼭ CGD_ASSERT()�� �ɸ��ٸ� Message�� ũ�Ⱑ �߸��� ���̴�.
		//  Message�� ���� �� 4Byte(uint32_t)�� Message�� ���̸� �ǹ��ϴµ�
		//  Buffer�� ����(len)�� ���̸� ��Ÿ���� ���� ���� 4Byte�� ũ�Ⱑ ����
		//  �ٸ� ��� �� Assert�� �߻��Ѵ�.
		//  
		//-----------------------------------------------------------------
		// Check) Message�� ũ�Ⱑ 0Byte�� �ȉ´�.
		CGD_ASSERT(sizeOfMessage!=0, );
		if(sizeOfMessage==0) return false;

		// Check) Message�� ũ�Ⱑ ���� ������ ũ�⺸�� ������ �ȉ´�.
		CGD_ASSERT(sizeOfMessage<=static_cast<int>(tempBuf.len), );
		if(sizeOfMessage>static_cast<int>(tempBuf.len)) return false;

		// - ���� Message
		tempBuf.buf	+= sizeOfMessage;
		tempBuf.len	-= sizeOfMessage;
	}

	// Return) ����~
	return	true;
}

inline bool validate_message(_In_ const CCGBuffer* _buffers, size_t _count)
{
	// Declare)
	int	iTotalLength	 = 0;
		
	// 1) ��ü Message ���̸� ���Ѵ�.
	for(size_t i=0;i<_count;++i)
	{
		iTotalLength	 += _buffers[i].len;
	}

	// 2) Buffer�� �����Ѵ�.
	size_t		idxBuffer	 = 0;
	CGD::buffer	tempBuf		 = _buffers[idxBuffer];

	while(iTotalLength!=0)
	{
		// Check) Message�� ũ�Ⱑ ���� ������ ũ�⺸�� ������ �ȉ´�.
		CGASSERT_ERROR(idxBuffer<=_count);
		if(idxBuffer>_count) return false;

		// - Message�� ���̸� ���Ѵ�.
		int32_t	sizeOfMessage	 = *reinterpret_cast<int32_t*>(tempBuf.buf);

		// Check) Message�� ũ�Ⱑ 0Byte�� �ȉ´�.
		CGASSERT_ERROR(sizeOfMessage!=0);
		if(sizeOfMessage==0) return false;

		// Check) Message�� ũ�Ⱑ ���� ������ ũ�⺸�� ������ �ȉ´�.
		CGASSERT_ERROR(sizeOfMessage<=static_cast<int32_t>(iTotalLength));
		if(sizeOfMessage>static_cast<int32_t>(iTotalLength)) return false;

		// - ���� Message
		iTotalLength-= sizeOfMessage;

		// Check) Total Bytes���� �� �� �޽����� �䱸�� ��� false�� �����Ѵ�.
		CGASSERT_ERROR(iTotalLength>=0);
		if(iTotalLength<0) return false;

		while(sizeOfMessage>=static_cast<int32_t>(tempBuf.len))
		{
			sizeOfMessage	-= tempBuf.len;

			++idxBuffer;

			BREAK_IF(sizeOfMessage==0);

			CGASSERT_ERROR(idxBuffer<_count);
			if(idxBuffer>=_count) return false;

			tempBuf	 = _buffers[idxBuffer];
		}

		tempBuf.buf	+= sizeOfMessage;
		tempBuf.len	-= sizeOfMessage;
	}

	return	true;
}
