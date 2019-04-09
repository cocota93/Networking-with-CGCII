//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
//  CODE
//
// 
//
//
//
//----------------------------------------------------------------------------

namespace CODE_TYPE
{
	//-----------------------------------------------------------------------------
	// Code Components
	//-----------------------------------------------------------------------------
	const uint32_t		HEAD_0		 = 0x00000000;		// Reserved for System
	const uint32_t		HEAD_1		 = 0x00100000;		// Reserved for Application
	const uint32_t		HEAD_2		 = 0x00200000;		// Reserved for Script
	const uint32_t		HEAD_3		 = 0x00300000;		// Free

	const uint32_t		SUB_0		 = 0x00000000;
	const uint32_t		SUB_1		 = 0x00010000;
	const uint32_t		SUB_2		 = 0x00020000;
	const uint32_t		SUB_3		 = 0x00030000;
	const uint32_t		SUB_4		 = 0x00040000;
	const uint32_t		SUB_5		 = 0x00050000;
	const uint32_t		SUB_6		 = 0x00060000;
	const uint32_t		SUB_7		 = 0x00070000;
	const uint32_t		SUB_8		 = 0x00080000;
	const uint32_t		SUB_9		 = 0x00090000;
	const uint32_t		SUB_10		 = 0x000a0000;
	const uint32_t		SUB_A		 = SUB_10;
	const uint32_t		SUB_11		 = 0x000b0000;
	const uint32_t		SUB_B		 = SUB_11;
	const uint32_t		SUB_12		 = 0x000c0000;
	const uint32_t		SUB_C		 = SUB_12;
	const uint32_t		SUB_13		 = 0x000d0000;
	const uint32_t		SUB_D		 = SUB_13;
	const uint32_t		SUB_14		 = 0x000e0000;
	const uint32_t		SUB_E		 = SUB_14;
	const uint32_t		SUB_15		 = 0x000f0000;
	const uint32_t		SUB_F		 = SUB_15;

	const uint32_t		TAIL_0		 = 0x00000000;
	const uint32_t		TAIL_1		 = 0x00001000;
	const uint32_t		TAIL_2		 = 0x00002000;
	const uint32_t		TAIL_3		 = 0x00003000;
	const uint32_t		TAIL_4		 = 0x00004000;
	const uint32_t		TAIL_5		 = 0x00005000;
	const uint32_t		TAIL_6		 = 0x00006000;
	const uint32_t		TAIL_7		 = 0x00007000;
	const uint32_t		TAIL_8		 = 0x00008000;
	const uint32_t		TAIL_9		 = 0x00009000;
	const uint32_t		TAIL_10		 = 0x0000a000;
	const uint32_t		TAIL_A		 = TAIL_10;
	const uint32_t		TAIL_11		 = 0x0000b000;
	const uint32_t		TAIL_B		 = TAIL_11;
	const uint32_t		TAIL_12		 = 0x0000c000;
	const uint32_t		TAIL_C		 = TAIL_12;
	const uint32_t		TAIL_13		 = 0x0000d000;
	const uint32_t		TAIL_D		 = TAIL_13;
	const uint32_t		TAIL_14		 = 0x0000e000;
	const uint32_t		TAIL_E		 = TAIL_14;
	const uint32_t		TAIL_15		 = 0x0000f000;
	const uint32_t		TAIL_F		 = TAIL_15;

	const uint32_t		TAIL_SUB_0	 = 0x00000000;
	const uint32_t		TAIL_SUB_1	 = 0x00000100;
	const uint32_t		TAIL_SUB_2	 = 0x00000200;
	const uint32_t		TAIL_SUB_3	 = 0x00000300;
	const uint32_t		TAIL_SUB_4	 = 0x00000400;
	const uint32_t		TAIL_SUB_5	 = 0x00000500;
	const uint32_t		TAIL_SUB_6	 = 0x00000600;
	const uint32_t		TAIL_SUB_7	 = 0x00000700;
	const uint32_t		TAIL_SUB_8	 = 0x00000800;
	const uint32_t		TAIL_SUB_9	 = 0x00000900;
	const uint32_t		TAIL_SUB_10	 = 0x00000a00;
	const uint32_t		TAIL_SUB_A	 = 0x00000a00;
	const uint32_t		TAIL_SUB_11	 = 0x00000b00;
	const uint32_t		TAIL_SUB_B	 = TAIL_SUB_11;
	const uint32_t		TAIL_SUB_12	 = 0x00000c00;
	const uint32_t		TAIL_SUB_C	 = TAIL_SUB_12;
	const uint32_t		TAIL_SUB_13	 = 0x00000d00;
	const uint32_t		TAIL_SUB_D	 = TAIL_SUB_13;
	const uint32_t		TAIL_SUB_14	 = 0x00000e00;
	const uint32_t		TAIL_SUB_E	 = TAIL_SUB_14;
	const uint32_t		TAIL_SUB_15	 = 0x00000f00;
	const uint32_t		TAIL_SUB_F	 = TAIL_SUB_15;


	//-----------------------------------------------------------------------------
	// Reserved List)
	//-----------------------------------------------------------------------------
	const uint32_t		WINDOWS		 = (HEAD_0 | SUB_0);
	const uint32_t		SYSTEM		 = (HEAD_0 | SUB_1);
	const uint32_t		NETWORK		 = (HEAD_0 | SUB_2);
	const uint32_t		SCRIPT		 = (HEAD_0 | SUB_3);
	const uint32_t		GRAPHICS	 = (HEAD_0 | SUB_4);
	const uint32_t		INIT		 = (HEAD_0 | SUB_5);
	const uint32_t		USER		 = (HEAD_1 | SUB_0);
}



namespace CGMESSAGE
{
	//-----------------------------------------------------------------------------
	//
	// 1. Windows Message
	//
	//-----------------------------------------------------------------------------
	namespace WINDOWS
	{
		// 1) User Messages
		const uint32_t	USER_RESERVED	 = (CODE_TYPE::WINDOWS | CODE_TYPE::TAIL_0 | CODE_TYPE::TAIL_SUB_4);	// Windows User Message

		// Message Definitions)
		const uint32_t	NOTIFY			 = (USER_RESERVED+0);
		const uint32_t	NOTIFY_UPDATE	 = (USER_RESERVED+1);

		// 2) User Messages
		const uint32_t	USER			 = (CODE_TYPE::WINDOWS | CODE_TYPE::TAIL_0 | CODE_TYPE::TAIL_SUB_5);	// Windows User Message
	}


	//-----------------------------------------------------------------------------
	//
	// 2. Common
	//
	//-----------------------------------------------------------------------------
	namespace SYSTEM
	{
		// 1) Message
		const uint32_t	FLAG_RELIABLE			 = 0x80000000;
		const uint32_t	MASK					 = 0x0fffffff;

		// 2) Message for System(5~B(11))
		const uint32_t	FACTORY					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_0);		// (Reserved for CGObjectClasses)
		const uint32_t	EXECUTE					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_1);		// (Reserved for CGExecuteClasses)
		const uint32_t	POOL					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_2);		// (Reserved for CGPoolClasses)
		const uint32_t	LOG						 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_3);		// (Reserved for Log)
		const uint32_t	BUFFER					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_4);		// (Reserved for Buffers)

		// 3) State
		const uint32_t	UPDATE_STATE			 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_3 |  1);// State Change

		// 4) Contexts
		const uint32_t	CONTEXT					 = (CODE_TYPE::SYSTEM | CODE_TYPE::TAIL_4);

		// 5) Message for network message
		const uint32_t	MESSAGE					 = CGMESSAGE::SYSTEM::BUFFER | 0x02000000;
	}


	//-----------------------------------------------------------------------------
	//
	// 3. Basese
	//
	//-----------------------------------------------------------------------------
	namespace NETWORK
	{
		namespace SOCKET	{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_0);}
		namespace P2P		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_1);}
		namespace UPDATE	{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_2);}
		namespace SECURITY	{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_3);}
		namespace USER		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_A);}
	}

	namespace SERVER
	{
		namespace ROOM		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_4);}
		namespace EVENT		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_5);}
		namespace QUERY		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_6);}
		namespace WEB		{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_7);}
		namespace ACCOUNT	{ const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_8);}
	}

	namespace ADMIN
	{
		const uint32_t	BASE = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_9);

		const uint32_t	TEST = (CODE_TYPE::NETWORK | CODE_TYPE::TAIL_9) | 1;
		
	}


	//-----------------------------------------------------------------------------
	//
	// 4. Attributes
	//
	//-----------------------------------------------------------------------------
	namespace ATTRIBUTE
	{
		// 1) Base
		const uint32_t	BASE					 = (CODE_TYPE::SCRIPT | CODE_TYPE::TAIL_0);

		// 2) Attributes
		const uint32_t	NAME					 = (BASE | CODE_TYPE::TAIL_SUB_0 |   1);
		const uint32_t	GET_ALL_ATTRIBUTE_INFO	 = (BASE | CODE_TYPE::TAIL_SUB_0 |   2);
		const uint32_t	GET_ALL_ATTRIBUTES		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   3);
		const uint32_t	GET_ATTRIBUTE_COUNT		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   4);
		const uint32_t	GET_ALL_METHOD_INFO		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   5);
		const uint32_t	GET_ALL_METHODES		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   6);
		const uint32_t	GET_METHOD_COUNT		 = (BASE | CODE_TYPE::TAIL_SUB_0 |   7);
		const uint32_t	GET_TYPE_NAME			 = (BASE | CODE_TYPE::TAIL_SUB_0 |   8);
		const uint32_t	GET_TYPE_ID				 = (BASE | CODE_TYPE::TAIL_SUB_0 |   9);
		const uint32_t	GET_ENTITY_NAME			 = (BASE | CODE_TYPE::TAIL_SUB_0 |  10);
		const uint32_t	GET_ENTITY_ID			 = (BASE | CODE_TYPE::TAIL_SUB_0 |  11);
	}


	//-----------------------------------------------------------------------------
	//
	// 5. Automation
	//
	//-----------------------------------------------------------------------------
	namespace AUTOMATION
	{
		// 1) ...
		const uint32_t	BASE					 = (CODE_TYPE::SCRIPT | CODE_TYPE::TAIL_1);

		// 2) 
		const uint32_t	MEMBER_FUNCTION			 = (BASE | CODE_TYPE::TAIL_SUB_0 | 1);
		const uint32_t	MEMBER_SET				 = (BASE | CODE_TYPE::TAIL_SUB_0 | 2);
		const uint32_t	MEMBER_RESET			 = (BASE | CODE_TYPE::TAIL_SUB_0 | 3);
		const uint32_t	MEMBER_GET				 = (BASE | CODE_TYPE::TAIL_SUB_0 | 4);
	}												   

	//-----------------------------------------------------------------------------
	//
	// 6. Graphics
	//
	//-----------------------------------------------------------------------------
	// 1) Message for Game Application(8~12)
	namespace GRAPHICS
	{
		const uint32_t	BASE					 = (CODE_TYPE::GRAPHICS | CODE_TYPE::TAIL_0);
		const uint32_t	UPDATE					 = (CODE_TYPE::GRAPHICS | CODE_TYPE::TAIL_1);
	}
											

	//-----------------------------------------------------------------------------
	//
	// 7. Users
	//
	//-----------------------------------------------------------------------------
	const uint32_t	USER						 = (CODE_TYPE::USER | CODE_TYPE::TAIL_0);
}

// Convertability) 
const uint32_t	CGNETMESSAGE		 = CGMESSAGE::SYSTEM::MESSAGE;


//-----------------------------------------------------------------------------
// Definitions)
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4239)
#endif
																 
const int	CGRETURN_VALUE_FAIL			 = 0;
const int	CGRETURN_VALUE_SUCCESS		 = 0;
const int	CGRETURN_VALUE_STOP			 = 1;
const int	CGRETURN_VALUE_CONTINUE		 = -1;


//-----------------------------------------------------------------------------
// 1. CGMSG-기본
//-----------------------------------------------------------------------------
typedef struct CGMSG
{
public:
			CGMSG() : message(0), pSource(nullptr) 	{}
			CGMSG(uint32_t _Message) : message(_Message), pSource(nullptr)	{}
			CGMSG(uint32_t _Message, void* _pSource) : message(_Message), pSource(_pSource)	{}
			template <class TSOURCE>
			CGMSG(uint32_t _Message, TSOURCE* _pSource) : message(_Message), pSource(_pSource)	{}
public:
			template <class TSOURCE>
			TSOURCE*			GetSource() const				{	return (TSOURCE*)pSource;}

			template <class TSOURCE>
			void				SetSource(TSOURCE* _pSource) 	{	pSource=_pSource;}
public:
			uint32_t			message;
			void*				pSource;
} *LPCGMSG;


//-----------------------------------------------------------------------------
// 2. CGMSG- Window message용
//-----------------------------------------------------------------------------
typedef struct CGMSG_WINDOW : public CGMSG
{
public:
			CGMSG_WINDOW()				{}
			CGMSG_WINDOW(uint32_t _Message, void* _pSource, WPARAM _wParam=0, LPARAM _lParam=0) : CGMSG(_Message, _pSource), wParam(_wParam), lParam(_lParam)  	{}
public:
			WPARAM				wParam;
			LPARAM				lParam;
} *LPCGMSG_WINDOW;


//-----------------------------------------------------------------------------
// 4. COMMAND용
//-----------------------------------------------------------------------------
class CGMSG_COMMAND : public CGMSG
{
public:
	CGMSG_COMMAND()				{}
	CGMSG_COMMAND(uint32_t _Message, uint32_t _Command) : CGMSG(_Message), dwCommand(_Command)	{}

public:
			uint32_t			dwCommand;
};

struct CGMSG_NOTIFY : public CGMSG_COMMAND
{
public:
			CGMSG_NOTIFY()															{}
			CGMSG_NOTIFY(uint32_t _Message, uint32_t _Command, uintptr_t _lPara=0, uintptr_t _wParam=0) : CGMSG_COMMAND(_Message, _Command), lParam(_lPara), wParam(_wParam)	{}
public:
			uintptr_t			lParam;
			uintptr_t			wParam;
};


//-----------------------------------------------------------------------------
// 5. CGMSG- DATA...
//-----------------------------------------------------------------------------
template <class TDATA>
struct CGMSG_DATA : public CGMSG
{
public:
			CGMSG_DATA()			{}
			CGMSG_DATA(uint32_t _message, const TDATA& _Data) : CGMSG(_message), sData(_Data)	{}
public:
			TDATA				sData;
};
