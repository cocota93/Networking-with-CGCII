#pragma once
#include "SocketTCP.h"
VOID CSocketTCP::OnDisconnect(uint32_t _Reason) {
	printf("disconnected");
}
