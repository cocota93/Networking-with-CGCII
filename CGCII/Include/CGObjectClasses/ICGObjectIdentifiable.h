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

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		ICGObjectIdentifiable
 @brief		��ü�� ���� ���а��� ������ �������̽� Ŭ����
 @todo		
 @ref		OBJECT_ID, ICGMessageable, ICGNameable
 @details	\n
 ��ü�� ���� ���а��� ������ �������̽� Ŭ�����̴�.
 OBJECT_ID�� ��ü�� ���������� 16Byte�� ũ�⸦ ������ �ִ�.

*/
//-----------------------------------------------------------------------------
class ICGObjectIdentifiable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGObjectIdentifiable() : m_idObject(0, 0)					{}
	//! @brief ��� �� ������ �Բ� �����Ѵ�. @param _Type ������ '��� ��'
			ICGObjectIdentifiable(uint64_t _Type) : m_idObject(0, _Type){}
	//! @brief ��� ���� ����(factory)�� ������ �Բ� �����Ѵ�.
			ICGObjectIdentifiable(eOBJECT_TYPE _Type, uint32_t _Factory) : m_idObject(0, _Type, _Factory){}
	//! @brief OBJECT_ID�� ������ �Բ� �ʱ�ȭ�Ѵ�. @param _id ������ '��ü ID'
			ICGObjectIdentifiable(const OBJECT_ID& _id) : m_idObject(_id){}
	virtual	~ICGObjectIdentifiable()									{}
	

// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief ��ü ID�� ��´�. @return true '��ü ID;
			const OBJECT_ID&	GetObjectID() const						{ return m_idObject;}
	//! @brief ��ü ���� ��´�. @return true '��ü ��'
			eOBJECT_TYPE		GetObjectType() const					{ return m_idObject.dwType;}
	//! @brief ������ ����(factory) �ε����� ��´�. @return true ���� �ε���
			uint32_t			GetObjectFactory() const				{ return m_idObject.dwFactory;}
	//! @brief ������ ��ü �ø��� ���� ��´�. @return true ��ü �ø��� ��
			uint64_t			GetObjectSerial() const					{ return m_idObject.qwSerial; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	//! @brief '��ü ��'�� �����Ѵ�. @param _Type �����ϰ��� �ϴ� '��ü ��'
			void				SetObjectType(_In_ eOBJECT_TYPE _eType)	{ m_idObject.dwType=_eType;}
			void				SetObjectType(_In_ uint64_t _Type)		{ m_idObject.qwType=_Type;}
	//! @brief '��ü �ø���' ���� �����Ѵ�. @param _Serial ������ '��ü �ø���' ��
			void				SetObjectSerial(_In_ uint64_t _Serial) { m_idObject.qwSerial = _Serial; }
	//! @brief '��ü ID'�� �����Ѵ�. @param _id �����ϰ��� �ϴ� '��ü ID'
			void				SetObjectID(_In_ const OBJECT_ID& _id) { m_idObject = _id; }
private:
			OBJECT_ID			m_idObject;
};
