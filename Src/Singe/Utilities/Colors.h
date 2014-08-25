#pragma once

#include "..\Geometry\Vec4.h"

#define GLOBALCONST extern const __declspec(selectany)

// RGBA
namespace Colors
{
	GLOBALCONST Vec4 White = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	GLOBALCONST Vec4 Black = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

	GLOBALCONST Vec4 Red = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	GLOBALCONST Vec4 Green = Vec4(0.0f, 1.0f, 0.0f, 1.0f);
	GLOBALCONST Vec4 Blue = Vec4(0.0f, 0.0f, 1.0f, 1.0f);

	GLOBALCONST Vec4 Yellow = Vec4(1.0f, 1.0f, 0.0f, 1.0f);
	GLOBALCONST Vec4 Cyan = Vec4(0.0f, 1.0f, 1.0f, 1.0f);
	GLOBALCONST Vec4 Magenta = Vec4(1.0f, 0.0f, 1.0f, 1.0f);

	GLOBALCONST Vec4 CornflowerBlue = Vec4(0.4f, 0.6f, 0.9f, 1.0f);
}