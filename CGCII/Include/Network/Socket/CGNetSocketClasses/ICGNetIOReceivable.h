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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
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
* @brief ������ I/O�� ���� �����ͼ��� ó���� �����ϴ� Ŭ����
*
*   ������ I/O��ġ�� ���� ������ ����ó���� �����ϴ� Ŭ������ �����͸� �޾� IPacketable��
*   �����ϴ� Ŭ�����̴�.
*   ������ I/O ��ġ�� API Ȥ�� ó�� ����� ���� �޶����� �ִ�.
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
	// 1) Reset�Ҷ� ȣ���ϴ� �Լ�.(�⺻�� ���...)
	virtual	void				ResetReceivable() PURE;

	// 2) Receive�� Prepare�ϴ� �Լ��̴�.(�� �Լ� ���Ŀ� Receive�� ����������.)
	//    (���� ó���� �߸��Ǵ� ��� throw�� �Ҽ��� �ִ�.)
	virtual	bool				PrepareReceive() PURE;
};


}
}