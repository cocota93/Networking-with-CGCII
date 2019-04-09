//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                                  Common                                   *
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
/**

 @class		CGPTR
 @brief		�ڵ� ���� ���(ARC, Auto Reference Counting) Ŭ�����̴�.
 @todo		
 @ref		CGOBJ, ICGReferenceable
 @details	\n
 ��������� ���� ��ü(ICGReferenceable�� ��ӹ��� ��ü)�� ��������� �ڵ������� ���������ִ� Ŭ�����̴�.
 ��������� ���� ��ü�� �����Ͱ� ������ �� AddRef()�Լ��� ȣ���� ��������� ���������ش�.
 �� ������ ������ �� Release()�Լ��� ȣ���� ��������� ���� �����ش�.
 ����, ������� ��� �Ϲ����� ���ۿ� ���� ������ �߰��ǰų� ���ҵ� �� �ڵ������� ��������� ���ǵ��� ����Ǿ���.

*/
//-----------------------------------------------------------------------------
namespace CGDK
{

//----------------------------------------------------------------------------
// CGDK
//----------------------------------------------------------------------------
enum class eCOMPILER
{
	VISUALSTUDIO_VS2005	 = 0,
	VISUALSTUDIO_VS2008	 = 1,
	VISUALSTUDIO_VS2010	 = 2,
	VISUALSTUDIO_VS2012	 = 3,
	VISUALSTUDIO_VS2013	 = 4,
	VISUALSTUDIO_VS2015	 = 5,
	ECLIPS				 = 6,
	MAX
};

enum class eCONFIGURATION
{
	DEBUG_				 = 0,
	DEBUG_DLL_			 = 1,
	RELEASE_			 = 2,
	RELEASE_DLL_		 = 3,
	MAX
};

enum class ePLATFORM
{
	WINDOWS_X86			 = 0,
	WINDOWS_X64			 = 1,
	LINUX				 = 2,
	MAX
};

enum class eLICENSE_TYPE
{
	FREE				 = 0,
	INDIE				 = 1,
	LIMITED_PROJECT		 = 2,
	LIMITED_COMPPANY	 = 3,
	UNLIMITED			 = 4,
	DEVELOPER			 = 5,
	MAX
};

class COMPONENT
{
public:
	// 1) Name
	_STRING						Name;

	// 2) Version
	int							VersionPackage;
	int							VersionSub;
	int							versionBuild;
	TIME::SYSTEM::time_point	timeBuild;

	// 3) Revision/Compiler/Configuration
	int							Revision;
	eCOMPILER					Compiler;
	ePLATFORM					Platform;
	eCONFIGURATION				Configuration;

	// 4) License
	eLICENSE_TYPE				LicenseType;
	_STRING						LicenseCompany;
	_STRING						LicenseProject;
	TIME::SYSTEM::time_point	LicenseExpire;

	DWORD						CRC;
};


//----------------------------------------------------------------------------
// CGDK functions
//----------------------------------------------------------------------------
int								GetVersion();
const std::vector<COMPONENT>&	GetComponentInfo();

const _CHAR*					GetString_Compiler(eCOMPILER _Compiler);
const _CHAR*					GetString_Configuration(eCONFIGURATION _Configuration);
const _CHAR*					GetString_Platform(ePLATFORM _Platform);
const _CHAR*					GetString_LicenseType(eLICENSE_TYPE _LicenseType);
const _CHAR*					GetString_License();

}
