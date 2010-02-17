#pragma once
#include "Physic.h"

class IGeometry
{
public:
	virtual Aabbf		CalcAABB() = 0;
};
