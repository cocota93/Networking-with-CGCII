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

 @class		ICGNameable
 @brief		�̸��� ������ �Ӽ� �������̽� Ŭ����
 @todo		
 @ref		ICGOpenable, ICGCloseable, ICGDestroyable
 @details	\n
 ��ü�� �̸��� �����ϰų� ������ �̸��� ��� �Ӽ��� �������� �� �������̽� Ŭ������ ��ӹ޴´�.
 SetName(...)�Լ��� �̸��� �����ϴ� �Լ��̸�
 GetName()�� ������ �̸��� ��� �Լ��̴�.

*/
//-----------------------------------------------------------------------------
#define	MAX_NAME_LENGTH		256

class ICGNameable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
	virtual	~ICGNameable()		{}

// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	//! @brief '�� �̸�'�� �����Ѱ��� Ȯ���ϴ� ó���� �����Ѵ�. @param _strCompare '�� �̸�' @return true ���� @return false �ٸ�
	virtual	bool				ProcessIsThis(_In_z_ const _CHAR* /*_strCompare*/) const PURE;
	//! @brief '��ü �̸�'�� ��� ������ �����Ѵ�. @return true '��ü �̸�' ������
	virtual	const _CHAR*		ProcessGetName() const PURE;
	//! @brief '��ü �̸�'�� �����ϴ� ������ �����Ѵ�. @param  _strName ������ '��ü �̸�'
	virtual	void				ProcessSetName(_In_z_ const _CHAR* /*_strName*/) PURE;

public:
	//! @brief '��ü �̸�'�� �����Ѵ�. @param _strName '��ü�̸�'
			void				SetName(_In_z_ const _CHAR* _strName)			{	ProcessSetName(_strName);}
	//! @brief '��ü �̸�'�� �����Ѵ�. @param _strName '��ü�̸�'
			void				SetName(_In_z_ const _CHAR_SUB* _strName)		{	_CHAR strBuffer[1024]; ProcessSetName(CONVERT_STRING(_strName, strBuffer));}

	//! @brief '�� �̸�'�� �����Ѱ� Ȯ���Ѵ�. @param _strCompare '�� �̸�' @return true ���� @return false �ٸ�
			bool				IsThis(_In_z_ const _CHAR* _strCompare) const	{	return ProcessIsThis(_strCompare);}
	//! @brief '�� �̸�'�� �����Ѱ� Ȯ���Ѵ�. @param _strCompare '�� �̸�' @return true ���� @return false �ٸ�
			bool				IsThis(_In_z_ const _CHAR_SUB* _strCompare) const{	_CHAR strBuffer[1024]; return ProcessIsThis(CONVERT_STRING(_strCompare, strBuffer));}

	//! @brief '��ü �̸�'�� ��´�. @return '��ü �̸�' ������
			const _CHAR*		GetName() const									{	return ProcessGetName();}
	//! @brief '��ü �̸�'�� ��´�. @param _strName '��ü �̸�'�� �޾ƿ� ������ @return '��ü�̸�'�� �޾ƿ� ������
			_CHAR*				GetName(_Inout_z_ _CHAR* _strName) const			{	RETURN_IF(_strName==nullptr, nullptr); CGSTRCPY_S(_strName, MAX_NAME_LENGTH, ProcessGetName()); return _strName;}
	//! @brief '��ü �̸�'�� ��´�. @param _strName '��ü �̸�'�� �޾ƿ� ������ @return '��ü�̸�'�� �޾ƿ� ������
			_CHAR_SUB*			GetName(_Inout_z_ _CHAR_SUB* _strName) const		{	RETURN_IF(_strName==nullptr, nullptr); return CONVERT_STRING(ProcessGetName(), _strName);}

};

template <class TOBJECT>
const _CHAR* GET_NAME(_In_ TOBJECT* object)
{	
	ICGNameable* p=dynamic_cast<ICGNameable*>(object);
	return (p!=nullptr) ? p->GetName() : _CGTEXT("");
}
