/*
 * Sphere.h
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Geometry.h"

class Sphere: public Geometry {
public:
	Sphere(glm::vec3 center, float r, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km);

	virtual ~Sphere();


	float intersect(glm::vec3 p0, glm::vec3 rayDirection) override;

	glm::vec3 getCenter();

private:
	float radius;
	glm::vec3 center;
};

#endif /* SPHERE_H_ */
