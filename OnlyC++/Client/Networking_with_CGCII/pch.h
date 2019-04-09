
#pragma once
//----------------------------------------------------------------------------
// Definitions
//----------------------------------------------------------------------------
// 1) For gcc
#undef __STRICT_ANSI__


// 3) 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다(WIN32용)
#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

// 4) Standard Libraries
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
