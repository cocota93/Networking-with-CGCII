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
	//!	@brief ��ϵ� '��ü'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ��� ����. @return false ��� ���� ����.
	bool						IsEmpty() const							{	return m_container.empty();}
	//!	@brief ��ϵ� '���� ��ü'���� �ϳ��� �ִ��� Ȯ���Ѵ�. @return true ��� ���� ����. @return false ��� ����.
	bool						IsExist() const							{	return !m_container.empty();}

	//! @brief ��ü�� ��ϵǾ����� Ȯ���Ѵ�. @param _pSource ã���� �ϴ� ��ü @return !nullptr ã�� @return nullptr ��ã��
	CGPTR<TTYPE>				Find(TTYPE* _pSource);
	//! @brief ��ϵ� ��� ��ü�� _fExecut�Լ��� �����Ѵ�. @param _fExecute ������ �Լ�
	void						ForEach(const std::function<void(TTYPE* _pSource)>& _fExecute);
	//! @brief ��� ��ϵ� ��ü�� �����ϰ� �ʱ�ȭ �Ѵ�.
	int							Clear();

	//! @brief ������ ���ͷ������� ó�� �ݺ��ڸ� ��´�. @return ������ ���ͷ������� ó�� �ݺ���
	typename TCON::iterator		begin()						{	return m_container.begin();}
	//! @brief ������ ���ͷ������� ó�� �ݺ��ڸ� ��´�. @return ������ ���ͷ������� ó�� �ݺ���
	typename TCON::reverse_iterator	rbegin()					{	return m_container.rbegin();}
	//! @brief ������ ���ͷ�������  �ݺ��ڸ� ��´�. @return ������ ���ͷ������� �� �ݺ���
	typename TCON::iterator		end()						{	return m_container.end();}
	//! @brief ������ ���ͷ������� �� �ݺ��ڸ� ��´�. @return ������ ���ͷ������� �� �ݺ���
	typename TCON::reverse_iterator	rend()						{	return m_container.rend();}
	//! @brief ��ϵ� '��ü'�� �� @return ��ϵ� '��ü'�� ��
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
	// Check) nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(_pSource!=nullptr);

	// Check)
	RETURN_IF(_pSource==nullptr, false);

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	CGASSERT_ERROR(_pSource!=static_cast<TTYPE*>(this));

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	RETURN_IF(_pSource==static_cast<TTYPE*>(this), false);

	// 1) �̹� �����ϴ��� ã�´�.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pSource);

	// Check) �̹� �����ϸ� �׳� ASSERT �߻�!
	CGASSERT_ERROR(iterFind==m_container.end());

	// Check) �̹� �����ϸ� �׳� false�� �����Ѵ�.
	RETURN_IF(iterFind!=m_container.end(), false);

	// 2) �߰��ϱ�
	m_container.push_back(_pSource);

	// Return) ����!!
	return	true;
}

template <typename TTYPE, typename TCON>
bool NCGRegisterable<TTYPE, TCON>::ProcessUnregister(TTYPE* _pSource)
{
	// Check) nullptr�̸� �ȉ´�.
	CGASSERT_ERROR(_pSource!=nullptr);

	// Check)
	RETURN_IF(_pSource==nullptr, false);

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	CGASSERT_ERROR(_pSource!=static_cast<TTYPE*>(this));

	// Check) �ڱ� �ڽ��̸� �ȉ´�!
	RETURN_IF(_pSource==static_cast<TTYPE*>(this), false);

	// 1) �̹� �����ϴ��� Ȯ���Ѵ�.
	auto iterFind	 = std::find(m_container.begin(), m_container.end(), _pSource);

	// Check) ã�� ���ߴ�!
	RETURN_IF(iterFind==m_container.end(), false);

	// 2) ã�� ��ü�� �����.
	m_container.erase(iterFind);

	// Return) ����!!
	return	true;
}

template <typename TTYPE, typename TCON>
CGPTR<TTYPE> NCGRegisterable<TTYPE, TCON>::Find(TTYPE* _pSource)
{
	// 1) ���� ã�´�.
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
		// - Renderer�� �߰��Ѵ�.
		_fExecute(iter);
	}
}

template <typename TTYPE, typename TCON>
int NCGRegisterable<TTYPE, TCON>::Clear()
{
	// Declare) 
	vector<CGPTR<TTYPE>>	vecTemp;

	// 1) m_container�� ����
	vecTemp.assign(m_container.begin(), m_container.end());

	// 2) ������ ���Ѵ�.
	int	iCount	 = vecTemp.size();

	// 3) ��� Detach
	for(auto& iter:vecTemp)
	{
		ProcessDetach(iter);
	}

	// Return)
	return	iCount;
}
