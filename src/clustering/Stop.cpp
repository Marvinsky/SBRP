/*
 * Stop.cpp
 *
 *  Created on: 15/10/2014
 *      Author: Marvin
 */

#include "Stop.h"

Stop::Stop(int x, int y) {
	this->x = x;
	this->y = y;
}

Stop::Stop(int x, int y, int capacity) {
	this->x = x;
	this->y = y;
	this->capacity = capacity;
}

int Stop::getX() {
	return x;
}

void Stop::setX(int x) {
	this->x = x;
}

int Stop::getY() {
	return this->y;
}

void Stop::setY(int y) {
	this->y = y;
}

int Stop::getCapacity() {
	return capacity;
}

void Stop::setCapacity(int capacity) {
	this->capacity = capacity;
}

