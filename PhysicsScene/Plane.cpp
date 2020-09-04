#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distanceToOrigin) : PhysicsObject(PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distanceToOrigin;
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
