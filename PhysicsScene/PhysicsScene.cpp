#include "PhysicsScene.h"
#include "RigidBody.h"
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

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

//void PhysicsScene::debugScene()
//{
//	for (auto actor : m_actors)
//	{
//		actor->debug();
//	}
//}