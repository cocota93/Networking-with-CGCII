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
// CGCryptBase
//
// 1. CGCryptBase란!
//    1) 암복호화에 관련된...
//
//
//-----------------------------------------------------------------------------
enum class eCRYPTION_TYPE : int32_t
{
	NONE,
	PNCODE_BYTE,
	PNCODE_DWORD,
	DES,
	RSA,
	CSP,
};

class ICGDecoder : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGDecoder()			{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				Decode(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength) PURE;

	virtual	bool				GenerateDecoder(void* _pSeedInfo, size_t& _iLength) PURE;
	virtual	bool				InitializeDecoder(_In_reads_bytes_(_iLength) const void* _pSeedInfo, size_t _iLength) PURE;
};


class ICGEncoder : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGReferenceable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
	virtual	~ICGEncoder()		{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	virtual	size_t				Encode(void* p_pDest, _In_reads_bytes_(_iLength) const void* _pSrc, size_t _iLength) PURE;

	virtual	bool				GenerateEncoder(void* _pSeedInfo, size_t& _iLength) PURE;
	virtual	bool				InitializeEncoder(_In_reads_bytes_(_iLength) const void* _pSeedInfo, size_t _iLength) PURE;
};