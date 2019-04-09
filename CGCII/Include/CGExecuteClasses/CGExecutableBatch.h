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

 @class		NBatch
 @brief		�Ѳ����� ���� ���� Executable ��ü�� ť���� �ɾ��ִ� Executable�̴�. 
 @todo		
 @ref		CList<TEXECUTABLE>
 @details	\n
 ���� ���� Executable ��ü�� ť���� �������ش�. 
 ���� ������ �ɾ��ְ� �Ǹ� ť�׵� Executable ��ü���� ���ŵȴ�.

*///-----------------------------------------------------------------------------
class NBatch :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			NBatch();
	virtual ~NBatch();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//!	@brief	���� ��ü���� ť���Ѵ�. @param _pExecutable ť���� '���� ��ü' @param _Param ���� �� ������ ����
			void				QueueExecutable(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param=0);
	//!	@brief	ť�׵� ��� ��ü���� �����Ѵ�.
			void				Clear();

	//! @brief	������ ��û�Ѵ�. �̶� ���� ť�׵� ��� '���� ��ü'�� �����Ѵ�. @param _pExecutor ������ ��û�� '������' @return true ���� @return false ���� 
			bool				RequestExecute(_In_ ICGExecutor* _pExecutor);

	//! @brief ���� ������ �������� '���� ��ü'�� ���� ��´�.	@return ���� ���� ���� '���� ��ü'�� ��
			size_t				GetExecutingCount() const;

	//! @brief ���� ��ü�� ť���� �Ѵ�. @param rhs ť���� '���� ��ü'
			NBatch&				operator<<(ICGExecutable* rhs)			{	QueueExecutable(rhs); return *this;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	//!	@brief �ϰ�ó���� �Ϸ�Ǿ��� �� ó���� ������ �����Ѵ�.
	virtual	void				ProcessCompleteExecution() PURE;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// Declare) 
	struct QUEUE_EXECUTABLE
	{
		CGPTR<ICGExecutable>	pExecutable;
		size_t					dwParam;

		QUEUE_EXECUTABLE()												{}
		QUEUE_EXECUTABLE(_In_ ICGExecutable* _pExecutable, _In_ size_t _Param) : pExecutable(_pExecutable), dwParam(_Param) {}
	};

	// 2) Executable List
			LOCKABLE<circular_list<QUEUE_EXECUTABLE>> m_listExecutable;

	// 3) ������ ó���Ѵ�.
	virtual intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t _Param) override;
};


}
