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
/**

 @class		NCGAttachable
 @brief		ICGAttachable<TTYPE>를 구현한 클래스
 @todo		
 @ref		
 @details	\n

*/
//-----------------------------------------------------------------------------
template <typename TTYPE, typename TCON=vector<CGPTR<TTYPE>>>
class NCGAttachable : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				ICGAttachable<TTYPE>
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NCGAttachable()		{}
	virtual	~NCGAttachable()	{}


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) Empty/Exist
	//! @brief 붙어 있는 객체가 하나도 없는가 검사한다. @return true 하나도 없다 @return false 비어 있지 않다.
			bool				is_attached_empty() const				{	return m_container.empty();}
	//! @brief 붙어 있는 객체가 하나라도 있는가 검사한다. @return true 하나라도 있다. @return false 하나도 없다.
			bool				is_attached_exist() const				{	return !m_container.empty();}
	//! @brief 붙어 있는 객체의 갯수를 얻는다. @return 붙어 있는 객체의 갯수
			size_t				attached_size() const					{	return m_container.size();}

	//! @brief 해당 객체가 붙어 있는지 확인한다. @param _Child 찾을 객체 @return !nullptr 찾음 @return nullptr 찾지 못함
			CGPTR<TTYPE>		find_attachable(TTYPE* _Child);

	//! @brief 모든 붙은 객체를 떼어낸다.
			int					clear();


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
public:
	// 1) Attach/Detach
	virtual	bool				ProcessAttach(_In_ TTYPE* _Child) override;
	virtual	int					ProcessDetach(_In_opt_ TTYPE* _Child) override;

public:
			TCON				m_container;

public:
	typedef	TCON				TCONTAINER;
};


template <typename TTYPE, typename TCON>
bool NCGAttachable<TTYPE, TCON>::ProcessAttach(_In_ TTYPE* _Child)
{
	// Check) nullptr이면 안됀다.
	CGASSERT_ERROR(_Child!=nullptr);

	// Check)
	RETURN_IF(_Child==nullptr, false);

	// Check) 자기 자신이면 안됀다!
	CGASSERT_ERROR(_Child!=static_cast<TTYPE*>(this));

	// Check) 자기 자신이면 안됀다!
	RETURN_IF(_Child==static_cast<TTYPE*>(this), false);

	// 1) 이미 존재하는지 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _Child);

	// Check) 이미 존재하면 그냥 ASSERT 발생!
	CGASSERT_ERROR(iterFind==m_container.end());

	// Check) 이미 존재하면 그냥 false를 리턴한다.
	RETURN_IF(iterFind!=m_container.end(), false);

	// 2) 추가하기
	m_container.push_back(_Child);

	// Return) 성공!!
	return	true;
}

template <typename TTYPE, typename TCON>
int NCGAttachable<TTYPE, TCON>::ProcessDetach(_In_opt_ TTYPE* _Child)
{
	// Check) No nullptr!
	if(_Child==nullptr)
	{
		return	clear();
	}

	// Check) No Self!
	CGASSERT_ERROR(_Child!=static_cast<TTYPE*>(this));

	// Check) No Self!
	RETURN_IF(_Child==static_cast<TTYPE*>(this), 0);

	// 1) Check aleady exists
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _Child);

	// Check) Find?
	RETURN_IF(iterFind==m_container.end(), 0);

	// 2) Delete found item
	m_container.erase(iterFind);

	// Return) Success
	return	true;
}

template <typename TTYPE, typename TCON>
CGPTR<TTYPE> NCGAttachable<TTYPE, TCON>::find_attachable(TTYPE* _Child)
{
	// 1) 먼저 찾는다.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _Child);

	// Check) 
	RETURN_IF(iterFind==m_container.end(), CGPTR<TTYPE>());

	// Return)
	return	(*iterFind);
}

template <typename TTYPE, typename TCON>
int NCGAttachable<TTYPE, TCON>::clear()
{
	// Declare) 
	vector<CGPTR<TTYPE>>	vecTemp;

	// 1) m_container에 복사
	vecTemp.assign(m_container.begin(), m_container.end());

	// Declare)
	int	iCount	 = static_cast<int>(vecTemp.size());

	// 2) 모두 Detach
	for(auto& iter:vecTemp)
	{
		ProcessDetach(iter);
	}

	// Return) 
	return	iCount;
}
