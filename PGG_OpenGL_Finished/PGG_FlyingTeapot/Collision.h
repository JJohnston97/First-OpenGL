#ifndef _COLLISION_H
#define _COLLISION_H

#include "Vector3.h"
#include "ContactPoint.h"

#include <vector>

namespace mutiny
{

	namespace engine
	{

		class Collider;

		class Collision
		{
		public:
			Vector3 relativeVelocity;
			std::vector<ContactPoint> contacts;
			//ref<Collider> collider;

		};

	}

}

#endif