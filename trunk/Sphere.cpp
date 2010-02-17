#include "Sphere.h"

Sphere::Sphere(void)
{
}

Sphere::~Sphere(void)
{
}

Aabbf Sphere::CalcAABB()
{
	float r = cnr.radius;
	Vector3f vecR(r, r, r);
	Vector3f center(cnr.center.x, cnr.center.y, cnr.center.z);
	return Aabbf(center-vecR, center+vecR);
}

void Sphere::SetPos(Vector3f pos)
{
	cnr.center.x = pos.x;
	cnr.center.y = pos.y;
	cnr.center.z = pos.z;
}

Vector3f Sphere::GetPos() const
{
	return Vector3f(cnr.center.x, cnr.center.y, cnr.center.z);
}

BOOL Sphere::DoesCollide(const Sphere &other)
{
#ifdef USE_INTRIN
	// SSE4.1 uses _mm_dp_ps
	bool bSSE41; {
		int CPUInfo[4];
		__cpuid(CPUInfo, 1);
		bSSE41 = (CPUInfo[2] & 0x80000) || false;
	}

	if (bSSE41)
	{
		__declspec(align(16)) static long _mask[4] = {0,0,0,0x80000000};
		__m128 _mask128 = *(__m128*)_mask;
		__m128 s, s1, s2;
		s	= _mm_load_ps((float*)cnr.xyzw);		// s = (x, y, z, r)
		s	= _mm_xor_ps(s, _mask128);				// s = (x, y, z, -r)
		s1	= _mm_load_ps((float*)other.cnr.xyzw);	// s1 = (x1, y1, z1, r1)
		s1	= _mm_sub_ps(s1, s);					// s1 = (x1-x, y1-y, z1-z, r1+r)
		s2	= _mm_xor_ps(s1, _mask128);				// s2 = (x1-x, y1-y, z1-z, -(r1+r))
		s1	= _mm_dp_ps(s1,s2,0xff);				// s1 = distSq-rSq
		//get sign bit of subtraction
		int res	= _mm_extract_ps(s1,0);
		res >>= 31;	res &= 0x01;
		return res;
	}
#endif
	const float totalR = GetR()+other.GetR();
	return (GetPos().distanceSquared(other.GetPos()) < totalR*totalR);
}

#ifdef UNITTEST
TEST(Sphere)
{
	Sphere s1, s2;
	s1.SetPos(Vector3f(0.f, 0.f, 0.f));
	s1.SetR(1.f);
	s2.SetPos(Vector3f(1.f, 1.f, 1.f));
	s2.SetR(1.f);
	CHECK(s1.DoesCollide(s2));
}
#endif
