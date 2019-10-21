/*
 * Camera.cpp
 *
 *  Created on: Nov. 11, 2018
 *      Author: bille
 */
#include <iostream>
using namespace std;

#include <vector>
#include "Camera.h"
#include <math.h>
#include <glm/glm.hpp>
#include "Plane.h"
#include "Triangle.h"
#include "Sphere.h"



Camera::Camera(float imageWidth, float imageHeight, std::vector<Geometry*> spaceItems, std::vector<Light> lights) : Camera(imageWidth, imageHeight, std::vector<glm::vec3>({glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)}), 45.0f, spaceItems, lights) {

}

Camera::Camera(float imageWidth, float imageHeight, std::vector<glm::vec3> basis, float fovAngle, vector<Geometry*> spaceItems, std::vector<Light> lights) {
	setImageDimension(imageWidth, imageHeight);
	basisVecs = basis;
	setFOV(fovAngle);
	setSpaceItems(spaceItems);
	setLights(lights);
	setAmbLight(lights);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::setFOV(float angle) {
	fieldOfView = angle * (3.14f/180.0f);
}

void Camera::setSpaceItems(std::vector<Geometry*> spaceItems) {
	this->spaceItems = spaceItems;
}

void Camera::setImageDimension(float imageWidth, float imageHeight) {
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	l = -1.0f * (this->imageWidth/2.0f);
	b = -1.0f * (this->imageHeight/2.0f);
}

void Camera::setLights(vector<Light> lights) {
	this->lights = lights;
}

void Camera::setAmbLight(std::vector<Light> lightSource) {
	ambientLight = lightSource[0].getIntensity() * 0.25f;
}

bool Camera::inShadow(glm::vec3 intersectPoint) {
	glm::vec3 lightVec = Geometry::normalizeVec(lights[0].getPosition() - intersectPoint);


	float minT = 10000.0f;
	float t = -1.0f;
	for (unsigned int i = 0; i < spaceItems.size(); i++) {
		t = spaceItems[i]->intersect(intersectPoint, lightVec);
		if ((t > 0.0001f) && (minT > t) ) {
			minT = t;
		}
	}

	return ((minT != 10000.0f)) && (glm::length(lights[0].getPosition() - intersectPoint) > glm::length((minT * lightVec)));
}

// shoot rays with respect to the given ray direction
glm::vec3 Camera::shootRay(glm::vec3 p0, glm::vec3 rayDirection) {
	recursionCount++;		// increments recursion counter so rays don't reflect indefinitely

	// calculates the object that intersects the closes to the respective ray
	float minT = 1000.0f;
	Geometry* intersectedItem = NULL;
	for (unsigned int i = 0; i < spaceItems.size(); i++) {
		float t = spaceItems[i]->intersect(p0, rayDirection);

		if ((t != -1.0f) && (minT > t) && (t > 0.00001f)) {
			minT = t;
			intersectedItem = spaceItems[i];
			//break;
		}
	}

	// check if ray intersected with anything
	// otherwise set the color of the intersection to black
	if (intersectedItem == NULL){
		return glm::vec3(0.0f); 		//default color for no intersection is black
	}

	// calculates lighting
	// accounts for diffusion, secular, and ambient lights
	// also the shininess of an object
	glm::vec3 intersectPoint = p0 + (minT*rayDirection);
	glm::vec3 view = glm::normalize(-1.0f*rayDirection);
	glm::vec3 l = lights[0].getPosition() - intersectPoint;
	l = glm::normalize(l);
	glm::vec3 sc = intersectedItem->getSpecularColor();
	glm::vec3 intensity = lights[0].getIntensity();
	glm::vec3 halfVec = glm::normalize(view + l);
	glm::vec3 normal = glm::vec3(0.0f);		// default normal value
	// get normal based on the type of the item
	int type = intersectedItem->getType();
	if (type == Geometry::PLANE) {
		normal = static_cast<Plane*>(intersectedItem)->getNormal();
	} else if (type == Geometry::TRIANGLE) {
		Triangle* aTri = static_cast<Triangle*>(intersectedItem);
		normal = glm::cross(aTri->getLine1(), aTri->getLine2());
	} else if (type == Geometry::SPHERE) {
		normal = (intersectPoint - (static_cast<Sphere*>(intersectedItem)->getCenter()));

	} else {
		std::cout << "Item type unknown, normal cannot be calculated\n";
	}
	normal = glm::normalize(normal);

	bool isShadow = inShadow(intersectPoint);
	glm::vec3 outputColor = intersectedItem->getColor();
	if (isShadow) {
		outputColor = ambientLight * outputColor;
	} else {
		outputColor = (ambientLight * outputColor) + (outputColor * intensity * std::max(0.0f, glm::dot(normal,l))) + (sc * intensity * pow(std::max(0.0f, glm::dot(normal, halfVec)), intersectedItem->getPExponent()));
	}

	glm::vec3 km = intersectedItem->getMirrorColor();
	if (recursionCount == MAX_REFLECTION || glm::length(km) == 0.0f) {
		return outputColor;
	} else {
		// calculate reflections
		glm::vec3 d =  -1.0f * view;
		// ** REFLECTION OF A REFLECTION ON A SPHERE IS WONKY **
		glm::vec3 r = d - (2.0f*(glm::dot(d, normal))*normal);
		return outputColor = outputColor + km*(shootRay(intersectPoint, Geometry::normalizeVec(r)));
	}

}

// calculates the ray relative to the camera and into the pixel corresponding to the given parameters
glm::vec3 Camera::shootRay(int pixelRow, int pixelCol) {
	//std::cout << "shootRay triggered\n";
	//std::cout << "Calculating row = " << pixelRow << "\n";
	//std::cout << "Calculating column = " << pixelCol << "\n";

	float wCoord = (imageHeight/2.0f) / tan(fieldOfView/2.0f);
	wCoord = -1.0f*wCoord;

	float uCoord = l + ((pixelCol + 0.5f));
	float vCoord = b + ((pixelRow + 0.5f));
	// direction with respect to camera
	glm::vec3 camDirection = Geometry::normalizeVec(glm::vec3(uCoord, vCoord, wCoord));


	recursionCount = 0;

	return shootRay(glm::vec3(0.0f, 0.0f, 0.0f), camDirection);
}


