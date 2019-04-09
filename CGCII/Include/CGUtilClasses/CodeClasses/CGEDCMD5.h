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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGEDC::CMD5
//
// 1. CGEDC::CMD5란!
//    1) MD5(Message Diegest 5)를 얻는 클래스이다.
//    2) 
//    3) 
//
// 2. 사용방법
//    1) 먼저 Initialize()함수를 호출하여 초기화한다.
//    2) PushMD5()함수를 호출하여 데이터들을 누적시킨다.
//       PushMD5로 File의 MD5를 얻을 수도 있다.
//    3) 모든 데이터를 누적시킨 후 PAdding()함수를 호출하여 마무리한다.
//    4) 얻어진 MD5를 GetMD5()함수를 사용하여 얻는다. 
//    5) 파일의 MD5를 구할 때는 이 과정들 필요 없이 CalculateMD5()함수를 호출하면
//       된다.
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
	// 1) 기본적 MD5 순서...
	//    - Initialize() -> PushMD5() -> PAdding() 의 과정을 거치면 MD5값이 계산된다.
			bool				Initialize();
			void				PushMD5(_In_reads_bytes_(s_size) const void* s_buffer, uint32_t s_size);
			bool				PushMD5(HANDLE _hFile, uint32_t p_dwStart, uint32_t p_dwEnd);
			void				PAdding();

	// 2) File을 이용해서 한꺼번에 일련과정을 처리한다.
			bool				CalculateMD5(_In_z_ const _CHAR* _strFileName);
			bool				CalculateMD5(_In_z_ const _CHAR_SUB* _strFileName);

	// 3) MD5값 얻기(MD5는 16Byte이므로 이것을 감안해야 한다.)
			void				GetMD5(LPMD5 p_MD5) const				{	*p_MD5=m_dwState;}
			const MD5&			GetMD5() const							{	return m_dwState;}
			void				SetMD5(const MD5& p_rMD5)				{	m_dwState=p_rMD5;}


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
			// 1) MD5를 보관하고 있는 변수.
			uint8_t				m_Buffer[64];

			// 2) A, B, C, D값
			bool				m_bProcess;
			MD5					m_dwState;

			// 3) Data의 크기를 Bit단위로 보관하고 있는 변수.
			uint32_t			m_dwCount[2];

protected:
			// 1) MD5를 Block단위로 계산하는 함수.
			void				TransformMD5(void* s_buffer, const void* s_from);
};


}