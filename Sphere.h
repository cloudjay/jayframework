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

	void				SetPos(Vector3f pos);
	Vector3f			GetPos() const;
	void				SetR(float r)			{ cnr.radius = r; }
	float				GetR() const			{ return cnr.radius; }
#ifdef USE_INTRIN
	__declspec(align(16))
#endif
	Vector4f			cnr;	// center and radius

	BOOL				DoesCollide(const Sphere& other);

};
