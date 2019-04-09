//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                          Network Socket Classes                           *
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
/*!
* @class IReceivable
*
* @ingroup CGNetIO
*
* @brief 저수준 I/O를 통해 데이터수신 처리를 정의하는 클래스
*
*   저수준 I/O장치를 통해 데이터 수신처리를 정의하는 클래스로 데이터를 받아 IPacketable로
*   전달하는 클래스이다.
*   저수준 I/O 장치나 API 혹은 처리 방법에 따라 달라질수 있다.
*
*/
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class IReceivable
{
// ****************************************************************************
// Frameworks)
// ----------------------------------------------------------------------------
public:
	// 1) Reset할때 호출하는 함수.(기본은 빈것...)
	virtual	void				ResetReceivable() PURE;

	// 2) Receive를 Prepare하는 함수이다.(이 함수 이후에 Receive가 가능해진다.)
	//    (만약 처리중 잘못되는 경우 throw를 할수도 있다.)
	virtual	bool				PrepareReceive() PURE;
};


}
}