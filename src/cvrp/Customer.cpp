/*
 * Customer.cpp
 *
 *  Created on: 28/10/2014
 *      Author: Marvin
 */
#include "Customer.h"

Customer::Customer() {
	//TODO
}

Customer::Customer(int x, int y, int demand) {
	this->x = x;
	this->y = y;
	this->demand = demand;
}

Customer::Customer(int id, int x, int y, int demand) {
	this->id = id;
	this->x = x;
	this->y = y;
	this->demand = demand;
}

int Customer::getId() {
	return this->id;
}

void Customer::setId(int id) {
	this->id = id;
}

int Customer::getX() {
	return this->x;
}

void Customer::setX(int x) {
	this->x = x;
}

int Customer::getY() {
	return this->y;
}

void Customer::setY(int y) {
	this->y = y;
}

int Customer::getDemand() {
	return this->demand;
}

void Customer::setDemand(int demand) {
	this->demand = demand;
}

