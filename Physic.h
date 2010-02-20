#pragma once

#include "JayFramework.h"

#include <vmmlib/vmmlib.h>
#include <vmmlib/axisAlignedBoundingBox.h>

#if _MSC_VER > 1400
#include <intrin.h>
#define USE_INTRIN
#endif

#ifdef USE_INTRIN
#define ALIGN16	__declspec(align(16))
#else
#define ALIGN16	
#endif


using namespace vmml;
