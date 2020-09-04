#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include <list>
PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
	
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i < m_actors.end(); i++)
	{
		if (*i == actor)
		{
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float deltaTime)
{
	static std::list<PhysicsObject*> dirty;
	// update physics at a fixed time step

	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;
		for (auto actor : m_actors)
		{
			for (auto other : m_actors)
			{
				if (actor == other)
				{
					continue;
				}
				if (std::find(dirty.begin(), dirty.end(), actor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), other) != dirty.end())
				{
					continue;
				}
				RigidBody* actorRB = dynamic_cast<RigidBody*> (actor);
				RigidBody* otherRB = dynamic_cast<RigidBody*> (actor);
				if (!actorRB || !otherRB)
					continue;
				if (actorRB->checkColllision(otherRB))
				{
					actorRB->applyForceToActor(otherRB, actorRB->getvelocity() * actorRB->getMass());
					dirty.push_back(actor);
					dirty.push_back(other);
				}
			}
		}
		dirty.clear();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctions[] =
{
	PhysicsScene::planeToPlane, PhysicsScene::planeToSphere,
	PhysicsScene::sphereToPlane, PhysicsScene::sphereToSphere
};

void PhysicsScene::checkForCollision()
{
	// get the number of actors in the scene
	int actorCount = m_actors.size();

	// check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount - 1; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius())
		{
			sphere1->applyForceToActor(sphere2, sphere1->getvelocity() * sphere1->getMass());
			return true;
		}
	}
}

//void PhysicsScene::debugScene()
//{
//	for (auto actor : m_actors)
//	{
//		actor->debug();
//	}
//}