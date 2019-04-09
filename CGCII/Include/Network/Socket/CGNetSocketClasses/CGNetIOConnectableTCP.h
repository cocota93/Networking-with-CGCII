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
// CGNet::IO::Connectable::NTCP
//
// 1. CGNet::IO::Connectable::NTCP�̶�!
//    1) TCP�� IConnectable�� ������ Ŭ�����̴�.
//    2) TCP�� ������ �õ��Ͽ� ����ó���� �Ϸ�Ǿ��� ��(������������ �������� ����)
//       �� Ŭ������ ���� ó�������� �����ϰ� �ȴ�.
//    3) �� Ŭ������ Overlapped I/O�� ����� Receive�� ó���ϵ��� ���ǵǾ����Ƿ�
//       ���� �� Receive()�� �ɵ��� �ۼ��Ǿ���.
//    4) ������ ������ ��� OnConnect()�Լ��� ȣ���ϰ� �������� ��� OnFailConnect()��
//       ȣ���Ѵ�.
//    5) ������ ����Ǿ��� �� OnDisconnect()�Լ��� ȣ���ϵ��� ���ǵǾ� �ִ�.
//    6) ������ ���Ḧ �䱸�� �� Disconnect()�Լ��� ȣ���ϸ� �Ǹ� �̴� Graceful
//       Close�� �����ϰ� �ȴ�.
//       ����) ���� Abortive Close�� ����ϰ��� �Ѵٸ� ISocket�� CloseSocket()�Լ���
//             ����ϵ��� �Ѵ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{
namespace Connectable
{

class NTCP :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				CGNet::IO::IConnectable,				//     Connectable
	virtual protected			CGNet::IO::IReceivable					// (I) Receivable
{
// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
// - ����ڰ� �� Socket�� ����ڰ� �����ϱ� ���� �Լ�.
public:
	// 1) Disconnect.(Graceful)
	virtual	bool				Disconnect();


// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
// - �� �Լ����� ������ �����ν� ���α׷����� �Ѵ�.
// - ��� �۾��� ����Ǿ��� �� �ҷ����� �Լ��̴�.
protected:
	// 1) �Ϲ����� On�Լ�.
	virtual void				OnConnect(CGNet::IO::IConnective* /*_pConnective*/){}
	virtual void				OnDisconnect(uint32_t /*_Reason*/)		{}

	// 2) �������� �� On�Լ�.
	virtual void				OnFailConnect(CGNet::IO::IConnective* /*_pConnective*/, uint32_t /*_Reason*/)		{}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Complete Process����.
	virtual bool				ProcessCompleteConnect(_In_opt_ CGNet::IO::IConnective* _pConnective, _In_ uintptr_t _Return) override;// 1) ���ӵǾ��� ���� ó�� ������ �����ϴ� �Լ�.
	virtual bool				ProcessCompleteDisconnect() override;// 2) ����Ǿ��� ���� ó�� ������ �����ϴ� �Լ�.

	virtual void				ProcessOnConnect(CGNet::IO::IConnective* _pConnective)	{	OnConnect(_pConnective);}
	virtual	void				ProcessOnDisconnect(uint32_t _Resson)	{	OnDisconnect(_Resson);}
	virtual	void				ProcessOnFailConnect(CGNet::IO::IConnective* _pConnective, uint32_t _Resson)	{	OnFailConnect(_pConnective, _Resson);}

	// 2) Reset�Ҷ� ȣ���ϴ� �Լ�.
	virtual	void				ResetConnectable() override;
			void				ProcessDisconnect();

			class	CCGExecutableDisconnect;
			friend	class CCGExecutableDisconnect;

			CGPTR<ICGExecutable> AllocExecutableDisconnect(_In_ CGNet::IO::Connectable::NTCP* _pConnectable);
};


}
}
}