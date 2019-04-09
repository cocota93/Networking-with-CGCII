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

 @class		CBatchWait
 @brief		���� ���� Executable ��ü�� �����ϱ� ���� Ŭ������ �Ϸ� �� �� ���� ���ŷ���ش�.
 @todo		
 @ref		
 @details	\n
 WaitExecuteCompletion()�� ����ϸ� ����� ��� Executable�� �Ϸ�� ������ ���ŷ���·� ����Ѵ�.
 ��� Executable ��ü�� �Ϸ�Ǹ� �׶� ���ŷ�� Ǯ���� ����ȴ�.

*///-----------------------------------------------------------------------------
class CBatchWait :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchWait();
	virtual ~CBatchWait();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) ���� �ϷḦ ��ٸ���.
	/**
	@brief	��� ������ �Ϸ�� ������ ���ŷ�Ѵ�.
	@param	_Millisecond	�ִ� ��� �ð� ( �� �ð��� ������ �Ϸ���� �ʾƵ� TIME_OUT���� ���ϵȴ�.)
	@return	true			��� ������ ����
	@return	false			��� ������ ���� (�Ϲ������� ��ü�� �ϳ��� ���� �� false�� �����Ѵ�.)
	*/
			bool				WaitExecuteCompletion(_In_ uint32_t _Millisecond=INFINITE);


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override;

	// 2) Executor
			HANDLE				m_hComplete;
};


}