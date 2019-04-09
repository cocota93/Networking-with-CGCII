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
//-----------------------------------------------------------------------------
//
// CGMessageMap
//
// 1. CGMessageMap이란...?
//    1) Message의 처리를 정의를 Map형태로 작성할 수 있도록 한 것이다.
//
// 2. CGMessageMap의 정의
//    CGCII Message Map을 사용하기 위해서는 아래와 같은 내용의 작성이 필요하다.
//		
//    1) 먼저 Message Map을 사용하고자하는 클래스의 정의에 아래와 같이 
//       'DECLARE_CGMESSAGE_MAP'을 추가해 준다.
//       일반적으로 이 것은 Class를 정의하는 헤더파일에 작성한다.
//
//       class foo
//       {
//          ....
//
//          DECLARE_CGMASSAGE_MAP
//          ....
//       };
//
//    2) CPP파일에 Message Map은 아래와 같이 작성한다.
//       Message Map 정의의 시작은 'BEGIN_CGMESAAGE_MAP(클래스명)' 키워드를
//       작성한다.
//       그리고 필요한 Message와 그 Message를 받았을 때 처리할 함수명과
//       함수의 파라메터를 아래와 같이 써준다.
//             ON_MESSAGE(메시지, 함수명, 파라메터형)
//       이때 파라메터는 반드시 CGMSG를 상속받은 형이어야 하고 메시지를 전송할 때
//       형과 일치해야 한다.
//       기본적인 예는 아래와 같다.
//
//       BEGIN_CGMESSAGE_MAP(foo)
//             CGMESSAGE_TYPE(MESSAGE_SEND_A, OnMessage_A, CGMSG);
//             CGMESSAGE_TYPE(MESSAGE_SEND_B, OnMessage_B, CGMSG);
//       END_CGMESSAGE_MAP
//
//    3) 이 때 OnMessage_A함수는 아래와 같이 작성한다.
//
//       int foo::OnMessage_A(CGMSG& _Msg)
//       {
//           ...
//       }
//
//       *주의: BEGIN_MESSAGE_MAP은 반드시 CPP파일에 작성해야 하며 헤더파일(.h)에
//              작성해서는 안된다.
//    
//    4) 마지막으로 이 Message Map을 사용하기 위해서는 반드시 메시지를 받는 함수
//       즉 OnMessage()함수에 아래와 같은 키워드를 추가해 주어야 한다.
//
//       int foo::OnMessage(CGMSG& _Msg)
//       {
//           EXECUTE_CGMESSAGE_MAP(_Msg);
//
//           ...
//
//           return FALSE;
//       }
//
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// ...
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
	#pragma warning(disable:4065)
#endif


//-----------------------------------------------------------------------------
// CG Message Map
//-----------------------------------------------------------------------------
// 1) Declare Message Map
#define	DECLARE_CGMESSAGE_MAP	uint32_t	ExecuteMessage(CGMSG& _Msg);

// 2) Declare Message Map
#define	DEFINE_PROCESS_MESSAGE			virtual	int ProcessMessage(CGMSG& _Msg) override	{	EXECUTE_CGMESSAGE_MAP(_Msg); return 0;}
#define	DEFINE_PROCESS_MESSAGE_BLOCK	virtual	int ProcessMessage(CGMSG& _Msg) override	{	EXECUTE_CGMESSAGE_MAP(_Msg); return 1;}
#define	DEFINE_ON_MESSAGE				virtual	int OnMessage(CGMSG& _Msg) override			{	EXECUTE_CGMESSAGE_MAP(_Msg); return 0;}
#define	DEFINE_ON_MESSAGE_BLOCK			virtual	int OnMessage(CGMSG& _Msg) override			{	EXECUTE_CGMESSAGE_MAP(_Msg); return 1;}

// 3) Message Mask
const uint32_t		CGMSG_MASK		 = 0x00ffffff;

// 4) Execute Message Function
#define	EXECUTE_CGMESSAGE_MAP(msg)								\
{																\
	auto result=ExecuteMessage(msg);							\
																\
	if(result!=0)												\
		return result;											\
}

// 5) Execute Message Function
#define	EXECUTE_CLASS_CGMESSAGE_MAP(class_type, msg)			\
{																\
	auto result=class_type::ExecuteMessage(msg);				\
																\
	if(result!=0)												\
		return result;											\
}

// 6) Begin Message Map head
#define	BEGIN_CGMESSAGE_MAP_HEAD								\
	{															\
		switch(_Msg.message)									\
		{														\
		default:												\
				{												\
					return	FALSE;

#define	BEGIN_CGMESSAGE_MAP_HEAD_MASK(mask)						\
	{															\
		switch(_Msg.message & mask)							\
		{														\
		default:												\
				{												\
					return	FALSE;


// head) Execute Message Function
#define	BEGIN_CGMESSAGE_MAP(class_name)							\
	uint32_t class_name::ExecuteMessage(CGMSG& _Msg)				\
	BEGIN_CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_MASK(class_name)					\
	uint32_t class_name::ExecuteMessage(CGMSG& _Msg)				\
	BEGIN_CGMESSAGE_MAP_HEAD_MASK(CGMSG_MASK)



#define	BEGIN_CGMESSAGE_MAP_TEMPLATE(class_name, type_a, type_b)		\
	uint32_t class_name<type_a, type_b>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE3(class_name, type_a, type_b, type_c)		\
	uint32_t class_name<type_a, type_b, type_c>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE4(class_name, type_a, type_b, type_c, type_d)		\
	uint32_t class_name<type_a, type_b, type_c, type_d>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD

#define	BEGIN_CGMESSAGE_MAP_TEMPLATE5(class_name, type_a, type_b, type_c, type_d, type_e)		\
	uint32_t class_name<type_a, type_b, type_c, type_d, type_e>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD



#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE(class_name, type_a, type_b)	\
	uint32_t class_name<type_a, type_b>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD_MASK(CGMSG_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE3(class_name, type_a, type_b, type_c)	\
	uint32_t class_name<type_a, type_b, type_c>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD_MASK(CGMSG_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE4(class_name, type_a, type_b, type_c, type_d)	\
	uint32_t class_name<type_a, type_b, type_c, type_d>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD_MASK(CGMSG_MASK)

#define	BEGIN_CGMESSAGE_MAP_MASK_TEMPLATE5(class_name, type_a, type_b, type_c, type_d, type_e)	\
	uint32_t class_name<type_a, type_b, type_c, type_d, type_e>::ExecuteMessage(CGMSG& _Msg)		\
	BEGIN_CGMESSAGE_MAP_HEAD_MASK(CGMSG_MASK)


#define	CGMESSAGE_TYPE(msg_type, function, type)				\
				}												\
		case	msg_type:										\
				{												\
					return	function((type&)_Msg);

#define	CGMESSAGE_TYPE_SUB(msg_type, msg_def)					\
				}												\
		case	msg_type:										\
				switch(msg_def)									\
				{												\
				default:										\
						{										\
							return	FALSE;										

// Body) Execute Message Function
#define	ON_CGMESSAGE(message, function, type)					\
						}										\
				case	message:								\
						{										\
							return	function((type&)_Msg);

#define	ON_CGMETHOD_RETURN(message, function, return_type)		\
						}										\
				case	message:								\
						{										\
							CCGBuffer tempBuffer(sizeof(return_type));	\
							tempBuffer.append<return_type>(function());	\
							((CGMSG_BUFFER&)_Msg).Buffer	=tempBuffer;\
							return	TRUE;

#define	ON_CGMETHOD(message, function)							\
						}										\
				case	message:								\
						{										\
							function();							\
							return	TRUE;


#define	END_SUB_CGMESSAGE_MAP									\
						}										\

// tail) Execute Message Function
#define	END_CGMESSAGE_MAP										\
				};												\
		};														\
	}

// Attribute용 Message Map
#define	CGMESSAGE_TYPE_ATTRIBUTE								CGMESSAGE_TYPE_SUB(CGMESSAGE::ATTRIBUTE, ((const CGMSG_BUFFER&)_Msg).Buffer.front<uint32_t>(4) & CGMESSAGE::SYSTEM::MASK)


//-----------------------------------------------------------------------------
// Sub-Message Type
//-----------------------------------------------------------------------------
// 1) Buffer Message
#define	CGMESSAGE_TYPE_SUB_BUFFER								CGMESSAGE_TYPE_SUB(CGMESSAGE::BUFFER,	((const CGMSG_BUFFER&)_Msg).Buffer.front<uint32_t>(4) & CGMESSAGE::SYSTEM::MASK)
#define	CGMESSAGE_TYPE_SUB_BUFFER_MESSAGE(msg)					CGMESSAGE_TYPE_SUB(msg,					((const CGMSG_BUFFER&)_Msg).Buffer.front<uint32_t>(4) & CGMESSAGE::SYSTEM::MASK)

// 2) Declare Message Map
#define	DECLARE_CGMESSAGE_MAP_SUB(name)	uint32_t	ExecuteMessage##name(CGMSG& _Msg);

// 3) Execute Message Function
#define	EXECUTE_CGMESSAGE_MAP_SUB(name, msg)					\
{																\
	auto result=ExecuteMessage##name(msg);						\
																\
	if(result!=0)												\
		return result;											\
}

// head) Execute Message Function
#define	BEGIN_CGMESSAGE_MAP_SUB(class_name, name)				\
	uint32_t class_name::ExecuteMessage##name(CGMSG& _Msg)	\
	{															\
		switch(_Msg.message)									\
		{														\
		default:												\
				{												\
					return	FALSE;

// head) Execute Message Function
#define	BEGIN_CGMESSAGE_MAP_SUB_MASK(class_name, name)			\
	uint32_t class_name::ExecuteMessage##name(CGMSG& _Msg)	\
	{															\
		switch(_Msg.message & CGMSG_MASK)						\
		{														\
		default:												\
				{												\
					return	FALSE;


////-----------------------------------------------------------------------------
//// Automation Message
////-----------------------------------------------------------------------------
/*
//// 1) Declare Message Map
//#define	DECLARE_CGAUTOMATION	uint32_t	AutomationMessage(CGMSG& _Msg);
//
//// 2) Execute Message Function
//#define	EXECUTE_AUTOMATION(msg)									\
//{																	\
//	uint32_t dwResult=AutomationMessage(msg);						\
//																	\
//	if(dwResult!=0)													\
//		return dwResult;											\
//}
//
//// 3) Automation head
//#define	BEGIN_CGAUTOMATION_HEAD									\
//	{																\
//		RETURN_IF(_Msg.message!=CGMESSAGE::AUTOMATION, FALSE)		\
//																	\
//		CG3DMSG_AUTOMATION&	rMSG	 = (CG3DMSG_AUTOMATION&)_Msg;	\
//																	\
//		switch(rMSG.dwType)											\
//		{															\
//		default:													\
//				{													\
//					return	FALSE;
//					//return	(__super::AutomationMessage!=nullptr) ? __super::AutomationMessage(_Msg) : FALSE;
//
//
//// Body) On Automation Message Function
//#define	ON_AUTOMATION(message, function, type)					\
//						}											\
//				case	message:									\
//						{											\
//							return	function((type&)_Msg);
*/
