#pragma once
#include "SocketTCP.h"
void CSocketTCP::OnConnect(CGNet::IO::IConnective* _pConnective)  {
	printf("connected");
}