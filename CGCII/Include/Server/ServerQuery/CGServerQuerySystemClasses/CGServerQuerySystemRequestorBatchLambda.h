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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGServerQuery::DB::CRequestorBatchLambda
//
// 1. CGServerQuery::DB::CRequestorConcurrentLambda란!
//    1) CGServerQuery::DB::CRequestorConcurrent를 상속받아 완료시 호출되는 ProcessCompleteQuery()
//       함수만 재정의한 클래스이다.
//    2) Query가 완료되면 정해진 Lambda함수가 실행된다.
//       이 Lambda함수는 SetFunctor()함수를 사용하여 설정할 수 있다.
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
	// 1) 실행할 함수를 정의하는 함수.
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