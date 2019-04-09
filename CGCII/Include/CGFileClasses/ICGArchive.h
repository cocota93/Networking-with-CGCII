//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               File Classes                                *
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
// 1. ICGArchive��!
//    1) I/O�� �����Ͽ� ó���ϱ� ���� Archive Interface
//    2) 
//    3) 
//    4) 
//
// 2. ICGArchive�� �ٽ�! Function�� ��� ����
//    1) int ProcessRead(void* _pData, size_t _Bytes)
//       - �����͸� �о���̴� ����� �������ϴ� �Լ�.
//       - file�� ��� �Ϲ������� ReadFile�� ����Ͽ� �����Ѵ�.
//
//    2) int ProcessWrite(const void* _pData, int _Bytes)
//       - �����͸� ���� ����� �������ϴ� �Լ��̴�.
//       - file�� ��� �Ϲ������� WriteFile�� ����Ͽ� �����Ѵ�.
//
//
//-----------------------------------------------------------------------------
#define	CGARCHIVE_STATUS_LOADING		0x01
#define	CGARCHIVE_STATUS_SAVING			0x02
#define	CGARCHIVE_STATUS_PRE_SAVING		0x03
#define	CGARCHIVE_STATUS_POST_LOADING	0x04

class ICGArchive : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual	uint32_t			GetStatus() const PURE;
	virtual	uint32_t			SetStatus(_In_ uint32_t _Status) PURE;

protected:
	virtual size_t				ProcessRead(_Inout_ CCGBuffer& _Buffer) PURE;
	virtual size_t				ProcessWrite(_In_ const CCGBuffer& _Buffer) PURE;
	

// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Read
			size_t				Read(_Inout_ CCGBuffer& _Buffer)			{	return ProcessRead(_Buffer);}
			size_t				Read(_Inout_updates_bytes_(_iByte) void* _pData, _In_ size_t _iByte) { CGD::buffer bufA(reinterpret_cast<char*>(_pData), static_cast<uint32_t>(_iByte)); CCGBuffer bufB(bufA, nullptr); return ProcessRead(bufB); }

	// 2) Write
			size_t				Write(_In_ const CCGBuffer& _Buffer)		{	return ProcessWrite(_Buffer);}
			size_t				Write(_In_reads_bytes_(_Bytes) const void* _pData, _In_ size_t _Bytes) {	return Write(CCGBuffer(MEM_POOL_ALLOC(_Bytes))<<CGD::buffer(const_cast<void*>(_pData), static_cast<uint32_t>(_Bytes)));}
};
