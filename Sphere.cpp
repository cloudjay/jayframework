#include "Sphere.h"

Sphere::Sphere(void)
{
}

Sphere::~Sphere(void)
{
}

Aabbf Sphere::CalcAABB()
{
	Vector3f vecR(r, r, r);
	return Aabbf(center-vecR, center+vecR);
}

float Sphere::GetR()
{
	return r;
}

void Sphere::SetR(float _r)
{
	r = _r;
}
