#pragma once
#include "Physic.h"

class PointMass
{
public:
	PointMass(void);
	PointMass(const Vector4f _attr);
	virtual ~PointMass(void) {}

private:
	ALIGN16 Vector4f	attr; // 3D position and mass
	ALIGN16 Vector4f	attrOld;

public:
	Vector3f			GetPos() const			{ return attr.getSphereCenter(); }
	float				GetMass() const			{ return attr.radius; }
	void				Verlet(float dt, const Vector3f& a);
};
