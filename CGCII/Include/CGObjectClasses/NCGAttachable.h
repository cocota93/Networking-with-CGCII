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

 @class		NCGAttachable
 @brief		ICGAttachable<TTYPE>�� ������ Ŭ����
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
	//! @brief �پ� �ִ� ��ü�� �ϳ��� ���°� �˻��Ѵ�. @return true �ϳ��� ���� @return false ��� ���� �ʴ�.
			bool				is_attached_empty() const				{	return m_container.empty();}
	//! @brief �پ� �ִ� ��ü�� �ϳ��� �ִ°� �˻��Ѵ�. @return true �ϳ��� �ִ�. @return false �ϳ��� ����.
			bool				is_attached_exist() const				{	return !m_container.empty();}
	//! @brief �پ� �ִ� ��ü�� ������ ��´�. @return �پ� �ִ� ��ü�� ����
			size_t				attached_size() const					{	return m_container.size();}

	//! @brief �ش� ��ü�� �پ� �ִ��� Ȯ���Ѵ�. @param _Child ã�� ��ü @return !nullptr ã�� @return nullptr ã�� ����
			CGPTR<TTYPE>		find_attachable(TTYPE* _Child);

	//! @brief ��� ���� ��ü�� �����.
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
	// Check) nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(_Child!=nullptr);

	// Check)
	RETURN_IF(_Child==nullptr, false);

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	CGASSERT_ERROR(_Child!=static_cast<TTYPE*>(this));

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	RETURN_IF(_Child==static_cast<TTYPE*>(this), false);

	// 1) �̹� �����ϴ��� ã�´�.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _Child);

	// Check) �̹� �����ϸ� �׳� ASSERT �߻�!
	CGASSERT_ERROR(iterFind==m_container.end());

	// Check) �̹� �����ϸ� �׳� false�� �����Ѵ�.
	RETURN_IF(iterFind!=m_container.end(), false);

	// 2) �߰��ϱ�
	m_container.push_back(_Child);

	// Return) ����!!
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
	// 1) ���� ã�´�.
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

	// 1) m_container�� ����
	vecTemp.assign(m_container.begin(), m_container.end());

	// Declare)
	int	iCount	 = static_cast<int>(vecTemp.size());

	// 2) ��� Detach
	for(auto& iter:vecTemp)
	{
		ProcessDetach(iter);
	}

	// Return) 
	return	iCount;
}
