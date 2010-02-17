#pragma once
#include "Geometry.h"

class Sphere : public IGeometry
{
public:
	Sphere(void);
	virtual ~Sphere(void);

	/*-------------------------
		IGeometry	
	---------------------------*/
	virtual Aabbf		CalcAABB();

	void				SetR(float r);
	float				GetR();

private:
	Vector3f			center;
	float				r;
};
