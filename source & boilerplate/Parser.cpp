/*
 * Parser.cpp
 *
 *  Created on: Nov. 18, 2018
 *      Author: bille
 */

#include "Parser.h"
#include <iostream>
#include <string>
#include <glm/vec3.hpp>
#include <sstream>
#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::parseAnObj(std::string source, std::vector<Geometry*>* spaceItems, int pExp, glm::vec3 color, glm::vec3 sp, glm::vec3 km) {
	std::string currentLine;
		std::ifstream myfile(source);
		std::cout << source << "is " << myfile.is_open() << "\n";
		std::vector<glm::vec3> points;
		if (myfile.is_open()) {
			while (getline(myfile, currentLine)) {
				removeWhiteSpaces(&currentLine);
				if (currentLine[0] == '#' || currentLine.empty() || currentLine[0] == '}' || currentLine[0] == '{') continue;
				// else create a triangle object

				if (currentLine[0] == 'v') {
					// remove v
					currentLine = currentLine.substr(1, std::string::npos);
					removeWhiteSpaces(&currentLine);
					// parse point
					glm::vec3 aPoint = parseVec(currentLine);
					points.push_back(aPoint);
				} else if (currentLine[0] == 'f') {
					// remove v
					currentLine = currentLine.substr(1, std::string::npos);
					removeWhiteSpaces(&currentLine);
					// parse triangle object
					glm::vec3 pointsToUse = parseVec(currentLine);

					// create triangle
					Triangle* aNewTri = new Triangle(points[pointsToUse.x - 1], points[pointsToUse.y - 1], points[pointsToUse.z - 1], pExp, color, sp, km);
					spaceItems->push_back(aNewTri);

				} else {
					std::cout << "Unidentified line: " << currentLine << "\n";
					exit(-1);
				}
			}
		}

}

void Parser::parseScene(std::string source, std::vector<Geometry*>* spaceItems, std::vector<Light>* lights) {
	std::string currentLine;
	std::ifstream myfile(source);
	std::cout << source << "is " << myfile.is_open() << "\n";
	if (myfile.is_open()) {
		while (getline(myfile, currentLine)) {
			// remove leading and trailing white spaces
			removeWhiteSpaces(&currentLine);
			//std::cout << currentLine << "\n";
			// skips irrelevant lines
			if (currentLine[0] == '#' || currentLine.empty() || currentLine[0] == '}' || currentLine[0] == '{') continue;

			if (currentLine == ("light {") || currentLine == ("light")) {
				//std::cout <<currentLine <<"light triggered \n";
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);

				glm::vec3 pos = parseVec(currentLine);
				Light aNewLight(pos);
				lights->push_back(aNewLight);

			} else if (currentLine == ("triangle {") || currentLine == ("triangle")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p0 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p1 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 p2 = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Triangle* aNewTri = new Triangle(p0, p1, p2, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewTri);
			} else if (currentLine == ("plane {") || currentLine == ("plane")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 normal = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 point = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Plane* aNewPlane = new Plane(normal, point, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewPlane);
			} else if(currentLine == ("sphere {") || currentLine == ("sphere")) {
				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 center = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				//std::cout <<currentLine << "\n";
				float radius = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				float pExp = parseFloat(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 color = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 specularC = parseVec(currentLine);

				getline(myfile, currentLine);
				removeWhiteSpaces(&currentLine);
				glm::vec3 mirrorC = parseVec(currentLine);

				Sphere* aNewSphere = new Sphere(center, radius, pExp, color, specularC, mirrorC);
				spaceItems->push_back(aNewSphere);

			} else {
				std::cout << "Encountered Unknown line " << currentLine << "\n";
				std::cout <<"Terminating Program\n";
				exit(-1);
			}


		}
	}
	myfile.close();

}

/*
void Parser::getNextLine(std::ifstream* myfile, std::string line) {
	getline(myfile, line);
	removeWhiteSpaces(line);
}
*/
void Parser::removeWhiteSpaces(std::string* str) {
	std::size_t ind = str->find_first_not_of(" \t");
	str->erase(0, ind);

	ind = str->find_last_not_of(" \t");
	if (std::string::npos != ind) {
		str->erase(ind+1);
	}

}

float Parser::parseFloat(std::string line) {
	//std::string::size_type sz;
	std::cout << line << "\n";
	float output = std::stof(line);
	std::cout << "output = " << output << "\n";
	return output;
}

glm::vec3 Parser::parseVec(std::string str) {
	std::cout << str << "\n";
	std::string::size_type sz;

	float x = std::stof(str, &sz);
	std::string subS = str.substr(sz);
	float y = std::stof(subS, &sz);
	subS = subS.substr(sz);
	float z = std::stof(subS, &sz);

	std::cout << "x value = " << x << "\n";
	std::cout << "y value = " << y << "\n";
	std::cout << "z value = " << z << "\n";

	return glm::vec3(x, y ,z);

}





