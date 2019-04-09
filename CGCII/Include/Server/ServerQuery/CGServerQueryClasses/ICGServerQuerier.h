//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                           Server Query Classes                            *
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
//
// ICGServerQuerier
//
// 1. ICGServerQuerier��!
//    1) Query�� ���� ó���ϴ� ��ü
//    2) RequestQuery/PostRequestQuery �Լ��� ���� Query ��ü�� �޾� ó���Ѵ�.
//    3) ����� Query   : RequestQuery
//       �񵿱�� Query : PostRequestQuery
//
//-----------------------------------------------------------------------------
class ICGServerQuerier :
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	virtual public				CGServerQuery::Statistics::NQuerier,
	virtual public				ICGInitializable,
	virtual public				ICGStartable,
	virtual public				ICGObjectState,
	virtual public				ICGObjectIdentifiable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			ICGServerQuerier()		{}
	virtual ~ICGServerQuerier()		{}


// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	// 1) Query Request/Cancel(�����/�񵿱��)
	virtual	bool				CancelQuery(ICGServerQuery* _pQuery) PURE;

public:
	// 2) ...
	virtual	bool				ProcessRequestQuery(ICGServerQuery* _pQuery) PURE;
	virtual	bool				ProcessPostRequestQuery(ICGServerQueryExecutable* _pQuery) PURE;

private:
			int					m_iQuerierID;
			friend class CGServerQuery::ManagerQuerier;


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			void				RegisterQuerier()						{	CGServerQuery::ManagerQuerier::GetInstance()->Register(this);}
			void				UnregisterQuerier()						{	CGServerQuery::ManagerQuerier::GetInstance()->Unregister(this);}
};
