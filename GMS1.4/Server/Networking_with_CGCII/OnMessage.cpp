#pragma once
#include "SocketTCP.h"

int CSocketTCP::OnMessage(CGMSG& _Msg) {
	EXECUTE_CGMESSAGE_MAP(_Msg);
	return 0;
}
