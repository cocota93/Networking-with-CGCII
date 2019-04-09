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

 @class		Manager
 @brief		'�ڿ� ��ü'�� �����ϴ� Ŭ����
 @todo		
 @ref		
 @details	\n
 '�ڿ� ��ü'�� ����� �����ϴ� Ŭ�����̴�.
 ��Ŭ������ �����Ǿ� �ִ�.

*/
//-----------------------------------------------------------------------------
namespace CGResource
{

class Manager :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
	typedef	_STRING						PATH_STRING;
	typedef	vector<PATH_STRING>			CONTAINER;
	typedef	CONTAINER::iterator			ITERATOR;
	typedef	CONTAINER::const_iterator	CONST_ITERATOR;

// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			Manager();
	virtual ~Manager();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief '�ڿ� ���'�� ����Ѵ�. @param _strPath ����� '�ڿ� ���' @return true ���� @return false ����
				bool			RegisterResourcePath(_In_z_ const _CHAR* _strPath);
	//! @brief '�ڿ� ���'�� ��������Ѵ�. @param _strPath ��������� '�ڿ� ���' @return true ���� @return false ����
				bool			UnregisterResourcePath(_In_z_ const _CHAR* _strPath);

	//! @brief '������ ó�� �ݺ���'�� ��´�. @return '������ ó�� �ݺ���'
				ITERATOR		begin()									{	return m_vectorPath.begin();}
	//! @brief '������ ó�� �ݺ���'�� ��´�. @return '������ ó�� �ݺ���'
				CONST_ITERATOR	begin() const							{	return m_vectorPath.begin();}
	//! @brief '������ �� �ݺ���'�� ��´�. @return '������ �� �ݺ���'
				ITERATOR		end()									{	return m_vectorPath.end();}
	//! @brief '������ �� �ݺ���'�� ��´�. @return '������ �� �ݺ���'
				CONST_ITERATOR	end() const								{	return m_vectorPath.end();}

	//! @brief ��ϵ� '�ڿ� ���' ���� ��´�. @return ��ϵ� '�ڿ� ���' ��
				size_t			GetRegisteredPathCount() const			{	return m_vectorPath.size();}
	//! @brief '�ڿ� �н�'�� ��´�. @param _Index �ε��� @return '�ڿ� �н�'
				const PATH_STRING& GetResourcePath(size_t _Index)		{	return m_vectorPath[_Index];}

	//! @brief '�ڿ� ������ �̱��� ��ü'�� ��´�. @return '�ڿ������� �̱��� ��ü' ������
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '�ڿ� ������ �̱��� ��ü'�� �����Ѵ�. @ param _pInstance ������ '�ڿ� ������ �̱��� ��ü'
	static	void				SetInstance(_In_ Manager* _pInstance)	{	m_pInstance=_pInstance;}
	//! @brief '�ڿ� ������ �̱��� ��ü'�� �����Ѵ�.
	static	void				ResetInstance()							{	m_pInstance.reset();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
private:
	// 1) Path list
				CONTAINER		m_vectorPath;

	// 2) Instance
	static	CGPTR<Manager>		m_pInstance;
	static	void				InitInstance();
};


}