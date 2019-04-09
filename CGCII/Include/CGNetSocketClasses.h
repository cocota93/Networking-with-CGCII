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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//----------------------------------------------------------------------------
//  Disable Warnning
//
// 1) Warnning C4250 Disable
//    - C4250은 다중 상속의 virtual 상속된 interface에 대해서 어떤 것을 선택
//      했는지에 대해서 표시해주는 Warnning이다. 이 부분에 대한 표시가
//      필요 없으므로 이 부분은 Disable한다.
//----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning( disable : 4250)
#endif

#define	CGNET_SOCKET_CLASSES

#ifdef _DEBUG
#define	_VALIDATE_SEND_MESSAGE
#define	_VALIDATE_RECEIVE_MESSAGE
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

namespace CGNet
{
namespace IO
{
	class ISocket;
	class IBinder;
	class IConnective;
	class IConnectable;
	class ISender;
	class ISenderDatagram;
	class IMessageable;
	class IAddress;

	namespace Receivable
	{
		class	NDatagram;
	}

	namespace Messageable
	{
		class	NBaseProxy;
	}

	namespace Connective
	{
		class	Manager;
	}

	namespace Sendable
	{
		namespace Executable
		{
			class CSendBuffer;
		}
	}

	namespace AddOn
	{
		class ManagerSocketSustain;
	}
}
}

#if !defined(_MSC_VER)
	#define	IPPROTO_RESERVED_MAX	261
#endif


//----------------------------------------------------------------------------
// head File들
//----------------------------------------------------------------------------
// 1) Socket header files
#include <winsock2.h>
#include <mstcpip.h>
#include <Ws2tcpip.h>
#include <Mswsock.h>

// 2) for GCC
#if !defined(_MSC_VER)
#include <in6addr.h>
#endif

// Undefinitions) 
#undef max

// 3) Execute Classes
#include "CGExecuteClasses.h"

// 4) Definitionsr
#include "Network/Socket/CGNetSocketClasses/CGNetDefinitionsSocketProtocol.h"
#include "Network/Socket/CGNetSocketClasses/CGNetDefinitionsSocket.h"
#include "Network/Socket/CGNetSocketClasses/CGNetExceptions.h"

// 5) Statistics & API
#include "Network/Socket/CGNetSocketClasses/CGNetStatistics.h"
#include "Network/Socket/CGNetSocketClasses/CGNetAPISocket.h"

// 6) Messages
#include "Network/CGNetDefineMessage.h"

// 7) Socket Manager
#include "Network/Socket/CGNetSocketClasses/CGNetIOBinderManager.h"

// 8) Interfaces

#include "Network/Socket/CGNetSocketClasses/ICGNetIOAddress.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOSocket.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOConnector.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOConnectable.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOSender.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOSendCompletor.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOSendRequest.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOSendable.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOReceivable.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOPacketable.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOPeer.h"

// 9) Manager
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectiveManager.h"

// 10) Connectable Manager
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectableManager.h"

// 11) Binder
#include "Network/Socket/CGNetSocketClasses/ICGNetIOBinder.h"

// 12) Connective
#include "Network/Socket/CGNetSocketClasses/ICGNetIOConnective.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOConnectiveAcceptor.h"
#include "Network/Socket/CGNetSocketClasses/ICGNetIOConnectiveConnector.h"



//----------------------------------------------------------------------------
// Component Classes
//----------------------------------------------------------------------------
// 1) Address
#include "Network/Socket/CGNetSocketClasses/CGNetIOAddress.h"

// 2) Socket
#include "Network/Socket/CGNetSocketClasses/CGNetIOSocket.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSocketTCP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSocketTCPRIO.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSocketUDP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSocketDummy.h"

// 3) Bindable
#include "Network/Socket/CGNetSocketClasses/CGNetIOBinderTCP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOBinderUDP.h"

// 4) Connector
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectorTCP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectorTCPReconnect.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOExecutableConnector.h"

// 5) Connectable
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectableTCP.h"

// 6) Connectable Manager
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectableManagerList.h"

// 7) Acceptor
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectiveAcceptorTCP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOConnectiveConnectorTCP.h"

// 8) Send Executable
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendCompletor.h"

// 9) Sendable
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendableTCP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendableTCPOverlapped.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendableUDP.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendableUDPQueued.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendableProxy.h"

// 10) Send Requestor
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendRequest.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendRequestUDPResend.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSendRequestProxy.h"

// 11) Sender
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderStream.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderStreamGather.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderStreamProxy.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderStreamStaticProxy.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderDatagram.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderDatagramProxy.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderDatagramAddress.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOSenderDatagramNULLAddress.h"

// 12) Receivable
#include "Network/Socket/CGNetSocketClasses/CGNetIOReceivableStream.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOReceivableDatagram.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOReceivableStreamQueue.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOReceivableRIOStream.h"

// 13) Packetable
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableDatagram.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableDatagramResponse.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableStream.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableStreamPrimitive.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableStreamFixed.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOPacketableStreamSeperator.h"

// 14) Messageable
#include "Network/Socket/CGNetSocketClasses/CGNetIOMessageableBase.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOMessageableDispatchable.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOMessageableProxy.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOMessageableQueue.h"

// 15) Group Peer
#include "Network/Socket/CGNetSocketClasses/CGNetIOGroupPeer.h"

// 16) AddOn
#include "Network/Socket/CGNetSocketClasses/CGNetIOAddOnSocketSustain.h"
#include "Network/Socket/CGNetSocketClasses/CGNetIOAddOnKeepAlive.h"

// 17) I/O Package
#include "Network/Socket/CGNetSocketClasses/CGNetIOUDPResend.h"

// 18) 기타..
#include "Network/Socket/CGNetSocketClasses/CGManagerRequest.h"
#include "Network/Socket/CGNetSocketClasses/CGMessageRemoteRequest.h"
#include "Network/Socket/CGNetSocketClasses/CGNETMSG_RESPONSE.h"


//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#if !defined(_LIB) || defined(_CONSOLE)

#if defined(_MSC_VER) && !defined(_MSC_PLATFORM_TOOLSET)
	#if _MSC_VER>=_MSC_VER_2015
		#define	_MSC_PLATFORM_TOOLSET	140
	#elif _MSC_VER>=_MSC_VER_2013
		#define	_MSC_PLATFORM_TOOLSET	120
	#elif _MSC_VER>=_MSC_VER_2012
		#define	_MSC_PLATFORM_TOOLSET	110
	#elif _MSC_VER>=_MSC_VER_2010
		#define	_MSC_PLATFORM_TOOLSET	100
	#elif _MSC_VER>=_MSC_VER_2008
		#define	_MSC_PLATFORM_TOOLSET	90
	#else
		#define	_MSC_PLATFORM_TOOLSET	80
	#endif
#endif

// 1) Default Socket 
#if defined(_MSC_VER)
	#pragma comment (lib,"ws2_32.lib")
#endif


//----------------------------------------------------------------------------
// * VS2015 Lib 
//----------------------------------------------------------------------------
#if _MSC_PLATFORM_TOOLSET>=140

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_v140.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_DLL_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_DLL_v140.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_v140_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_v140.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2013 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=120

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_v120.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_DLL_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_DLL_v120.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_v120_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_v120.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2012 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=110

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_v110.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_DLL_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_DLL_v110.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_v110_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_v110.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


//----------------------------------------------------------------------------
// * VS2010 Lib 
//----------------------------------------------------------------------------
#elif _MSC_PLATFORM_TOOLSET>=100

#if defined(_M_X64)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses64_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses64_v100.lib")
		#endif
	#endif
#elif defined(_M_IX86)
	//1) DLL version일 때
	#ifdef _DLL 
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_DLL_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_DLL_v100.lib")
		#endif

	//2) DLL이 아닐 때
	#else
		#ifdef _DEBUG
			#pragma comment (lib,"CGNetSocketClasses_v100_Debug.lib")
		#else
			#pragma comment (lib,"CGNetSocketClasses_v100.lib")
		#endif
	#endif
#else
	#error	"Unsupport Platform"
#endif


#else

#endif


#endif