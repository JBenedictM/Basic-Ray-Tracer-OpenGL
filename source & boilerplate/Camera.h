/*
 * Camera.h
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/vec3.hpp>
#include <vector>
#include "imagebuffer.h"
#include "Geometry.h"
#include "Light.h"


class Camera {
public:
	Camera(float imageWidth, float imageHeight, std::vector<Geometry*> spaceItems, std::vector<Light> lights);
	Camera(float imageWidth, float imageHeight, std::vector<glm::vec3> basis, float fovAngle, std::vector<Geometry*> spaceItems, std::vector<Light> lights);
	virtual ~Camera();

	glm::vec3 shootRay(int pixelRow, int pixelCol);

	void captureImage();

	void setFOV(float angle);

	void setImageDimension(float imageWidth, float imageHeight);

	void setSpaceItems(std::vector<Geometry*> spaceItems);

	void setLights(std::vector<Light> lights);

	void setAmbLight(std::vector<Light> lightSource);

	glm::vec3 shootRay(int pixelRow, int pixelCol, glm::vec3 origin, glm::vec3 direction);



private:
	float fieldOfView;
	std::vector<glm::vec3> basisVecs;
	std::vector<Geometry*> spaceItems;
	std::vector<Light> lights;
	glm::vec3 ambientLight;
	float imageWidth;
	float imageHeight;
	float l;
	float r;
	float b;
	float t;

	glm::vec3 shootRay(glm::vec3 p0, glm::vec3 rayDirection);

	bool inShadow(glm::vec3 intersectPoint);

	const int MAX_REFLECTION = 10;
	int recursionCount = 0;
};

#endif /* CAMERA_H_ */
