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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
/**

 @class		CGPTR
 @brief		자동 참조 계수(ARC, Auto Reference Counting) 클래스이다.
 @todo		
 @ref		CGOBJ, ICGReferenceable
 @details	\n
 참조계수를 가진 객체(ICGReferenceable를 상속받은 객체)의 참조계수를 자동적으로 증감시켜주는 클래스이다.
 참조계수를 가진 객체의 포인터가 설정될 때 AddRef()함수를 호출해 참조계수를 증가시켜준다.
 또 설정이 해제될 때 Release()함수를 호출해 참조계수를 감소 시켜준다.
 대입, 복사생성 등등 일반적인 조작에 의해 참조가 추가되거나 감소될 때 자동적으로 참조계수가 계산되도록 설계되었다.

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
