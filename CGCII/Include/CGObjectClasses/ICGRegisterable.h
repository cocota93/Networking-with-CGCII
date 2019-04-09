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

template<typename TTYPE> class ICGRegisterable;
template<typename TOBJECT> bool REGISTER(ICGRegisterable<TOBJECT>* _pAttach, TOBJECT* _Object);
template<typename TOBJECT> bool UNREGISTER(ICGRegisterable<TOBJECT>* _pAttach, TOBJECT* _Object);

//-----------------------------------------------------------------------------
/**

 @class		ICGRegisterable
 @brief		��� ���� �Ӽ��� �������̽� Ŭ����
 @todo		
 @ref		
 @details	\n
 TTYPE�� ��ü�� ����ϰų� ��� �����ϴ� �Ӽ��� ���� �������̽� Ŭ�����̴�.
 ProcessRegister(...)�Լ��� ��ü�� ����ϰ� ProcessUnregister(...)�� ��ϵ� ��ü�� �����ϴ� �������̽��� ������.

*/
//-----------------------------------------------------------------------------
template <typename TTYPE>
class ICGRegisterable : 
	// ****************************************************************************
	// Inherited Classes) 
	// ----------------------------------------------------------------------------
	virtual public				ICGReferenceable
{
	// ****************************************************************************
	// Protected)
	// ----------------------------------------------------------------------------
public:
	//! @brief '��� ��ü'�� ����Ѵ�. @param _Object ����� '��� ��ü' @return true ���� @return false ����(�Ϲ������� �̹� ��ϵ� ��ü �� ���)
	virtual bool				ProcessRegister(TTYPE* _Object) PURE;
	//! @brief ��ϵ� '��� ��ü'�� �����Ѵ�. @param _Object ������ '��� ��ü' @return true ���� @return false ����(�Ϲ������� ��ϵǾ� ���� ���� ��ü�� ���)
	virtual bool				ProcessUnregister(TTYPE* _Object) PURE;

public:
	//! @brief _Registerable ��ü�� _Object ��ü�� ����Ѵ�. @param _pRegisterable �ǵ�� ��ü @param _Object ����� ��ü @return true ���� @return false ����(�Ϲ������� �̹� ��ϵ� ��ü �� ���)
	friend bool					REGISTER<>(ICGRegisterable<TTYPE>* _pRegisterable, TTYPE* _Object);
	//! @brief _Registerable ��ü���� _Object ��ü�� ��� �����Ѵ�. @param _pRegisterable �ǵ������ ��ü @param _Object ��������� ��ü @return true ���� @return false ����(�Ϲ������� ��ϵǾ� ���� ���� ��ü�� ���)
	friend bool					UNREGISTER<>(ICGRegisterable<TTYPE>* _pRegisterable, TTYPE* _Object);
};

template<class TOBJECT>
bool REGISTER(ICGAttachable<TOBJECT>* _pAttach, TOBJECT* _Object)
{
	return _pAttach->ProcessRegister(_Object);
}

template<typename TOBJECT>
bool UNREGISTER(ICGAttachable<TOBJECT>* _pAttach, TOBJECT* _Object)
{
	return _pAttach->ProcessUnregister(_Object);
}
