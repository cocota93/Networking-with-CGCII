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

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGObjectIdentifiable
 @brief		객체의 고유 구분값을 가지는 인터페이스 클래드
 @todo		
 @ref		OBJECT_ID, ICGMessageable, ICGNameable
 @details	\n
 객체의 고유 구분값을 가지는 인터페이스 클래스이다.
 OBJECT_ID가 객체의 고유값으로 16Byte의 크기를 가지고 있다.

*/
//-----------------------------------------------------------------------------
class ICGObjectIdentifiable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGObjectIdentifiable() : m_idObject(0, 0)					{}
	//! @brief 대상 형 설정과 함께 생성한다. @param _Type 설정할 '대상 형'
			ICGObjectIdentifiable(uint64_t _Type) : m_idObject(0, _Type){}
	//! @brief 대상 형과 공상(factory)의 설정과 함께 생성한다.
			ICGObjectIdentifiable(eOBJECT_TYPE _Type, uint32_t _Factory) : m_idObject(0, _Type, _Factory){}
	//! @brief OBJECT_ID의 설정과 함께 초기화한다. @param _id 설정할 '객체 ID'
			ICGObjectIdentifiable(const OBJECT_ID& _id) : m_idObject(_id){}
	virtual	~ICGObjectIdentifiable()									{}
	

// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief 객체 ID를 얻는다. @return true '객체 ID;
			const OBJECT_ID&	GetObjectID() const						{ return m_idObject;}
	//! @brief 객체 형을 얻는다. @return true '객체 형'
			eOBJECT_TYPE		GetObjectType() const					{ return m_idObject.dwType;}
	//! @brief 설정된 공장(factory) 인덱스를 얻는다. @return true 공장 인덱스
			uint32_t			GetObjectFactory() const				{ return m_idObject.dwFactory;}
	//! @brief 설정된 객체 시리얼 값를 얻는다. @return true 객체 시리얼 값
			uint64_t			GetObjectSerial() const					{ return m_idObject.qwSerial; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief '객체 형'을 설정한다. @param _Type 설정하고자 하는 '객체 형'
			void				SetObjectType(_In_ eOBJECT_TYPE _eType)	{ m_idObject.dwType=_eType;}
			void				SetObjectType(_In_ uint64_t _Type)		{ m_idObject.qwType=_Type;}
	//! @brief '객체 시리얼' 값을 설정한다. @param _Serial 설정할 '객체 시리얼' 값
			void				SetObjectSerial(_In_ uint64_t _Serial) { m_idObject.qwSerial = _Serial; }
	//! @brief '객체 ID'를 설정한다. @param _id 설정하고자 하는 '객체 ID'
			void				SetObjectID(_In_ const OBJECT_ID& _id) { m_idObject = _id; }
private:
			OBJECT_ID			m_idObject;
};
