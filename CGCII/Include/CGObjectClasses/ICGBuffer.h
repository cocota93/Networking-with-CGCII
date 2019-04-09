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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// Memory Base!
//
// 1. Memory Base는
//     Memory Base는 Memory Pool에 사용되는 Memory class이다. 
//    기본적으로 WSABUF와 같은 형태를 하고 있으며 Reference Counter가능을 
//    가지고 있다. 
//     Reference Counting이 0이 될 경우 Free함수가 호출되게 되어 있고 
//    일반적으로 이때 할당해제되도록 프로그래밍 된다.
//
// 2. Memory Base!!
//    1) buf/len
//       할당된 Buffer의 Pointer와 그 Buffer의 길이를 저장하는 변수이다.
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
