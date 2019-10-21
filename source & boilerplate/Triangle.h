/*
 * Triangle.h
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Geometry.h"

class Triangle: public Geometry {
public:
	Triangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km);
	virtual ~Triangle();

	float intersect(glm::vec3 p0, glm::vec3 rayDirection) override;

	glm::vec3 getLine1();
	glm::vec3 getLine2();

private:
	glm::vec3 point0;
	glm::vec3 point1;
	glm::vec3 point2;

	glm::vec3 line1;
	glm::vec3 line2;

};

#endif /* TRIANGLE_H_ */
