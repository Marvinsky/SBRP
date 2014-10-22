/*
 * Student.cpp
 *
 *  Created on: 16/10/2014
 *      Author: Marvin
 */

#include "Student.h"

Student::Student() {
	//NOTHING
}

Student::Student(int x, int y) {
	this->coord_x = x;
	this->coord_y = y;
}

int Student::getCoord_x() {
	return this->coord_x;
}

void Student::setCoord_x(int x) {
	this->coord_x = x;
}

int Student::getCoord_y() {
	return this->coord_y;
}

void Student::setCoord_y(int y) {
	this->coord_y = y;
}

