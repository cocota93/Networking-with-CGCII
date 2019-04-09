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

template<typename TTYPE> class ICGAttachable;
template<typename TOBJECT> bool ATTACH(ICGAttachable<TOBJECT>* _pTarget, TOBJECT* _Object);
template<typename TOBJECT> bool DETACH(ICGAttachable<TOBJECT>* _pTarget, TOBJECT* _Object);

//-----------------------------------------------------------------------------
/**

 @class		ICGAttachable
 @brief		T���� ��ü�� ���� �� �ִ� �Ӽ� �������̽� Ŭ����
 @todo		
 @ref		
 @details	\n
 T Ŭ���� ��ü�� ���̰ų�(Attach) �پ� �ִ� ��ü�� �����(Detach) �������̽��� ������ �ִ�.

*/
//-----------------------------------------------------------------------------
template <typename TTYPE>
class ICGAttachable : 
// ****************************************************************************
// Inherited Classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
// ****************************************************************************
// Protected)
// ----------------------------------------------------------------------------
public:
	//! @brief _Object ��ü ���̱� ������ �����Ѵ�. @param _pChild '�� ���� ��ü' @return true ���� @return false ����(�Ϲ������� �̹� �پ� ���� ���)
	virtual bool				ProcessAttach(_In_ TTYPE* _pChild) PURE;
	//! @brief �پ� �ִ� _Object ��ü�� ����� ������ �����Ѵ�. @param _pChild '�� ���� ��ü' @return true ���� @return false ����(�Ϲ������� �پ� ���� ���� ���)
	virtual int					ProcessDetach(_In_opt_ TTYPE* _pChild) PURE;

public:
	friend bool					ATTACH<>(ICGAttachable<TTYPE>* _pParent, TTYPE* _pChild);
	friend bool					DETACH<>(ICGAttachable<TTYPE>* _pParent, TTYPE* _pChild);
};

//! @brief _pParent��ü�� _pChild�� ���δ�. @param _pAttach �� ���� ��ü @param _pChild ���� ��ü @return true ���� @return false ����(�Ϲ������� �̹� �پ� ���� ���)
template<class TOBJECT>
bool ATTACH(ICGAttachable<TOBJECT>* _pParent, TOBJECT* _pChild)
{
	return _pParent->ProcessAttach(_pChild);
}

//! @brief _pParent��ü���� _pChild�� ������. @param _pParent �� ���� ��ü @param _pChild ��� ��ü @return true ���� @return false ����(�Ϲ������� �پ� ���� ���� ���)
template<typename TOBJECT>
bool DETACH(ICGAttachable<TOBJECT>* _pParent, TOBJECT* _pChild)
{
	return _pParent->ProcessDetach(_pChild)!=0;
}
