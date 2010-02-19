#pragma once
#include "Geometry.h"

class Sphere : public IGeometry
{
public:
	Sphere(void);
	virtual ~Sphere(void) {}

private:
#ifdef USE_INTRIN
	__declspec(align(16))
#endif
	Vector4f			cnr;	// center and radius

public:
	/*-------------------------
		IGeometry	
	---------------------------*/
	virtual Aabbf		CalcAABB();

	BOOL				DoesCollide(const Sphere& other);
	void				SetPos(Vector3f pos)	{ cnr.set(pos, cnr.radius); }
	Vector3f			GetPos() const			{ return cnr.getSphereCenter(); }
	void				SetR(float r)			{ cnr.radius = r; }
	float				GetR() const			{ return cnr.radius; }
};
