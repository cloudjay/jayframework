#pragma once
#include "Physic.h"
#include <vector>

class PhysicalEntity
{
public:
	PhysicalEntity(void);
	~PhysicalEntity(void);

	void				Step(float dt);

private:
	Vector3f			pos;
	float				m;
	Vector3f			v;
	float				m_inv;
};

typedef std::vector<PhysicalEntity*>	PhysEntList;
typedef PhysEntList::iterator			PhysEntIter;
