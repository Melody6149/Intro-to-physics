#pragma once
#include "glm\ext.hpp"
#include "PhysicsObject.h"
#include <vector>
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();
	
	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float deltaTime);
	void checkForCollision();
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	static bool planeToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool planeToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool sphereToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool sphereToSphere(PhysicsObject* object1, PhysicsObject* object2);

protected:
	glm::vec2 m_gravity;
		float m_timeStep;
		std::vector<PhysicsObject*>  m_actors;
};