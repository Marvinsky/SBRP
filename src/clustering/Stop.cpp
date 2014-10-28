/*
 * Stop.cpp
 *
 *  Created on: 15/10/2014
 *      Author: Marvin
 */

#include "Stop.h"

Stop::Stop() {
	//TODO
}

Stop::Stop(int x, int y) {
	//depot
	this->id = 0;
	this->x = x;
	this->y = y;
	this->capacity = 0;
}

Stop::Stop(int x, int y, int capacity) {
	this->x = x;
	this->y = y;
	this->capacity = capacity;
}

Stop::Stop(int id, int x, int y, int capacity) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->capacity = capacity;
}

int Stop::getId() {
	return this->id;
}

void Stop::setId(int id) {
	this->id = id;
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

