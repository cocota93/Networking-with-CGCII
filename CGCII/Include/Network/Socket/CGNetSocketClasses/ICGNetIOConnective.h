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
// CGNet::IO::IConnective(���� �߰��)
//
// 1. IConnective��~
//    1) ���� Connectable�� ������ ������ ó�����ִ� ����� ������ �����Ѵ�.
//    2) Connectable�� ��ӹ��� ��ü�� ������ ���ش�.
//    3) ��ǥ���� ������ TCP�� Acceptor�� Connetor�� �ִ�.
//       Connective::Acceptor�� ������ �޾� IConnectable�� ��������ִ� ���̰�
//       Connective::Connector�� Ŭ���̾�Ʈ�� ������ �õ����ִ� ���̴�.
//    4) �� Ŭ������ ��ӹ޾� ������ ��ü�� ��� Connective::Manager�� ��ϵǸ�
//       Connective::Manager���� ã�� ����� �� �ִ�.
//    5) �� Ŭ������ Nameable�� ��ӹ޾� �⺻������ �̸��� ������.
//
// 2. ���� �Լ�.
//    1) ProcessConnectiveConnect()
//       - ����ó���� �Ǵ� ������ �����ϴ� �Լ�.
//
//    2) ProcessConnectiveDisconnect()
//       - ���������Ǵ� ������ �����ϴ� �Լ�.
//
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IConnective :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual	public				ICGNameable,							// (I) Nameable
	virtual public				ICGReferenceable,						// (I) Reference Count
	virtual public				CGNet::IO::Statistics::NConnective		// (@) ���
{
// ****************************************************************************
// Constructor) 
// ----------------------------------------------------------------------------
public:
			IConnective()		{}
	virtual	~IConnective()		{}


// ****************************************************************************
// Interfaces) 
// ----------------------------------------------------------------------------
public:
	// 1) Status
	virtual	bool				IsEnable() const PURE;
			bool				IsDisable() const						{	return !IsEnable();}

	// 2) Start Object
			template <class TSTART>
			CGPTR<TSTART>		GetStartObject() const					{	return dynamic_pointer_cast<TSTART>(m_pobjectStart); }
			void				SetStartObject(ICGReferenceable* _pObj)	{	m_pobjectStart= _pObj;}

	// 3) On Complete
	virtual	void				ProcessConnectiveConnect(_In_ CGNet::IO::IConnectable* _pConnectable, _In_ uintptr_t _Return) PURE;
	virtual	void				ProcessConnectiveDisconnect(_In_ CGNet::IO::IConnectable* _pConnectable) PURE;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			void				RegisterConnective()					{	CGNet::IO::Connective::Manager::GetInstance()->Register(this);}
			void				UnregisterConnective()					{	CGNet::IO::Connective::Manager::GetInstance()->Unregister(this);}

protected:
			CGPTR<ICGReferenceable>	m_pobjectStart;
};


}
}