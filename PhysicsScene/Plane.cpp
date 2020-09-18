#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distanceToOrigin) : PhysicsObject(PLANE)
{
	m_normal = glm::normalize(normal);
	m_distanceToOrigin = distanceToOrigin;
}

Plane::~Plane()
{

}

void Plane::makeGizmo()
{
	float lineSegmentLength = 360;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	// easy to rotate nomal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resolveCollision(RigidBody* other, glm::vec2 contact)
{
	glm::vec2 collisionNormal = m_normal;
	glm::vec2 relativeVelocity = other->getvelocity();

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), collisionNormal) / (1 / other->getMass());

	glm::vec2 force = collisionNormal * j;
	other->applyForce(force, contact - other->getPosition());

}