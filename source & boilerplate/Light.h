/*
 * Light.h
 *
 *  Created on: Nov. 13, 2018
 *      Author: bille
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/vec3.hpp>


class Light {
public:
	Light(glm::vec3 pos);
	Light(glm::vec3 pos, glm::vec3 ints);
	virtual ~Light();

	glm::vec3 getPosition();
	glm::vec3 getIntensity();

private:
	glm::vec3 position;
	glm::vec3 intensity;
};

#endif /* LIGHT_H_ */
