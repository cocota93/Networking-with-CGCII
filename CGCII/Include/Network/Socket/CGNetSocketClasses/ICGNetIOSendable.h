//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
// CGNet::IO::ISendable
//
// 1. CGNet::IO::ISendable��~
//    1) �����͸� ������ I/O�Լ��� ����Ͽ� ������ ������ ó���� �����ϴ� �Լ�.
//    2) ProcessSend()�� �������� ������ ��û�ϴ� ó�� ������ �����ϴ� �Լ�.
//    3) ProcessCompleteSendable()�� �������� ������ �Ϸ�Ǿ��� �� ȣ��Ǿ� ó��
//       ������ �����ϴ� �Լ��̴�.
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class ISendable : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable						// (I) Reference Counter.
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief ���� ó�� ������ �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _arrayBuffer ������ ���� �迭 @param _countBuffer ������ ���� @param _pOriginal ������ ��������� ������ ��ü �������� ������ ��������� 1 �����ϸ� ������ �Ϸ�Ǹ� 1 ���ҽ�Ų��. @param _pSockAddress ������ �ּ�(UDP����)  @return true ����  @return false ����
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddr) PURE;

	//! @brief ������ �Ϸ�Ǿ��� �� ó���� �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _Return ���� ��� @param _Transfered ���۵� ����Ʈ ��
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) PURE;

	//! @brief �ʱ�ȭ �� �� ȣ��Ǵ� �Լ�.
	virtual	void				ResetSendable() PURE;
};


}
}