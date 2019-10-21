/*
 * Light.cpp
 *
 *  Created on: Nov. 13, 2018
 *      Author: bille
 */

#include "Light.h"

Light::Light(glm::vec3 pos) : Light(pos, glm::vec3(1.0f, 1.0f, 1.0f)) {
	// TODO Auto-generated constructor stub

}

Light::Light(glm::vec3 pos, glm::vec3 ints) {
	this->position = pos;
	this->intensity = ints;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Light::getPosition() {
	return glm::vec3(this->position.x, this->position.y, this->position.z);
}

glm::vec3 Light::getIntensity() {
	return glm::vec3(this->intensity.x, this->intensity.y, this->intensity.z);
}
