#include "PointMass.h"


PointMass::PointMass(void)
{
}

PointMass::PointMass(const Vector4f _attr)
: attr(_attr), attrOld(_attr)
{
}

void PointMass::Verlet(float dt, const Vector3f& a)
{	// x += x-oldx+a*fTimeStep*fTimeStep;
#ifdef USE_INTRIN
	__declspec(align(16)) static long _mask[4] = {-1,-1,-1,0};
	__m128 _mask128 = *(__m128*)_mask;
	__m128 curPos = _mm_load_ps((float*)attr.xyzw);
	__m128 oldPos = _mm_load_ps((float*)attrOld.xyzw);
	__m128 dt2    = _mm_set1_ps(dt*dt);					// dt2 = fTimeStep*fTimeStep
	__m128 acc    = _mm_load_ps((float*)a.xyz);			// acc = a vector
		   acc	  = _mm_and_ps(acc, _mask128);			// preserve 'xyz' term and remove 'w' term
	acc			  = _mm_mul_ps(acc, dt2);				// acc = a*fTimeStep*fTimeStep;
	oldPos		  = _mm_sub_ps(curPos, oldPos);			// oldPos = curPos-oldPos;
	oldPos		  = _mm_add_ps(oldPos, acc);			// oldPos = oldPos+acc --> curPos-oldPos+a*fTimeStep*fTimeStep
	curPos		  = _mm_add_ps(curPos, oldPos);			// curPos += oldPos;
	memcpy((void*)attrOld.xyzw, (void*)attr.xyzw, sizeof(float)*4);	// attrOld = attr;
	_mm_store_ps(attr.xyzw, curPos);
#else
	Vector3f curPosV = attr.getSphereCenter();
	Vector3f oldPosV = attrOld.getSphereCenter();
	curPosV += curPosV-oldPosV+a*dt*dt;
	attrOld = attr;
	attr.set(curPosV, attr.w);
#endif
}

#ifdef UNITTEST
TEST(PointmassVerlet)
{
	PointMass p(Vector4f(0.f, 0.f, 1.f, 1.f));
	p.Verlet(2.f, Vector3f(0.f, 1.f, 2.f));
	CHECK_EQUAL(1.f, p.GetMass());
	CHECK_EQUAL(0.f, p.GetPos().x);
	CHECK_EQUAL(4.f, p.GetPos().y);
	CHECK_EQUAL(9.f, p.GetPos().z);
}
#endif
