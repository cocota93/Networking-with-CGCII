//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                             Server DB Classes                             *
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
// CGServerQuery::DB::CRequestorBatchLambda
//
// 1. CGServerQuery::DB::CRequestorConcurrentLambda��!
//    1) CGServerQuery::DB::CRequestorConcurrent�� ��ӹ޾� �Ϸ�� ȣ��Ǵ� ProcessCompleteQuery()
//       �Լ��� �������� Ŭ�����̴�.
//    2) Query�� �Ϸ�Ǹ� ������ Lambda�Լ��� ����ȴ�.
//       �� Lambda�Լ��� SetFunctor()�Լ��� ����Ͽ� ������ �� �ִ�.
//
//
//-----------------------------------------------------------------------------
#if defined(_MSC_VER) && (_MSC_VER>=_MSC_VER_2010)
namespace CGServerQuery
{
namespace DBSystem
{
namespace RequestorBatch
{

class CLambda : 
// ****************************************************************************
// Inherited Classes)
// ----------------------------------------------------------------------------
	public						NRequestorBatch
{
// ****************************************************************************
// Constructor/Destructor) 
// ----------------------------------------------------------------------------
public:
			CLambda()			{}
	virtual ~CLambda()			{}


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) ������ �Լ��� �����ϴ� �Լ�.
			void				SetFunctor(const TFUNCTION& p_pFunc){	m_lfFunctor=p_pFunc;}
			TFUNCTION			GetFunctor() const							{	return m_lfFunctor;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) ProcessCompleteExecution
	virtual	void				ProcessCompleteQuery()				{	m_lfFunctor();}

	// 2) Lambda function
			TFUNCTION	m_lfFunctor;
};


}
}
}
#endif