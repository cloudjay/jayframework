#include "PhysicalWorld.h"

PhysicalWorld::PhysicalWorld(void)
{
}

PhysicalWorld::~PhysicalWorld(void)
{
}

void PhysicalWorld::Register(PhysicalEntity *pEnt)
{
	m_entities.push_back(pEnt);
}

void PhysicalWorld::Step(float dt)
{
	for (PhysEntIter it = m_entities.begin(); it != m_entities.end(); ++it) {
		((PhysicalEntity*)*it)->Step(dt);
	}
}
