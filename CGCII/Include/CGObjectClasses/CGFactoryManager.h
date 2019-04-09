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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		Manager
 @brief		풀 관리자
 @todo		
 @ref		ICGAllocator
 @details	\n
 Factory 객체를 관리하는 클래스이다.

*/
//-----------------------------------------------------------------------------
class Manager :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CGNameable::NString,
	public						NCGDispatchable,
	virtual public				ICGDestroyable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
protected:
			Manager();
	virtual	~Manager();


// ****************************************************************************
// Publics)
// ----------------------------------------------------------------------------
public:
	//! @brief 메모리 블록 풀을 파괴함
	virtual	bool				Destroy() override;

	//! @brief 모든 풀 객체를 파괴한다.
			void				DestroyAllFactory();
	//! @brief 풀 ID로 풀 객체를 찾는다. @return 풀 객체 포인터
			CGPTR<ICGFactory>	FindFactory(_In_ int _idFactory);
	//! @brief 해당 풀 객체의 존재를 확인한다. @return 풀 객체 포인터
			CGPTR<ICGFactory>	FindFactory(_In_ ICGFactory* _pFactory);
	//! @brief 풀 이름으로 풀 객체를 찾는다. @return 풀 객체 포인터
			CGPTR<ICGFactory>	FindFactory(_In_z_ const _CHAR* _strFactoryName);

	//! @brief 모든 풀의 이름을 얻는다. @return 모든 풀의 이름을 저장한 버퍼
			CCGBuffer			GetAllFactoryName();
	//! @brief 모든 풀 정보를 얻는다. @return 모든 풀 정보를 저장한 버퍼
			CCGBuffer			GetAllFactoryInfo();

	//! @brief 풀 통계 정보를 얻는다. @param _idFactory 풀의 ID @param _rFactoryInfo 풀통계정보 @return true 성공 @return false 실패
			_Success_(return!=false) 
			bool			 	GetFactoryInfo(_In_ int _idFactory, _Out_ CGStatistics::FACTORY& _rFactoryInfo);
	//! @brief 풀 통계 정보를 얻는다. @param _strFactoryName 풀 이름 @param _rFactoryInfo 풀통계정보 @return true 성공 @return false 실패
			_Success_(return!=false) 
			bool			 	GetFactoryInfo(_In_z_ const _CHAR* _strFactoryName, _Out_ CGStatistics::FACTORY& _rFactoryInfo);

	//! @brief 현재 풀 객체의 갯수를 얻는다. @return 현재 풀 갯수
			long				GetCount() const						{	return static_cast<int>(m_listFactory.size());}
	//! @brief 모든 풀 객체가 파괴되었는가. @return true 모두 파괴되었다. @return false 모두 파괴되지 않았다.
			bool				IsAllReleased() const					{	return (GetCount()==0);}
	//! @brief 풀의 가비지콜렉션모드를 결정하는 사용 메모리량 한계치를 얻는다. @return 각 레벨별 사용량
			size_t				GetSustainThreshold(int _Index)			{	RETURN_IF(_Index<0 || _Index>=4, 0); return m_sizeSustainThreshhold[_Index]; }

	//! @brief 락 객체를 얻는다.
								operator lockable&()					{	return m_listFactory;}
	//! @brief 최초 풀 반복자. @return 첫번째 풀 반복자
			list<CGPTR<ICGFactory>>::iterator	begin()					{	return m_listFactory.begin();}
	//! @brief 마지막 풀 반복자. @return 마지막 풀 반복자
			list<CGPTR<ICGFactory>>::iterator	end()					{	return m_listFactory.end();}

	//! @brief 유지처리를 한다. @param 유지처리 레벨
			void				Sustain();
			void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level);
			//! @brief 가비지콜렉션을 사용하는지 확인한다. @return true 가비지콜렉션 사용 @return false 가비지콜렉션 사용하지 않는다.
			bool				IsEnableSustain() const					{	return m_bSustain;}
	//! @brief 가비콜렉션 가능 여부를 설정한다. @param _bStatus 가비지콜렉션 동작 여부
			void				EnableSustain(_In_ bool _bStatus=true);
	//! @brief 가비콜렉션을 불가능하게 한다.
			void				DisableSustain()						{	EnableSustain(false);}

	// 5) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief '풀 관리자 싱글턴 객체'를 설정한다. @ param _pInstance 설정할 '풀 관리자 싱글턴 객체'
	static	void				SetInstance(_In_ Manager* _pInstance);
	//! @brief '풀 관리자 싱글턴 객체'를 리셋한다.
	static	void				ResetInstance();


// ****************************************************************************
// Implementations)
// ----------------------------------------------------------------------------
private:
	// 1) Factory List.
			LOCKABLE<list<ICGFactory*>>			m_listRegistered;
			LOCKABLE<list<CGPTR<ICGFactory>>>	m_listFactory;
			int					m_iFactorySerial;
			size_t				m_sizeSustainThreshhold[4];

	// 2) Garbage Collection
			bool				m_bSustain;

	// 3) Factory Register/UnRegister
			bool				RegisterFactory(ICGFactory* _pFactory);
			bool				UnregisterFactory(ICGFactory* _pFactory);

	// 4) Instance
	static	CGOWN<Manager>		m_pInstance;
	static	LOCKABLE<>			m_csCreate;
	static	void				InitInstance();

	// Friend)
	friend	ICGFactory;
};


}
