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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGMessageMap
//
// 1. CGMessageMap�̶�...?
//    1) Message�� ó���� ���Ǹ� Map���·� �ۼ��� �� �ֵ��� �� ���̴�.
//
// 2. CGMessageMap�� ����
//    CGCII Message Map�� ����ϱ� ���ؼ��� �Ʒ��� ���� ������ �ۼ��� �ʿ��ϴ�.
//		
//    1) ���� Message Map�� ����ϰ����ϴ� Ŭ������ ���ǿ� �Ʒ��� ���� 
//       'DECLARE_CGMESSAGE_MAP'�� �߰��� �ش�.
//       �Ϲ������� �� ���� Class�� �����ϴ� ������Ͽ� �ۼ��Ѵ�.
//
//       class foo
//       {
//          ....
//
//          DECLARE_CGMASSAGE_MAP
//          ....
//       };
//
//    2) CPP���Ͽ� Message Map�� �Ʒ��� ���� �ۼ��Ѵ�.
//       Message Map ������ ������ 'BEGIN_CGMESAAGE_MAP(Ŭ������)' Ű���带
//       �ۼ��Ѵ�.
//       �׸��� �ʿ��� Message�� �� Message�� �޾��� �� ó���� �Լ����
//       �Լ��� �Ķ���͸� �Ʒ��� ���� ���ش�.
//             ON_MESSAGE(�޽���, �Լ���, �Ķ������)
//       �̶� �Ķ���ʹ� �ݵ�� CGMSG�� ��ӹ��� ���̾�� �ϰ� �޽����� ������ ��
//       ���� ��ġ�ؾ� �Ѵ�.
//       �⺻���� ���� �Ʒ��� ����.
//
//       BEGIN_CGMESSAGE_MAP(foo)
//             CGMESSAGE_TYPE(MESSAGE_SEND_A, OnMessage_A, CGMSG);
//             CGMESSAGE_TYPE(MESSAGE_SEND_B, OnMessage_B, CGMSG);
//       END_CGMESSAGE_MAP
//
//    3) �� �� OnMessage_A�Լ��� �Ʒ��� ���� �ۼ��Ѵ�.
//
//       int foo::OnMessage_A(CGMSG& _Msg)
//       {
//           ...
//       }
//
//       *����: BEGIN_MESSAGE_MAP�� �ݵ�� CPP���Ͽ� �ۼ��ؾ� �ϸ� �������(.h)��
//              �ۼ��ؼ��� �ȵȴ�.
//    
//    4) ���������� �� Message Map�� ����ϱ� ���ؼ��� �ݵ�� �޽����� �޴� �Լ�
//       �� OnMessage()�Լ��� �Ʒ��� ���� Ű���带 �߰��� �־�� �Ѵ�.
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

// Attribute�� Message Map
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
