#pragma once

#include "PhysicalEntity.h"

class PhysicalWorld
{
public:
	PhysicalWorld(void);
	~PhysicalWorld(void);

	void	Register(PhysicalEntity* pEnt);
	void	Step(float dt);

private:
	PhysEntList			m_entities;
};
