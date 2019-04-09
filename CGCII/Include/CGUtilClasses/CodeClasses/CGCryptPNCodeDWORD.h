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
// CGCrypt::CPNCodeDWORD
//
// 1. CGCrypt::CPNCodeDWORD��!
//    1) PN(Pseudo Noise) Code�� ����� �Ϻ�ȣȭ���̴�.
//    2) �Ϻ�ȣȭ�� uint32_t ������ ����ȴ�. ���� 4Byte������ �ƴ϶�� ����� ����
//       ���� ���� �� �ִ�.
//
// 2. �Ϻ�ȣȭ�� �⺻ ����
//    1) PN Code (Pseudo Noise Code)�� ����� �Ϻ�ȣ�ϱ��̴�.
//    2) �⺻���� ������ �Ʒ��� ����.
//       - �⺻ key������ Pseudo Noise Generator�� �Ϻ�ȣ�ϱ⸦ �ʱ�ȭ�Ѵ�.
//       - ��ȣȭ�� �䱸�ϸ� Pseudo Noise���� Noise�� ���� �� ����Ÿ�� XOR��
//         �����Ѵ�.
//       - ��ȣȭ�� �䱸�ϸ� ���� key������ �ʱ�ȭ�� PN Code Cryptor�� ����Ͽ�
//         ���� ������� XOR�� �����Ͽ� ��ȣȭ�� �س���.
//
// 3. PN Code �Ϻ�ȭ���� Ư¡.
//    1) ������ ��ȣȭ�� �����Ѵ�.
//    2) ��Ŷ�� ����ä��δ� ����� �� �����͸� ��ȣȭ�س��� ���Ѵ�.
//    3) ���� �����Ͷ� ��ȣȭ�� ������ ���� ���� �ٸ� �����ͷ� ��ȣȭ �ǹǷ� 
//       ��Ŷ�� �����̳� �ݺ������ ��õ������ �����ش�.
//    4) ���� �������� ���� ������ ������� ���� ��Ȳ������ ����� �Ұ����ϴ�.
//	  5) �Ϻ�ȣȭ ó�� �ӵ��� �ſ� ������.
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
	// 1) Key���� ����
			uint32_t			m_arrayKey[256];

	// 2) Now
	//    - �̰��� ������ Byte�� �Ѵ�. �ֳĸ� 256�� ������ �ڵ����� ©���� �����̴�.
	//      ���� ���� ���� ����ó���� ������ �ʾƵ� �ȴ�.
			uint8_t				m_bytePositionOutput;
			uint8_t				m_byteOffset;

	// 3) Cryption�Լ�
protected:
			size_t				CryptXOR(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength);;

	// 4) �ʱ�ȭ �Լ�
public:
			bool				Initialize(uint8_t p_byteOffset, const uint32_t* p_arraySeed, int p_iRound, size_t _iLength=4);
			bool				GenerateKey(const uint32_t* p_dwSeed, _In_ size_t _iLength);

			void				Round(int p_iRound);
};


}