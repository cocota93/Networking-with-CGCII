//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
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

namespace CGExecutable
{

//-----------------------------------------------------------------------------
/**

 @class		CList
 @brief		���� ���� Exectutable ��ü�� ������ �ִ� Executable Ŭ�����̴�.
 @todo		
 @ref		
 @details	\n
 ���� ���� Executable�� list���·� ������ ������ ����� �� �ڽ��� ���� Executable�� ProcessExecute()�� ��� ȣ�����ش�.
 �� ITERATOR�� ��� ���� Executable�� ���� �� �� �ִ�.

*///-----------------------------------------------------------------------------
template <class TEXECUTABLE=ICGExecutable>
class CList :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual protected			ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CList();
	virtual ~CList();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions)
			typedef	circular_list<CGPTR<TEXECUTABLE>>	CONTAINER;
			class ITERATOR;

	// 1) Attach/Detach
	//! @brief Executable '���� ��ü'�� ����Ѵ�. @param _pExecutable ����� '���� ��ü' @return true ��� ���� @return false ��� ����(�Ϲ������� ������ ��ü�� ��ϵǾ� ���� ��� �����Ѵ�.)
			bool				RegisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief ��ϵ� '���� ��ü'�� �����Ѵ�. @param _pExecutable ��������� '���� ��ü' @return true ������� ���� @return false ������� ����(�Ϲ������� �ش� ��ü�� ��ϵǾ� ���� ���� ��� �����Ѵ�.)
			bool				UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief ��� ��ϵ� Executable ��ü���� ��������Ѵ�.
			void				DetachAllExecutable();

	// 2) Iterator
	//! @brief ��ϵ� '���� ��ü'�鿡 �����ϱ� ���� �ݺ��ڸ� ��´�. @return !nullptr �ݺ��� @return nullptr ȹ�� ����
			ITERATOR			GetIterator();

	// 3) ExecutableCount
	//! @brief ��ϵ� '���� ��ü'���� ������ ��´�.	@return	��ϵ� '���� ��ü'���� ����
			size_t				GetExecutableCount() const;
	//!	@brief ��ϵ� '���� ��ü'�� �ϳ��� ������ Ȯ���Ѵ�. @return true ��� ����. @return false ��� ���� ����.
			bool				IsEmpty() const;
	//!	@brief ��ϵ� '���� ��ü'���� �ϳ��� �ִ��� Ȯ���Ѵ�. @return true ��� ���� ����. @return false ��� ����.
			bool				IsExist() const;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;

private:
			LOCKABLE<CONTAINER>				m_listExecutable;
			typename CONTAINER::iterator	m_iterNow;
};


}

#include "CGExecuteclasses/CGExecutableList.inl"