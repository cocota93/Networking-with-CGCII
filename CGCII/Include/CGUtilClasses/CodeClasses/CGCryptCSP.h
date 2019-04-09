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
// CGRenderer::CPoints
//
// 1. CGCrypt::CCSP란!
//    1) Windows에서 제공해주는 암호화 API로 만들어진 Crypto class입니다. 
//
//
//-----------------------------------------------------------------------------
#include "Wincrypt.h"

namespace CGCrypt
{

class CCSP :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public				ICGEncoder,
	public				ICGDecoder,
	virtual public		ICGInitializable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCSP();
	virtual ~CCSP();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
public:
	// 1) Initialize/Destroy
	//! @brief 전달 인자 없이 초기화를 실행한다. @return true 성공 @return false 실패
			bool				Initialize() { CGMSG_CONTEXT tempMSG; return Initialize(tempMSG); }
	virtual	bool				Initialize(CGMSG_CONTEXT& _Msg) override;
	virtual	bool				Destroy() override;

	virtual	bool				InitializeEncoder(/*_In_reads_bytes_(_iLength)*/ const void* _pSeedInfo, int _iLength);
	virtual	bool				InitializeDecoder(/*_In_reads_bytes_(_iLength)*/ const void* _pSeedInfo, int _iLength);

	// 2) Encode/Decode
	virtual	int					Encode(void* p_pDest, /*_In_reads_bytes_(_iLength)*/ const void* _pSrc, int _iLength);
	virtual	int					Decode(void* p_pDest, /*_In_reads_bytes_(_iLength)*/ const void* _pSrc, int _iLength);

	// 3) ...
	virtual	bool				GenerateEncoder(void* _pSeedInfo, int& _iLength);
	virtual	bool				GenerateDecoder(void* _pSeedInfo, int& _iLength);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			HCRYPTKEY			m_hKey;
			HCRYPTPROV			m_hProv;
			HCRYPTHASH			m_hHash;
};


}
