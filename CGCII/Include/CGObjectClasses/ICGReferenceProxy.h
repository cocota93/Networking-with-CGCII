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
/**

 @class		ICGReferenceProxy
 @brief		����ϴ� ������� Ŭ�����̴�.
 @todo		
 @ref		CGPTR
 @details	\n
 ������� �Ӽ��� ������ �������̽� Ŭ������ ����������  ��������� ������ �ִ�.
 �� ��������� ó�� �����ɶ��� 0���� �ʱ�ȭ �Ǹ�
 AddReference()�Լ��� ȣ���ϸ� ������� 1�� �����ϰ� �ȴ�.
 Release()�Լ��� ȣ���ϸ� ������� 1�� �����ϰ� �ȴ�.
 �� ��������� 0�� �Ǹ� OnFinalRelease()�Լ��� ȣ�����ش�.
 OnFinalRelease()�Լ��� �������ϸ� ��������� 0�� �Ǿ��� �� ������ ������ 
 �� �� �ִ�.
 �̶� ������� ������ �����忡 �����ϰ� �����Ѵ�.

 �Ϲ������� ICGReferenceable�� �����Ҵ�� ��ü�� �ڵ��Ҵ������� ���� ���ȴ�.

*/
//-----------------------------------------------------------------------------
class ICGReferenceProxy
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			ICGReferenceProxy(ICGReferenceable* _pBoss) : m_pBoss(_pBoss) {}
			ICGReferenceProxy(const ICGReferenceProxy& _Copy): m_pBoss(_Copy.m_pBoss) {}
	virtual	~ICGReferenceProxy()										{}


// ****************************************************************************
// Publics) 
// ----------------------------------------------------------------------------
public:
	//! @brief ��������� 1 ������Ų��. @return ������ ������� ��
			int					AddRef()								{	return m_pBoss->AddRef();}
	//! @brief ��������� _Count��ŭ ������Ų��.(_Count���� ������ �ȉ´�.) @param _Count ����ġ @return ������Ų ���� �������
			int					AddRef(int _Count)						{	return m_pBoss->AddRef(_Count);}

	//! @brief ��������� 1 ���ҽ�Ų��. ��������� 0�� �Ǹ� OnFinalRelease/ProcessDispose�� ȣ���Ѵ�. @return ���ҽ�Ų �� �������
			int					Release()								{	return m_pBoss->Release();}

	//! @brief ���� ��������� ��´�. @return ���� �������
			int					GetReferenceCount() const				{	return m_pBoss->GetReferenceCount();}

	//! @brief ��ü�� ����ϵ��� �����Ѵ�. Ǯ���� �Ҵ�� ��ü�� ��� Disuse�� �����Ǹ� Ǯ�� �ǵ��� ���� �������� �ʰ� �ٷ� �Ҹ��Ų��. 
			void				SetAsDisuse()							{	m_pBoss->SetAsDisuse();}
			bool				IsDisuse() const						{	return m_pBoss->IsDisuse();}

	//! @brief ����������: ��������� 1 ������Ų��.(AddRef�� �����ϴ�.)
			ICGReferenceProxy&	operator++()							{	m_pBoss->AddRef(); return *this;}
	//! @brief ���ҿ�����: ��������� 1 ���ҽ�Ų��.(Release()�� �����ϴ�.)
			ICGReferenceProxy&	operator--()							{	m_pBoss->Release(); return *this;}
	//! @brief ���ϱ� ������: ��������� rhs��ŭ ������Ų��. @param rhs ����ġ
			void				operator+=(int rhs)						{	m_pBoss->AddRef(rhs);}

	//! @brief ���Կ�����
			ICGReferenceProxy&	operator=(const ICGReferenceProxy&)		{	return *this;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
			ICGReferenceable*	m_pBoss;
};
