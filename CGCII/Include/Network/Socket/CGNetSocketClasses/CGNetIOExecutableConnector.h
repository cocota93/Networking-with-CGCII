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
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 
//
//-----------------------------------------------------------------------------
namespace CGNet
{
namespace IO
{

class CExecutableConnectorTCP :
// ****************************************************************************
// Inherited classes) 
// ----------------------------------------------------------------------------
	virtual public				ICGExecutable,
	public						NCGPoolable<CExecutableConnectorTCP>
{
// ****************************************************************************
// Framework)
// ----------------------------------------------------------------------------
public:
	virtual	intptr_t			ProcessExecute(_In_ intptr_t _Return, _In_ size_t ) override	{	m_pConnectable->ProcessConnect(_Return); m_pConnectable.reset(); return intptr_t(0);}
			void				SetConnectable(_In_ CGNet::IO::Connector::NTCP* _pConnectable)	{ m_pConnectable = _pConnectable; }


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
public:
			CGPTR<CGNet::IO::Connector::NTCP>	m_pConnectable;
};


}
}