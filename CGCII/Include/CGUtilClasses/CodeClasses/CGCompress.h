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
// CGCompress
//
// 1. CGCompress��!
//    1) ������ �����ϴ� Function�̴�.
//    2) ���Լ��� ���������� ZLib�� �Լ��� ����ϰ� �ִ�.
//    3) ���� �� �Լ��� ����ϰ��� �Ѵٸ� Zlib�� �������ؼ� �߰������־���Ѵ�.
//
//  ���ǻ���) �⺻������ ZLib�� �����ϰ� ���� �ʴ�.
//            �ʿ�� �������̺귯���� ZLib�� ������ �������Ͽ� Link�����־��
//            �Ѵ�.
//  
//            #pragma comment (lib,"zlib.lib")
//
//
//-----------------------------------------------------------------------------
namespace CGCompress
{
	int Compress(void* p_pDest, size_t* p_pDestLen, _In_reads_bytes_(p_dwSourceLen) const void* _pSource, size_t p_dwSourceLen);
	int Uncompress(void* p_pDest, size_t* p_pDestLen, _In_reads_bytes_(p_dwSourceLen) const void* _pSource, size_t p_dwSourceLen);
}
