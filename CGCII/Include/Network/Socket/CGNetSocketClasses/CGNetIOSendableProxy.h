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
// CGNet::IO::Sendable::NProxy
//
// 1. CGNet::IO::CSendable::NProxy��~
//     Sendable�� �����ͷ� ������ ������ ProcessReqestSend()�Լ��� ȣ���ϰ� �Ǹ�
//    �����ͷ� ������ �Լ��� ProcessSend()�Լ��� ȣ���Ѵ�.
//
//    1) �� Sendalble�� ���� ���۴ɷ��� ����.
//    2) �� ��� �ٸ� Sendable�� �������� �ִٰ� ProcessSend()�� ������ �䱸�ϸ�
//       �������� Sendable�� ProcessSend()�� ȣ���� �ش�.
//    3) �� ������� ������ Sendable�̴�.
//    4) �ַ� Peer ���ۿ� ���� ���ȴ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Sendable
{

class NProxy : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::ISendable					//     Sendable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			NProxy(_In_ ISendable* _pSendable = nullptr) : m_pSendable(_pSendable)	{}
			~NProxy()													{}


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief '������ ISendable ��ü'�� �����Ѵ�. @param _pSendable ISendable ��ü @return true ����  @return false ����
			void				SetSendable(_In_ ISendable* _pSendable){ m_pSendable = _pSendable; }
	//! @brief ������ '������ ISendable ��ü'�� ��´�. @return ������ '������ ISendable ��ü'
			ISendable*			GetSendable() const						{	 return m_pSendable;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
	//! @brief ���� ó�� ������ �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _arrayBuffer ������ ���� �迭 @param _countBuffer ������ ���� @param _pOriginal ������ ��������� ������ ��ü �������� ������ ��������� 1 �����ϸ� ������ �Ϸ�Ǹ� 1 ���ҽ�Ų��. @param _pSockAddress ������ �ּ�(UDP����)  @return true ����  @return false ����
	virtual	bool				ProcessSend(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_reads_(_countBuffer) const CGD::buffer* _arrayBuffer, _In_ int _countBuffer, _In_opt_ ICGReferenceable* _pOriginal, _In_opt_ const SOCKADDR_CGNETWORK* _pSockAddress) override;

	//! @brief ������ �Ϸ�Ǿ��� �� ó���� �����ϴ� �Լ�. @param _pSendCompletor �Ϸ��� ȣ��� �Լ� ��ü @param _Return ���� ��� @param _Transfered ���۵� ����Ʈ ��
	virtual	void				ProcessCompleteSendable(_In_opt_ CGNet::IO::ISendCompletor* _pSendCompletor, _In_ uintptr_t _Return, _In_ size_t _Transfered) override;

	//! @brief �ʱ�ȭ �� �� ȣ��Ǵ� �Լ�.
	virtual	void				ResetSendable() override;

protected:
			ISendable*			m_pSendable;
};


}
}
}