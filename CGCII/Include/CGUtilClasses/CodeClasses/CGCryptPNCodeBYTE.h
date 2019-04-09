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
// CGCrypt::CPNCodeBYTE
//
// 1. CGCrypt::CPNCodeBYTE란!
//    1) PN(Pseudo Noise) Code를 사용한 암복호화기이다.
//    2) 기본적인 동작은 CGCrypt::CPNCodeDWORD와 동일하다.
//       다만 암복호화가 uint8_t 단위로 수행해 어떤 크기의 데이터라도 암복호화를
//       할 수 있다는 것만 다르다.
//    3) 자세한 내용은 CGCrypt::CPNCodeDWORD와 동일하다.
//
//
//-----------------------------------------------------------------------------
namespace CGCrypt
{

class CPNCodeBYTE :
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
			CPNCodeBYTE();
	virtual ~CPNCodeBYTE();


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
			uint8_t				m_arrayKey[256];

	// 2) Now
	//    - 이것은 무조건 Byte로 한다. 왜냐면 256이 넘으면 자동으로 짤리기 때문이다.
	//      따라서 따로 값의 영역처리를 해주지 않아도 된다.
			uint8_t				m_bytePositionOutput;
			uint8_t				m_byteOffset;

	// 3) Cryption함수
protected:
			size_t				CryptXOR(_Out_writes_bytes_(_iLength) void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);;

	// 4) 초기화 함수
public:
			bool				GenerateKey(_In_reads_bytes_(_iLength) const uint8_t* p_dwSeed, _In_ size_t _iLength);
			void				Round(int p_iRound);
};


}