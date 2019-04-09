//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Object Classes                               *
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

//#pragma once
////-----------------------------------------------------------------------------
///**
//
// @class		ICGObject
// @brief		객체의 정의에 많이 사용하는 공통 속성들을 모아 놓은 인터페이스 클래드
// @todo		
// @ref		ICGMessageable, ICGObjectIdentifiable, ICGNameable
// @details	\n
// 객체의 정의에 많이 사용되는 공통 속성들을 모은 인터페이스 클래스로 
// 메시지를 전달받을 수 있고 (IMessageable)
// 객체의 고유값를 가지며(ICGObjectIdentifiable)
// 문자열로 된 객체의 이름을 가지는(ICGNameable)
// 속성을 모아 놓은 것이다.
// 이 클래스는 CGCII에서 사용되는 객체의 기본이 되는 인터페이스 클래스이다.
//
//*/
////-----------------------------------------------------------------------------
//class ICGObject : 
//// ****************************************************************************
//// Inherited Classes) 
//// ----------------------------------------------------------------------------
//	public						ICGObjectIdentifiable,
//	virtual public				ICGMessageable,
//	virtual public				ICGNameable
//{
//// ****************************************************************************
//// Constructor/Destructor)
//// ----------------------------------------------------------------------------
//public:
//			ICGObject()													{}
//			ICGObject(uint64_t _Type) : ICGObjectIdentifiable(_Type)	{}
//			ICGObject(const OBJECT_ID& _id) : ICGObjectIdentifiable(_id){}
//	virtual	~ICGObject()												{}
//
//
//// ****************************************************************************
//// Public)
//// ----------------------------------------------------------------------------
//public:
//	//! @brief _Index에 해당하는 객체를 설정한다. @param _Index 찾고자 하는 객체의 인덱스 @param _Object 설정하고자 하는 객체 @return true 성공 @return false 실패
//		template<class T>
//			bool				SET(int _Index, T* _Object);
//	//! @brief _Index에 해당하는 객체를 리셋한다. @param T 설정하고자 하는 객체의 형 @param _Index 리셋하고자 하는 객체의 인덱스 @return 설정되어 있던 객체 포인터
//		template<class T>
//			bool				RESET(int _Index);
//	//! @brief _Index에 해당하는 객체를 얻는다. @param T 찾고자 하는 객체의 형 @param _Index 찾고자 하는 객체의 인덱스 @return 설정되어 있는 객체 포인터
//		template<class T>
//			CGPTR<T>			GET(int _Index);
//
//	//! @brief Type으로 대상 객체를 찾는다. @param _Type 찾고자 하는 형 @ param _Mask 비교시 형에 AND될 마스크  @param bool _Recursive 재귀적 탐색 여부 @return true 찾은 객체
//			vector<CGPTR<ICGObject>> FIND(uint32_t _Type, uint32_t _Mask=0xffffffff, bool _Recursive=false);
//	//! @brief 이름으로 대상 객체를 찾는다. @param _str 찾고자 객체의 이름 @ param _Mask 비교시 형에 AND될 마스크  @param bool _Recursive 재귀적 탐색 여부 @return true 찾은 객체
//			CGPTR<ICGObject>	FIND(const _CHAR* _str, uint32_t _Mask=0xffffffff, bool _Recursive=false);
//};
//
//template<class T>
//bool ICGObject::SET(int _Index, T* _Object)
//{
//	// 1) Query용 Message를 만든다.
//	auto	msg	 = CGMSG_SET<T>(_Index, _Object);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	msg.bResult;
//}
//
//template<class T>
//bool ICGObject::RESET(int _Index)
//{
//	// 1) Query용 Message를 만든다.
//	auto	msg	 = CGMSG_SET<T>(_Index, nullptr);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	msg.bResult;
//}
//
//template<class T>
//CGPTR<T> ICGObject::GET(int _Index)
//{
//	// 1) Query용 Message를 만든다.
//	auto	msg	 = CGMSG_GET<T>(_Index);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	msg.pParam;
//}
//
//inline vector<CGPTR<ICGObject>> ICGObject::FIND(uint32_t _Type, uint32_t _Mask, bool _Recursive)
//{
//	// 1) Query용 Message를 만든다.
//	auto	msg	 = CGMSG_SEARCH_BY_TYPE<ICGObject>(CGFUNCTION_SEARCH_BY_TYPE, _Type, _Mask, _Recursive);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	std::move(msg.vectorSource);
//}
//
//inline CGPTR<ICGObject> ICGObject::FIND(const _CHAR* _str, uint32_t _Mask, bool _Recursive)
//{
//	// 1) Query용 Message를 만든다.
//	auto	msg	 = CGMSG_FIND_BY_NAME<ICGObject>(CGFUNCTION_FIND_BY_NAME, _str, _Mask, _Recursive);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	std::move(msg.pParam);
//}
