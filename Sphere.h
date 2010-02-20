#pragma once
#include "Geometry.h"

class Sphere : public IGeometry
{
public:
	Sphere(void);
	virtual ~Sphere(void) {}

private:
	ALIGN16 Vector4f	attr;	// center and radius

public:
	/*-------------------------
		IGeometry	
	---------------------------*/
	virtual Aabbf		CalcAABB();

	BOOL				DoesCollide(const Sphere& other);
	void				SetPos(Vector3f pos)	{ attr.set(pos, attr.radius); }
	Vector3f			GetPos() const			{ return attr.getSphereCenter(); }
	void				SetR(float r)			{ attr.radius = r; }
	float				GetR() const			{ return attr.radius; }
};
