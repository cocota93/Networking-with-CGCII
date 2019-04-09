//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Utility Classes                              *
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
// CGEDC::CMD5
//
// 1. CGEDC::CMD5��!
//    1) MD5(Message Diegest 5)�� ��� Ŭ�����̴�.
//    2) 
//    3) 
//
// 2. �����
//    1) ���� Initialize()�Լ��� ȣ���Ͽ� �ʱ�ȭ�Ѵ�.
//    2) PushMD5()�Լ��� ȣ���Ͽ� �����͵��� ������Ų��.
//       PushMD5�� File�� MD5�� ���� ���� �ִ�.
//    3) ��� �����͸� ������Ų �� PAdding()�Լ��� ȣ���Ͽ� �������Ѵ�.
//    4) ����� MD5�� GetMD5()�Լ��� ����Ͽ� ��´�. 
//    5) ������ MD5�� ���� ���� �� ������ �ʿ� ���� CalculateMD5()�Լ��� ȣ���ϸ�
//       �ȴ�.
//
//-----------------------------------------------------------------------------
typedef struct MD5
{
	uint32_t data[4];

public:
	bool	operator>(const MD5& p_RHS) const
			{
				for(int i=0; i<4; i++)
				{
					RETURN_IF(data[i] > p_RHS.data[i], true);
					RETURN_IF(data[i] < p_RHS.data[i], false);
				}
				return	false;
			}

	bool	operator<(const MD5& p_RHS) const
			{
				for(int i=0; i<4; i++)
				{
					RETURN_IF(data[i] < p_RHS.data[i], true);
					RETURN_IF(data[i] > p_RHS.data[i], false);
				}
				return	false;
			}

	int		CompareMD5(const MD5& b) const
			{
				for(int i=0; i<4; i++)
				{
					RETURN_IF(data[i] > b.data[i], 1);
					RETURN_IF(data[i] < b.data[i], -1);
				}

				return	0;
			}
public:
	MD5()	{}
	MD5(uint32_t p_dwA, uint32_t p_dwB, uint32_t p_dwC, uint32_t p_dwD)	{	data[0]=p_dwA; data[1]=p_dwB; data[2]=p_dwC; data[3]=p_dwD;}
} *LPMD5;



namespace CGEDC
{

class CMD5
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CMD5();
	virtual ~CMD5();


// ****************************************************************************
// Public)
// ----------------------------------------------------------------------------
public:
	// 1) �⺻�� MD5 ����...
	//    - Initialize() -> PushMD5() -> PAdding() �� ������ ��ġ�� MD5���� ���ȴ�.
			bool				Initialize();
			void				PushMD5(_In_reads_bytes_(s_size) const void* s_buffer, uint32_t s_size);
			bool				PushMD5(HANDLE _hFile, uint32_t p_dwStart, uint32_t p_dwEnd);
			void				PAdding();

	// 2) File�� �̿��ؼ� �Ѳ����� �Ϸð����� ó���Ѵ�.
			bool				CalculateMD5(_In_z_ const _CHAR* _strFileName);
			bool				CalculateMD5(_In_z_ const _CHAR_SUB* _strFileName);

	// 3) MD5�� ���(MD5�� 16Byte�̹Ƿ� �̰��� �����ؾ� �Ѵ�.)
			void				GetMD5(LPMD5 p_MD5) const				{	*p_MD5=m_dwState;}
			const MD5&			GetMD5() const							{	return m_dwState;}
			void				SetMD5(const MD5& p_rMD5)				{	m_dwState=p_rMD5;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			// 1) MD5�� �����ϰ� �ִ� ����.
			uint8_t				m_Buffer[64];

			// 2) A, B, C, D��
			bool				m_bProcess;
			MD5					m_dwState;

			// 3) Data�� ũ�⸦ Bit������ �����ϰ� �ִ� ����.
			uint32_t			m_dwCount[2];

protected:
			// 1) MD5�� Block������ ����ϴ� �Լ�.
			void				TransformMD5(void* s_buffer, const void* s_from);
};


}