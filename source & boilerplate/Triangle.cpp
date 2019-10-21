/*
 * Triangle.cpp
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#include "Triangle.h"

Triangle::Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km) : Geometry(std::vector<glm::vec3>({p0, p1, p2}), exp, color, sc, km) {
	point0 = p0;
	point1 = p1;
	point2 = p2;

	line1 = p1 - p0;
	line2 = p2 - p0;
	type = Geometry::TRIANGLE;
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

float Triangle::intersect(glm::vec3 p0, glm::vec3 rayDirection) {
	glm::vec3 s = p0 - point0;

	float det1 = determinant(glm::mat3(-1.0f*rayDirection, line1, line2));
	float det2 = determinant(glm::mat3(s, line1, line2));
	float det3 = determinant(glm::mat3(-1.0f*rayDirection, s, line2));
	float det4 = determinant(glm::mat3(-1.0f*rayDirection, line1, s));

	float u = det3 / det1;
	float v = det4 / det1;
	float t = det2 / det1;

	// checks if u, v and u+v are within [0, 1]
	// else returns -1.0f which implies that t does not intersect
	if ((u >= 0.00000f && u <= 1.000000f) && (v >= 0.000000f && v <= 1.000000f) && ((u+v) <= 1.0000000f) && (t > 0.00000000f)) {
		return (t);
	} else
		return -1.0f;
}

glm::vec3 Triangle::getLine1() {
	return glm::vec3(line1.x, line1.y, line1.z);
}

glm::vec3 Triangle::getLine2() {
	return glm::vec3(line2.x, line2.y, line2.z);
}

