/*
 * Sphere.cpp
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#include "Sphere.h"
//#include <glm/gtc/type_ptr.hpp>

Sphere::Sphere(glm::vec3 center, float r, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km) : Geometry(std::vector<glm::vec3>({center}), exp, color, sc, km) {
	radius = r;
	this->center = center;
	this->type = Geometry::SPHERE;

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

float Sphere::intersect(glm::vec3 p0, glm::vec3 rayDirection) {
	glm::vec3 centerToOrigin = p0 - center;
	float a = glm::dot(rayDirection, rayDirection);
	float b = glm::dot(2.0f*rayDirection, centerToOrigin);
	float c = glm::dot(centerToOrigin, centerToOrigin) - pow(radius, 2.0f);
	float determinant = pow(b, 2.0f) - (4.0f*a*c);

	float sol1 = 10000.0f;
	float sol2 = 10000.0f;
	if (determinant < 0.00000000f) {
		return -1.0f;
	} else if (determinant == 0.0f) {
		sol1 = ((-1.0f*b)) / (2.0f*a);
	} else {
		float sqrdDet = sqrt(determinant);
		sol1 = ((-1.0f*b) + sqrdDet) / (2.0f*a);
		sol2 = ((-1.0f*b) - sqrdDet) / (2.0f*a);
	}

	return std::min(sol1, sol2);
}



glm::vec3 Sphere::getCenter() {
	return glm::vec3(center.x, center.y, center.z);
}
