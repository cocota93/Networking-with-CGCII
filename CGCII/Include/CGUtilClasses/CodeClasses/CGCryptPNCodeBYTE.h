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
// CGCrypt::CPNCodeBYTE
//
// 1. CGCrypt::CPNCodeBYTE��!
//    1) PN(Pseudo Noise) Code�� ����� �Ϻ�ȣȭ���̴�.
//    2) �⺻���� ������ CGCrypt::CPNCodeDWORD�� �����ϴ�.
//       �ٸ� �Ϻ�ȣȭ�� uint8_t ������ ������ � ũ���� �����Ͷ� �Ϻ�ȣȭ��
//       �� �� �ִٴ� �͸� �ٸ���.
//    3) �ڼ��� ������ CGCrypt::CPNCodeDWORD�� �����ϴ�.
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
	// 1) Key���� ����
			uint8_t				m_arrayKey[256];

	// 2) Now
	//    - �̰��� ������ Byte�� �Ѵ�. �ֳĸ� 256�� ������ �ڵ����� ©���� �����̴�.
	//      ���� ���� ���� ����ó���� ������ �ʾƵ� �ȴ�.
			uint8_t				m_bytePositionOutput;
			uint8_t				m_byteOffset;

	// 3) Cryption�Լ�
protected:
			size_t				CryptXOR(_Out_writes_bytes_(_iLength) void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);;

	// 4) �ʱ�ȭ �Լ�
public:
			bool				GenerateKey(_In_reads_bytes_(_iLength) const uint8_t* p_dwSeed, _In_ size_t _iLength);
			void				Round(int p_iRound);
};


}