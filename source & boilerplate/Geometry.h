/*
 * Geometry.h
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <glm/vec3.hpp>
#include <vector>
#include <glm/glm.hpp>

class Geometry {
public:
	//Geometry();
	Geometry(std::vector<glm::vec3> vertices, float exp, glm::vec3 color, glm::vec3 sc, glm::vec3 km);
	virtual ~Geometry();

	virtual float intersect(glm::vec3 p0, glm::vec3 rayDirection) = 0;
	static glm::vec3 normalizeVec(glm::vec3 vector);

	void initAppearance(float texture, glm::vec3 color, glm::vec3 sc, glm::vec3 km);

	glm::vec3 getColor();
	float getPExponent();

	void setSpecularColor(glm::vec3 sc);

	glm::vec3 getSpecularColor();

	const int getType();

	void setMirrorColor(glm::vec3 km);

	glm::vec3 getMirrorColor();

	static const int TRIANGLE;
	static const int SPHERE;
	static const int PLANE;
	static const int NONE;

	float intersect(glm::vec3 p0, glm::vec3 rayDirection, int noUse);


private:
	std::vector<glm::vec3> vertices;
	float shinyExp;
	glm::vec3 color;
	glm::vec3 specularColor;
	glm::vec3 mirrorColor;

protected:
	int type = Geometry::NONE;

};

#endif /* GEOMETRY_H_ */
