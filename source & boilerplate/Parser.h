/*
 * Parser.h
 *
 *  Created on: Nov. 18, 2018
 *      Author: bille
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Geometry.h"
#include <vector>
#include <string>
#include "Light.h"
#include <iostream>
#include <fstream>
using namespace std;


class Parser {
public:
	Parser();
	virtual ~Parser();

	void parseScene(std::string source, std::vector<Geometry*>* spaceItems, std::vector<Light>* lights);

	void removeWhiteSpaces(std::string* str);
	float parseFloat(std::string str);
	glm::vec3 parseVec(std::string str);
	void getNextLine(std::ifstream* myfile, std::string line);
	void parseAnObj(std::string source, std::vector<Geometry*>* spaceItems, int pExp, glm::vec3 color, glm::vec3 sp, glm::vec3 km);


};

#endif /* PARSER_H_ */
