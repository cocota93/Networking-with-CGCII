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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

//#pragma once
////-----------------------------------------------------------------------------
///**
//
// @class		ICGObject
// @brief		��ü�� ���ǿ� ���� ����ϴ� ���� �Ӽ����� ��� ���� �������̽� Ŭ����
// @todo		
// @ref		ICGMessageable, ICGObjectIdentifiable, ICGNameable
// @details	\n
// ��ü�� ���ǿ� ���� ���Ǵ� ���� �Ӽ����� ���� �������̽� Ŭ������ 
// �޽����� ���޹��� �� �ְ� (IMessageable)
// ��ü�� �������� ������(ICGObjectIdentifiable)
// ���ڿ��� �� ��ü�� �̸��� ������(ICGNameable)
// �Ӽ��� ��� ���� ���̴�.
// �� Ŭ������ CGCII���� ���Ǵ� ��ü�� �⺻�� �Ǵ� �������̽� Ŭ�����̴�.
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
//	//! @brief _Index�� �ش��ϴ� ��ü�� �����Ѵ�. @param _Index ã���� �ϴ� ��ü�� �ε��� @param _Object �����ϰ��� �ϴ� ��ü @return true ���� @return false ����
//		template<class T>
//			bool				SET(int _Index, T* _Object);
//	//! @brief _Index�� �ش��ϴ� ��ü�� �����Ѵ�. @param T �����ϰ��� �ϴ� ��ü�� �� @param _Index �����ϰ��� �ϴ� ��ü�� �ε��� @return �����Ǿ� �ִ� ��ü ������
//		template<class T>
//			bool				RESET(int _Index);
//	//! @brief _Index�� �ش��ϴ� ��ü�� ��´�. @param T ã���� �ϴ� ��ü�� �� @param _Index ã���� �ϴ� ��ü�� �ε��� @return �����Ǿ� �ִ� ��ü ������
//		template<class T>
//			CGPTR<T>			GET(int _Index);
//
//	//! @brief Type���� ��� ��ü�� ã�´�. @param _Type ã���� �ϴ� �� @ param _Mask �񱳽� ���� AND�� ����ũ  @param bool _Recursive ����� Ž�� ���� @return true ã�� ��ü
//			vector<CGPTR<ICGObject>> FIND(uint32_t _Type, uint32_t _Mask=0xffffffff, bool _Recursive=false);
//	//! @brief �̸����� ��� ��ü�� ã�´�. @param _str ã���� ��ü�� �̸� @ param _Mask �񱳽� ���� AND�� ����ũ  @param bool _Recursive ����� Ž�� ���� @return true ã�� ��ü
//			CGPTR<ICGObject>	FIND(const _CHAR* _str, uint32_t _Mask=0xffffffff, bool _Recursive=false);
//};
//
//template<class T>
//bool ICGObject::SET(int _Index, T* _Object)
//{
//	// 1) Query�� Message�� �����.
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
//	// 1) Query�� Message�� �����.
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
//	// 1) Query�� Message�� �����.
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
//	// 1) Query�� Message�� �����.
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
//	// 1) Query�� Message�� �����.
//	auto	msg	 = CGMSG_FIND_BY_NAME<ICGObject>(CGFUNCTION_FIND_BY_NAME, _str, _Mask, _Recursive);
//
//	// Declare) 
//	ProcessMessage(msg);
//
//	// Return)
//	return	std::move(msg.pParam);
//}
