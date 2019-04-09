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

namespace CGSchedulable
{
namespace Executable
{

//-----------------------------------------------------------------------------
/**

 @class		CList
 @brief		���� ���� Executable�� ����� ���� �ð����� �������ִ� Schedulable��ü�̴�.
 @todo		
 @ref		
 @details	\n
 RegisterExecutable()�Լ��� ����� Executable�� ����� �� �ִ�.
 ��ϵ� Executable���� �����ð����� ��� ȣ�����ش�.
 ��ϵ� Executable���� GetIterator()�� ������ �� �ִ�.

*///-----------------------------------------------------------------------------
template <class TEXECUTABLE=ICGExecutable>
class CList :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						CGSchedulable::NExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CList(uint32_t _tickGap=1000);
	virtual ~CList();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// Definitions) 
			typedef	circular_list<CGPTR<TEXECUTABLE>>	CONTAINER;
			class ITERATOR;

	// 1) Attach/Detach
	//! @brief '���� ��ü'�� ����Ѵ�. @param _pExecutable ����� '���� ��ü' @return true ���� @return false ����(�̹� ������ ��� �����Ѵ�.)
			bool				RegisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief ��ϵ� '���� ��ü'�� �����Ѵ�. @param _pExecutable ��������� '���� ��ü' @return @return true ���� @return false ����(�ش� ��ü�� �������� ���� ��� �����Ѵ�.)
			bool				UnregisterExecutable(_In_ TEXECUTABLE* _pExecutable);
	//! @brief ��ϵ� ��� '���� ��ü'�� �����Ѵ�.
			void				UnregisterAllExecutable();

	// 2) Iterator
	//! @brief	��ϵ� '���� ��ü'�鿡 �����ϱ� ���� �ݺ��ڸ� ��´�. @return !nullptr �ݺ��� @return nullptr ȹ�� ����
			ITERATOR			GetIterator();

	// 3) ExecutableCount
	//!	@brief ��ϵ� '���� ��ü'�� ������ ��´�. @return ��ϵ� '������ ��ü'�� ��
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
			LOCKABLE<CONTAINER>	m_listExecutable;
			typename CONTAINER::iterator	m_iterNow;
};


}
}

#include "CGExecuteclasses/CGSchedulableExecutableList.inl"
