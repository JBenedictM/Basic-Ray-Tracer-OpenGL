/*
 * Plane.h
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "Geometry.h"

class Plane: public Geometry {
public:
	Plane(glm::vec3 normal, glm::vec3 point, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km);
	virtual ~Plane();

	float intersect(glm::vec3 p0, glm::vec3 rayDirection) override;

	glm::vec3 getNormal();

private:
	glm::vec3 normal;
	glm::vec3 point;
};

#endif /* PLANE_H_ */
