//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Utility Classes                              *
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
// CGEDC::CCRC
//
// 1. CGEDC::CCRC란!
//    1) CRC를 구하는 클래스이다.
//    2) GenerateCRCTable() 에 p_dwKey를 전달하여 CRC Table을 생성한다.
//       (여기서 32Bit CRC의 일반적인 값은 0x04c11db7L이고 필요에 따라 임의로 다른
//        키값을 설정할 수도 있다.)
//    3) 그후 get_CRC()함수를 호출하면 CRC를 리턴해 준다.
//    4) 얻은 CRC()값을 데이터의 뒷쪽에 붙여서 새로운 데이터열을 만든 후 CRC()값을
//       새로 얻게 되면 CRC()값은 0이 된다.
//
//
//-----------------------------------------------------------------------------
#define SIZE_OF_CRC	sizeof(uint32_t)

namespace CGEDC
{

class CCRC
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCRC(uint32_t p_dwKey=0x04c11db7L)							{	if(p_dwKey != 0) { GenerateCRCTable(p_dwKey);}}
	virtual ~CCRC()														{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) CRC를 얻는 함수(핵심임...)
			uint32_t			get_CRC(const uint8_t* p_pbData, size_t _dwByte) const;

	// 2) Key를 읽거나 설정하는 함수.
			uint32_t			GetKey() const							{	return m_dwKey;}
			void				GenerateCRCTable(uint32_t p_dwKey);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			uint32_t			m_dwKey;			// Table을 만든 CRCKey입니다.
			uint32_t			m_dwCRCTable[256];	// Key에 의해서 만들어진 CRCKey입니다.
};


}