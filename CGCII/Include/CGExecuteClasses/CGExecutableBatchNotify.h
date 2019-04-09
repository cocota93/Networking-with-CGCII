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

 @class		CBatchNotify
 @brief		���� ���� Executable ��ü�� �����ϱ� ���� Ŭ������ �Ϸ� �� Ư�� �޽����� ������ �ش�.
 @todo		
 @ref		
 @details	\n

*///-----------------------------------------------------------------------------
template <class TMESSAGE>
class CBatchNotify :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	public						NBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CBatchNotify()												{ SetObjectType(eOBJECT_TYPE::EXECUTABLE_BATCH_NOTIFY);}
	virtual ~CBatchNotify()												{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	//! @brief '�Ϸ� �� ������ �޽���'�� '�Ϸ� �� ������ ��ü'�� �����Ѵ�. @param _Msg '�Ϸ� �� �۽��� �޽���' @param _pTarget '�Ϸ� �� �޽����� ������ ��ü'
			void				SetMessage(_In_ const TMESSAGE& _Msg, _In_ ICGMessageable* _pTarget) {	SetMessage(_Msg); SetTarget(_pTarget);}
	//! @brief '�Ϸ� �� ������ �޽���'�� �����Ѵ�. @param _Msg �Ϸ� �� �۽��� �޽���
			void				SetMessage(_In_ const TMESSAGE& _Msg) {	m_Message=_Msg;}
	//! @brief ������ '�Ϸ� �� ������ �޽���'�� ��´�. @return ������ '�Ϸ� �� ������ �޽���'
			const TMESSAGE&		GetMessage() const						{	return m_Message;}
	//! @brief '�Ϸ� �� �޽����� ������ ��ü'�� �����Ѵ�. @param _pTarget '�Ϸ� �� �޽����� ������ ��ü'
			void				SetTarget(_In_ ICGMessageable* _pTarget){	m_pTarget=_pTarget;}
	//! @brief ������ '�Ϸ� �� �޽����� ������ ��ü'�� ��´�. @return '�Ϸ� �� �޽����� ������ ��ü'
			CGPTR<ICGMessageable> GetTarget() const						{	return m_pTarget;}


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteExecution() override		{	m_pTarget->RequestProcessMessage(m_Message);}

	// 2) Message
			CGPTR<ICGMessageable> m_pTarget;
			TMESSAGE			m_Message;
};


}
