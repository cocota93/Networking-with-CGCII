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
//-----------------------------------------------------------------------------
/**

 @class		Manager
 @brief		���� �������̴�.
 @todo		
 @ref		
 @details	\n
 Access Violation�� ���� SEH�� ���� �߻��ϴ� Exception�� �����ϴ� �Ŵ����̴�.
 �Ϲ������� ���ܰ� �߻����� �� ������ ����� ������ �����Ѵ�.
 ���������� ���� �ּҿ��� �߻��ϴ� ���ܿ� ���ؼ��� �ߺ������� Dump�� ������ �ʴ´�.
 SetDumpCountLimit()�� ����� ����� �ִ��� Dump���� ������ �� �ִ�.
 (�⺻���� DEFAULT_MAX_EXCEPTIONLIMIT:4096��)
 SetDumpType()�� ����Ͽ� ����� Dump�� ������ ������ �� �ִ�.
 (�⺻���� DEFAULT_MINIDUMP_TYPE:MINIDUMP_TYPE_MINI)

*///-----------------------------------------------------------------------------
namespace CGExecutor
{

class Manager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,					// (@) Nameable
	public						NCGDispatchable,
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Definitions)
// ----------------------------------------------------------------------------
public:
		typedef	circular_list<ICGExecutor*>::iterator	ITERATOR;


// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
protected:
			Manager();
	virtual ~Manager();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	// 1) Iterator��.
	//! @brief �� ��ü�� ��´�.
								operator lockable&()					{	return m_listExcutor;}
	//! @brief ���� ���� �ݺ���. @return ù��° ���� �ݺ���
			ITERATOR			begin()									{	return m_listExcutor.begin();}
	//! @brief ������ ���� �ݺ���. @return ������ ���� �ݺ���
			ITERATOR			end()									{	return m_listExcutor.end();}
	//! @brief Executor�� ����
			size_t				size()									{	return m_listExcutor.size();}


	// 2) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '���� ������ �̱��� ��ü'�� �����Ѵ�. @ param _pInstance ������ '���� ������ �̱��� ��ü'
	static	void				SetInstance(Manager* _pInstance);
	//! @brief '���� ������ �̱��� ��ü'�� �����Ѵ�.
	static	void				ResetInstance();


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
private:
	//! @brief ������ ��ü�� ����Ѵ�. @return true ���� @return false ����
			bool				RegisterExecutor(_In_ ICGExecutor* _pExecutor);
	//! @brief ������ ��ü�� ��������Ѵ�. @return true ���� @return false ����
			bool				UnregisterExecutor(_In_ ICGExecutor* _pExecutor);

	//! @brief �����尡 ��ϵ� �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnRegister()						{}
	//! @brief �����尡 ��������� �� ȣ��Ǵ� �Լ�
	virtual	void				ProcessOnUnregister()					{}
protected:
	// 1) Executor ����
			LOCKABLE<circular_list<ICGExecutor*>> m_listExcutor;

	// 2) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

public:
	// 3) Destroy
	virtual	bool				Destroy() override;
};


}

