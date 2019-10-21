/*
 * Plane.cpp
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#include "Plane.h"
#include <iostream>
Plane::Plane(glm::vec3 normal, glm::vec3 point, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km) : Geometry(std::vector<glm::vec3>({normal, point}), exp, color, sc, km) {
	this->normal = normal;
	this->point = point;
	type = Geometry::PLANE;

}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

float Plane::intersect(glm::vec3 p0, glm::vec3 rayDirection) {
	float t = (glm::dot(point, normal) - glm::dot(p0, normal)) / glm::dot(rayDirection, normal);
	//std::cout << "t value = " << t << "\n";

	if (t >= 0.0f ) {
		return t;
	} else {
		return -1.0f;
	}
}

glm::vec3 Plane::getNormal() {
	return glm::vec3(normal.x, normal.y, normal.z);
}


