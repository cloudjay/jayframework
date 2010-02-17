#include "PhysicalEntity.h"

PhysicalEntity::PhysicalEntity(void)
: m(1.f), m_inv(1.f)
{
}

PhysicalEntity::~PhysicalEntity(void)
{
}

void PhysicalEntity::Step(float dt)
{
	pos += v*dt;
}
