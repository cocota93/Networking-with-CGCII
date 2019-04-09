// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#if _MSC_VER>=1700
#include "CppUnitTest.h"
#endif


#include <../../Include/CGObjectClasses.h>

#include <CGDbuffer>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>

#if _MSC_VER>=1700
	#include <unordered_map>
	#include <unordered_set>
#endif

#include "CGDBuffers_UnitTest_Functional_Definitions.h"
