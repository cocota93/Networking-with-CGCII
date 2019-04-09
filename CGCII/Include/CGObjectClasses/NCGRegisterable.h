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

 @class		NCGRegisterable
 @brief		
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
template <typename TTYPE, typename TCON=vector<CGPTR<TTYPE>>>
class NCGRegisterable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGRegisterable<TTYPE>
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGRegisterable()	{}
	virtual	~NCGRegisterable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//!	@brief 등록된 '객체'가 하나도 없는지 확인한다. @return true 비어 있음. @return false 비어 있지 않음.
	bool						IsEmpty() const							{	return m_container.empty();}
	//!	@brief 등록된 '실행 객체'들이 하나라도 있는지 확인한다. @return true 비어 있지 않음. @return false 비어 있음.
	bool						IsExist() const							{	return !m_container.empty();}

	//! @brief 객체를 등록되었는지 확인한다. @param _pSource 찾고자 하는 객체 @return !nullptr 찾음 @return nullptr 못찾음
	CGPTR<TTYPE>				Find(TTYPE* _pSource);
	//! @brief 등록된 모든 객체에 _fExecut함수를 실행한다. @param _fExecute 실행할 함수
	void						ForEach(const std::function<void(TTYPE* _pSource)>& _fExecute);
	//! @brief 모든 등록된 객체를 해제하고 초기화 한다.
	int							Clear();

	//! @brief 정방향 이터레이터의 처음 반복자를 얻는다. @return 정방향 이터레이터의 처음 반복자
	typename TCON::iterator		begin()						{	return m_container.begin();}
	//! @brief 역방향 이터레이터의 처음 반복자를 얻는다. @return 역방향 이터레이터의 처음 반복자
	typename TCON::reverse_iterator	rbegin()					{	return m_container.rbegin();}
	//! @brief 정방향 이터레이터의  반복자를 얻는다. @return 정방향 이터레이터의 끝 반복자
	typename TCON::iterator		end()						{	return m_container.end();}
	//! @brief 역방향 이터레이터의 끝 반복자를 얻는다. @return 역방향 이터레이터의 끝 반복자
	typename TCON::reverse_iterator	rend()						{	return m_container.rend();}
	//! @brief 등록된 '객체'의 수 @return 등록된 '객체'의 수
	size_t						size() const							{	return m_container.size();}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Renderable Attach/Detach
	virtual	bool				ProcessRegister(TTYPE* _pSource);
	virtual	bool				ProcessUnregister(TTYPE* _pSource);

protected:
			TCON				m_container;

public:
	typedef	TCON	TCONTAINER;
};

template <typename TTYPE, typename TCON>
bool NCGRegisterable<TTYPE, TCON>::ProcessRegister(TTYPE* _pSource)
{
	// Check) nullptr이면 안됀다.
	CGASSERT_ERROR(_pSource!=nullptr);

	// Check)
	RETURN_IF(_pSource==nullptr, false);

	// Check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_pSource!=static_cast<TTYPE*>(this));

	// Check) 자기 자신이면 안됀다!
	RETURN_IF(_pSource==static_cast<TTYPE*>(this), false);

	// 1) 이미 존재하는지 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pSource);

	// Check) 이미 존재하면 그냥 ASSERT 발생!
	CGASSERT_ERROR(iterFind==m_container.end());

	// Check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iterFind!=m_container.end(), false);

	// 2) 추가하기
	m_container.push_back(_pSource);

	// Return) 성공!!
	return	true;
}

template <typename TTYPE, typename TCON>
bool NCGRegisterable<TTYPE, TCON>::ProcessUnregister(TTYPE* _pSource)
{
	// Check) nullptr이면 안됀다.
	CGASSERT_ERROR(_pSource!=nullptr);

	// Check)
	RETURN_IF(_pSource==nullptr, false);

	// Check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_pSource!=static_cast<TTYPE*>(this));

	// Check) 자기 자신이면 안됀다!
	RETURN_IF(_pSource==static_cast<TTYPE*>(this), false);

	// 1) 이미 존재하는지 확인한다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pSource);

	// Check) 찾지 못했다!
	RETURN_IF(iterFind==m_container.end(), false);

	// 2) 찾은 객체를 지운다.
	m_container.erase(iterFind);

	// Return) 실패!!
	return	true;
}

template <typename TTYPE, typename TCON>
CGPTR<TTYPE> NCGRegisterable<TTYPE, TCON>::Find(TTYPE* _pSource)
{
	// 1) 먼저 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pSource);

	// Check) 
	RETURN_IF(iterFind==m_container.end(), CGPTR<TTYPE>());

	// Return)
	return	(*iterFind);
}

template <typename TTYPE, typename TCON>
void NCGRegisterable<TTYPE, TCON>::ForEach(const std::function<void(TTYPE* _pSource)>& _fExecute)
{
	for(auto& iter:m_container)
	{
		// - Renderer를 추가한다.
		_fExecute(iter);
	}
}

template <typename TTYPE, typename TCON>
int NCGRegisterable<TTYPE, TCON>::Clear()
{
	// Declare) 
	vector<CGPTR<TTYPE>>	vecTemp;

	// 1) m_container에 복사
	vecTemp.assign(m_container.begin(), m_container.end());

	// 2) 갯수를 구한다.
	int	iCount	 = vecTemp.size();

	// 3) 모두 Detach
	for(auto& iter:vecTemp)
	{
		ProcessDetach(iter);
	}

	// Return)
	return	iCount;
}
