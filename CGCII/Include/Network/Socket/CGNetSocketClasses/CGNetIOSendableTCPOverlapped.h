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
// CGNet::IO::Sendable::NTCPOverlapped
//
// 1. CGNet::IO::Sendable::NTCPOverlapped��!
//    1) TCP�� Send�� �ѹ��� Send�� �ѹ��� Overlapped I/O�� �ɾ �����ϴ� 
//       Sendable�̴�.
//    2) �ѹ��� Send�� �ѹ��� Overlapped I/O�� ���� ������ ������ �����Ͽ� Send
//       �󵵰� ���� Socket������ ���� ������ ����.
//    3) ������ Send�� �󵵰� ���� Socket������ ���� I/O�� ������ ������ ������
//       �� �����Ƿ� �󵵰� ���� Send�� �����ϴ� Socket������ �� Sendable���
//       Send Gathering�� �����ϴ� TCPGathering�� ����ϵ��� ���Ѵ�.
//    4) ��κ��� Server Socket�̳� Client Socket�� ��� �� ������ Sendable��
//       ����ϴ�.
//
// 2. CGNet::IO::Sendable::CTCP�� �ٽ�! Function�� ��� ����
//    1) ProcessSend()		CCGBuffer�� �����Ѵ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

class NTCPOverlapped :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendable,					//     Sendable
	virtual protected			CGNet::IO::IConnectable					// (I) Sendable
{
// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ó�� ������ �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _arrayBuffer ������ ���� �迭 @param _countBuffer ������ ���� @param _pOriginal ������ ��������� ������ ��ü �������� ������ ��������� 1 �����ϸ� ������ �Ϸ�Ǹ� 1 ���ҽ�Ų��. @param _pSockAddress ������ �ּ�(UDP����)  @return true ����  @return false ����
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief ������ �Ϸ�Ǿ��� �� ó���� �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _Return ���� ��� @param _Transfered ���۵� ����Ʈ ��
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief �ʱ�ȭ �� �� ȣ��Ǵ� �Լ�.
	virtual	void				ResetSendable() override;
};


}
}
}