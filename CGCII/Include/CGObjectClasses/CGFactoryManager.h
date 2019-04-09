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

namespace CGFactory
{

//-----------------------------------------------------------------------------
/**

 @class		Manager
 @brief		Ǯ ������
 @todo		
 @ref		ICGAllocator
 @details	\n
 Factory ��ü�� �����ϴ� Ŭ�����̴�.

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
	//! @brief �޸� ��� Ǯ�� �ı���
	virtual	bool				Destroy() override;

	//! @brief ��� Ǯ ��ü�� �ı��Ѵ�.
			void				DestroyAllFactory();
	//! @brief Ǯ ID�� Ǯ ��ü�� ã�´�. @return Ǯ ��ü ������
			CGPTR<ICGFactory>	FindFactory(_In_ int _idFactory);
	//! @brief �ش� Ǯ ��ü�� ���縦 Ȯ���Ѵ�. @return Ǯ ��ü ������
			CGPTR<ICGFactory>	FindFactory(_In_ ICGFactory* _pFactory);
	//! @brief Ǯ �̸����� Ǯ ��ü�� ã�´�. @return Ǯ ��ü ������
			CGPTR<ICGFactory>	FindFactory(_In_z_ const _CHAR* _strFactoryName);

	//! @brief ��� Ǯ�� �̸��� ��´�. @return ��� Ǯ�� �̸��� ������ ����
			CCGBuffer			GetAllFactoryName();
	//! @brief ��� Ǯ ������ ��´�. @return ��� Ǯ ������ ������ ����
			CCGBuffer			GetAllFactoryInfo();

	//! @brief Ǯ ��� ������ ��´�. @param _idFactory Ǯ�� ID @param _rFactoryInfo Ǯ������� @return true ���� @return false ����
			_Success_(return!=false) 
			bool			 	GetFactoryInfo(_In_ int _idFactory, _Out_ CGStatistics::FACTORY& _rFactoryInfo);
	//! @brief Ǯ ��� ������ ��´�. @param _strFactoryName Ǯ �̸� @param _rFactoryInfo Ǯ������� @return true ���� @return false ����
			_Success_(return!=false) 
			bool			 	GetFactoryInfo(_In_z_ const _CHAR* _strFactoryName, _Out_ CGStatistics::FACTORY& _rFactoryInfo);

	//! @brief ���� Ǯ ��ü�� ������ ��´�. @return ���� Ǯ ����
			long				GetCount() const						{	return static_cast<int>(m_listFactory.size());}
	//! @brief ��� Ǯ ��ü�� �ı��Ǿ��°�. @return true ��� �ı��Ǿ���. @return false ��� �ı����� �ʾҴ�.
			bool				IsAllReleased() const					{	return (GetCount()==0);}
	//! @brief Ǯ�� �������ݷ��Ǹ�带 �����ϴ� ��� �޸𸮷� �Ѱ�ġ�� ��´�. @return �� ������ ��뷮
			size_t				GetSustainThreshold(int _Index)			{	RETURN_IF(_Index<0 || _Index>=4, 0); return m_sizeSustainThreshhold[_Index]; }

	//! @brief �� ��ü�� ��´�.
								operator lockable&()					{	return m_listFactory;}
	//! @brief ���� Ǯ �ݺ���. @return ù��° Ǯ �ݺ���
			list<CGPTR<ICGFactory>>::iterator	begin()					{	return m_listFactory.begin();}
	//! @brief ������ Ǯ �ݺ���. @return ������ Ǯ �ݺ���
			list<CGPTR<ICGFactory>>::iterator	end()					{	return m_listFactory.end();}

	//! @brief ����ó���� �Ѵ�. @param ����ó�� ����
			void				Sustain();
			void				Sustain(_In_ eFACTORY_SUSTAIN_TYPE _Level);
			//! @brief �������ݷ����� ����ϴ��� Ȯ���Ѵ�. @return true �������ݷ��� ��� @return false �������ݷ��� ������� �ʴ´�.
			bool				IsEnableSustain() const					{	return m_bSustain;}
	//! @brief �����ݷ��� ���� ���θ� �����Ѵ�. @param _bStatus �������ݷ��� ���� ����
			void				EnableSustain(_In_ bool _bStatus=true);
	//! @brief �����ݷ����� �Ұ����ϰ� �Ѵ�.
			void				DisableSustain()						{	EnableSustain(false);}

	// 5) Initialize Instance/RunExecutor
	static	CGPTR<Manager>		GetInstance()							{	if(m_pInstance.empty()){ InitInstance();} return m_pInstance;}
	//! @brief 'Ǯ ������ �̱��� ��ü'�� �����Ѵ�. @ param _pInstance ������ 'Ǯ ������ �̱��� ��ü'
	static	void				SetInstance(_In_ Manager* _pInstance);
	//! @brief 'Ǯ ������ �̱��� ��ü'�� �����Ѵ�.
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
