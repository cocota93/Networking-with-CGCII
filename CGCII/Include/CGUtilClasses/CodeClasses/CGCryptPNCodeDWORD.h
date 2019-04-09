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
// CGCrypt::CPNCodeDWORD
//
// 1. CGCrypt::CPNCodeDWORD란!
//    1) PN(Pseudo Noise) Code를 사용한 암복호화기이다.
//    2) 암복호화는 uint32_t 단위로 수행된다. 따라서 4Byte단위가 아니라면 제대로 동작
//       하지 않을 수 있다.
//
// 2. 암복호화의 기본 원리
//    1) PN Code (Pseudo Noise Code)를 사용한 암복호하기이다.
//    2) 기본적인 동작은 아래와 같다.
//       - 기본 key값으로 Pseudo Noise Generator가 암복호하기를 초기화한다.
//       - 암호화를 요구하면 Pseudo Noise에서 Noise를 얻어내어 원 데이타와 XOR을
//         수행한다.
//       - 복호화를 요구하면 같은 key값으로 초기화된 PN Code Cryptor를 사용하여
//         같은 방법으로 XOR을 수행하여 복호화를 해낸다.
//
// 3. PN Code 암복화기의 특징.
//    1) 강력한 암호화를 제공한다.
//    2) 패킷의 가로채기로는 절대로 원 데이터를 복호화해내지 못한다.
//    3) 같은 데이터라도 암호화된 순서에 따라 전혀 다른 데이터로 암호화 되므로 
//       패킷의 재사용이나 반복사용을 원천적으로 막아준다.
//    4) 따라서 데이터의 전달 순서가 보장되지 않은 상황에서는 사용이 불가능하다.
//	  5) 암복호화 처리 속도가 매우 빠르다.
//
//
//-----------------------------------------------------------------------------
namespace CGCrypt
{

class CPNCodeDWORD :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						ICGEncoder,
	public						ICGDecoder
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CPNCodeDWORD();
	virtual ~CPNCodeDWORD();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				Encode(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);
	virtual	size_t				Decode(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);

	virtual	bool				GenerateEncoder(void* _pSeedInfo, size_t& _iLength);
	virtual	bool				GenerateDecoder(void* _pSeedInfo, size_t& _iLength);

	virtual	bool				InitializeEncoder(_In_reads_bytes_(_iLength) const void* _pSeedInfo, size_t _iLength);
	virtual	bool				InitializeDecoder(_In_reads_bytes_(_iLength) const void* _pSeedInfo, size_t _iLength);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	// 1) Key정보 숫자
			uint32_t			m_arrayKey[256];

	// 2) Now
	//    - 이것은 무조건 Byte로 한다. 왜냐면 256이 넘으면 자동으로 짤리기 때문이다.
	//      따라서 따로 값의 영역처리를 해주지 않아도 된다.
			uint8_t				m_bytePositionOutput;
			uint8_t				m_byteOffset;

	// 3) Cryption함수
protected:
			size_t				CryptXOR(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);;

	// 4) 초기화 함수
public:
			bool				Initialize(uint8_t p_byteOffset, const uint32_t* p_arraySeed, int p_iRound, size_t _iLength=4);
			bool				GenerateKey(const uint32_t* p_dwSeed, _In_ size_t _iLength);

			void				Round(int p_iRound);
};


}