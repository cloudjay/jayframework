#include "Sphere.h"

Sphere::Sphere(void)
{
	attr = Vector4f::ZERO;
}

Aabbf Sphere::CalcAABB()
{
#ifdef USE_INTRIN
	__declspec(align(16)) Vector4f vecMin, vecMax;
	__m128 vecR = _mm_set1_ps(attr.radius);						// vecR = { r, r, r, r }
	__m128 vecC = _mm_load_ps((float*)attr.xyzw);				// vecC = { x, y, z, r }
	_mm_store_ps((float*)vecMin.xyzw, _mm_sub_ps(vecC, vecR));	// vecMin = vecC - vecR
	_mm_store_ps((float*)vecMax.xyzw, _mm_add_ps(vecC, vecR));	// vecMax = vecC + vecR
	return Aabbf(vecMin.getSphereCenter(), vecMax.getSphereCenter());
#else
	return Aabbf(attr);
#endif
}

#ifdef UNITTEST
TEST(SphereCalcAABB)
{
	Sphere s1;
	s1.SetPos(Vector3f(1.f, 1.f, 1.f));
	s1.SetR(1.f);
	Aabbf aabb = s1.CalcAABB();
	Vector3f min = aabb.getMin();
	Vector3f max = aabb.getMax();
	CHECK_EQUAL(0.f, min.x);
	CHECK_EQUAL(0.f, min.y);
	CHECK_EQUAL(0.f, min.z);
	CHECK_EQUAL(2.f, max.x);
	CHECK_EQUAL(2.f, max.y);
	CHECK_EQUAL(2.f, max.z);
}
#endif

/// http://download.intel.com/technology/itj/2008/v12i3/paper2.pdf
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
		s	= _mm_load_ps((float*)attr.xyzw);		// s = (x, y, z, r)
		s	= _mm_xor_ps(s, _mask128);				// s = (x, y, z, -r)
		s1	= _mm_load_ps((float*)other.attr.xyzw);	// s1 = (x1, y1, z1, r1)
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
TEST(SphereDoesCollide)
{
	Sphere s1, s2;
	s1.SetPos(Vector3f(0.f, 0.f, 0.f));
	s1.SetR(1.f);
	s2.SetPos(Vector3f(1.f, 1.f, 1.f));
	s2.SetR(1.f);
	CHECK(s1.DoesCollide(s2));
}
#endif
