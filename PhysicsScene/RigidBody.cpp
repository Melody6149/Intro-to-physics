#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;

	m_velocity -= m_velocity * m_linearDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	otherActor->applyForce(force);
	applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 perpendicular(normal.y, -normal.x);

	float radius;

	float otherRadius;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));
	
	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);
}

