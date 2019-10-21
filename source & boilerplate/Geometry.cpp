/*
 * Geometry.cpp
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#include "Geometry.h"
#include <math.h>

Geometry::Geometry(std::vector<glm::vec3> vertices, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km) {
	this->vertices = vertices;
	initAppearance(exp, color, sc, km);
}

Geometry::~Geometry() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Geometry::normalizeVec(glm::vec3 vector) {
	float vecLength = 1.0f / (sqrt(pow(vector.x, 2.0f) + pow(vector.y, 2.0f) + pow(vector.z, 2.0f)));
	return vecLength*vector;
}

void Geometry::initAppearance(float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km) {
	this->shinyExp = exp;
	this->color = color;
	setSpecularColor(sc);
	setMirrorColor(km);
}

glm::vec3 Geometry::getColor() {
	return glm::vec3(color.x, color.y, color.z);
}

float Geometry::getPExponent() {
	return shinyExp;
}

void Geometry::setMirrorColor(glm::vec3 km) {
	mirrorColor = km;
}
float Geometry::intersect(glm::vec3 p0, glm::vec3 rayDirection) {
	return -1.0f;
}

void Geometry::setSpecularColor(glm::vec3 sc) {
	specularColor = sc;
}

glm::vec3 Geometry::getSpecularColor() {
	return glm::vec3(specularColor.x, specularColor.y, specularColor.z);
}

glm::vec3 Geometry::getMirrorColor() {
	return glm::vec3(mirrorColor.x, mirrorColor.y, mirrorColor.z);
}

const int Geometry::getType() {
	return type;
}

const int Geometry::PLANE = 0;
const int Geometry::TRIANGLE = 1;
const int Geometry::SPHERE = 2;
const int Geometry::NONE = -1;




