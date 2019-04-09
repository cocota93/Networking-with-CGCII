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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGEDC::CCRC
//
// 1. CGEDC::CCRC��!
//    1) CRC�� ���ϴ� Ŭ�����̴�.
//    2) GenerateCRCTable() �� p_dwKey�� �����Ͽ� CRC Table�� �����Ѵ�.
//       (���⼭ 32Bit CRC�� �Ϲ����� ���� 0x04c11db7L�̰� �ʿ信 ���� ���Ƿ� �ٸ�
//        Ű���� ������ ���� �ִ�.)
//    3) ���� get_CRC()�Լ��� ȣ���ϸ� CRC�� ������ �ش�.
//    4) ���� CRC()���� �������� ���ʿ� �ٿ��� ���ο� �����Ϳ��� ���� �� CRC()����
//       ���� ��� �Ǹ� CRC()���� 0�� �ȴ�.
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
	// 1) CRC�� ��� �Լ�(�ٽ���...)
			uint32_t			get_CRC(const uint8_t* p_pbData, size_t _dwByte) const;

	// 2) Key�� �аų� �����ϴ� �Լ�.
			uint32_t			GetKey() const							{	return m_dwKey;}
			void				GenerateCRCTable(uint32_t p_dwKey);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			uint32_t			m_dwKey;			// Table�� ���� CRCKey�Դϴ�.
			uint32_t			m_dwCRCTable[256];	// Key�� ���ؼ� ������� CRCKey�Դϴ�.
};


}