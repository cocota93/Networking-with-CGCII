#pragma once
#include "pch.h"
#include "../../../CGCII/Include/CGNetSocketTemplates.h"

// ----------------------------------------------------------------------------
// CSocket Class
// ----------------------------------------------------------------------------
class CSocketTCP :
	public CGNet::Socket::CTCPQueue<>,
	public NCGPoolable<CSocketTCP>
{
	// ****************************************************************************
	// Constructor/Destructor)
	// ----------------------------------------------------------------------------
public:
	CSocketTCP() {}
	virtual ~CSocketTCP() {}

	// ****************************************************************************
	// Framework)
	// ----------------------------------------------------------------------------
protected:
	virtual void	OnConnect(CGNet::IO::IConnective* _pConnective) override;
	virtual void	OnDisconnect(uint32_t _Reason) override;
	virtual int		OnMessage(CGMSG& _MSG) override;
	int ping(CGNETMSG& _Msg);
	DECLARE_CGMESSAGE_MAP
};