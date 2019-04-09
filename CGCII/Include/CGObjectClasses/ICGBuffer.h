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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// Memory Base!
//
// 1. Memory Base��
//     Memory Base�� Memory Pool�� ���Ǵ� Memory class�̴�. 
//    �⺻������ WSABUF�� ���� ���¸� �ϰ� ������ Reference Counter������ 
//    ������ �ִ�. 
//     Reference Counting�� 0�� �� ��� Free�Լ��� ȣ��ǰ� �Ǿ� �ְ� 
//    �Ϲ������� �̶� �Ҵ������ǵ��� ���α׷��� �ȴ�.
//
// 2. Memory Base!!
//    1) buf/len
//       �Ҵ�� Buffer�� Pointer�� �� Buffer�� ���̸� �����ϴ� �����̴�.
//
//-----------------------------------------------------------------------------
class ICGBuffer : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGD::buffer,
	virtual public				ICGReferenceable						// (@) ReferenceCounter
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGBuffer()			 										{}
			ICGBuffer(char* _buf, uint32_t _len) : CGD::buffer(_buf, _len) {}
	virtual	~ICGBuffer()												{}
};

inline CGPTR<ICGBuffer> _CGMEM_ALLOC(size_t _size CGNEW_DEBUG_INFO_COMMA CGNEW_DEBUG_INFO_PARAMETERS_WITH_DEFAULT)
{
	// Definitions) 
	class CREATE : public ICGBuffer
	{
	public:
			CREATE(size_t _Size) : ICGBuffer(reinterpret_cast<char*>(CGMALLOC(_Size)), static_cast<uint32_t>(_Size)) {}
	virtual	~CREATE()	{	CGFREE(buf);}
	};

	// Return) Create and Return 
	return	std::move(_CGNEW<CREATE>(CGNEW_DEBUG_INFO_PARAMETERS_PASSING CGNEW_DEBUG_INFO_COMMA _size));
}
