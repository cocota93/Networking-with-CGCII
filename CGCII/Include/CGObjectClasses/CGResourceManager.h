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

 @class		Manager
 @brief		'자원 객체'를 관리하는 클래스
 @todo		
 @ref		
 @details	\n
 '자원 객체'를 등록해 관리하는 클래스이다.
 싱클턴으로 구현되어 있다.

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
	//! @brief '자원 경로'를 등록한다. @param _strPath 등록할 '자원 경로' @return true 성공 @return false 성공
				bool			RegisterResourcePath(_In_z_ const _CHAR* _strPath);
	//! @brief '자원 경로'를 등록해제한다. @param _strPath 등록해제할 '자원 경로' @return true 성공 @return false 성공
				bool			UnregisterResourcePath(_In_z_ const _CHAR* _strPath);

	//! @brief '정방향 처음 반복자'를 얻는다. @return '정방향 처음 반복자'
				ITERATOR		begin()									{	return m_vectorPath.begin();}
	//! @brief '정방향 처음 반복자'를 얻는다. @return '정방향 처음 반복자'
				CONST_ITERATOR	begin() const							{	return m_vectorPath.begin();}
	//! @brief '정방향 끝 반복자'를 얻는다. @return '정방향 끝 반복자'
				ITERATOR		end()									{	return m_vectorPath.end();}
	//! @brief '정방향 끝 반복자'를 얻는다. @return '정방향 끝 반복자'
				CONST_ITERATOR	end() const								{	return m_vectorPath.end();}

	//! @brief 등록된 '자원 경로' 수를 얻는다. @return 등록된 '자원 경로' 수
				size_t			GetRegisteredPathCount() const			{	return m_vectorPath.size();}
	//! @brief '자원 패스'를 얻는다. @param _Index 인덱스 @return '자원 패스'
				const PATH_STRING& GetResourcePath(size_t _Index)		{	return m_vectorPath[_Index];}

	//! @brief '자원 관리자 싱글턴 객체'를 얻는다. @return '자원관리자 싱글턴 객체' 포인터
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '자원 관리자 싱글턴 객체'를 설정한다. @ param _pInstance 설정할 '자원 관리자 싱글턴 객체'
	static	void				SetInstance(_In_ Manager* _pInstance)	{	m_pInstance=_pInstance;}
	//! @brief '자원 관리자 싱글턴 객체'를 리셋한다.
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