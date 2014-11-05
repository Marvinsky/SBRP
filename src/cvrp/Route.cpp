/*
 * Route.cpp
 *
 *  Created on: 05/11/2014
 *      Author: Marvin
 */

#include "Route.h"
#include <cmath>

Route::Route() {
	//TODO
}

Route::Route(std::vector<Customer> route) {
	this->route = route;
}

std::vector<Customer> Route::getRoute() {
	return this->route;
}

void Route::setRoute(std::vector<Customer> route) {
	this->route = route;
}

double Route::getCost() {
	std::vector<Customer> customers = this->route;
	double sum = 0.0;
	for (size_t i = 0; i < customers.size() - 1; i++) {
		Customer c1 = customers.at(i);
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c2 = customers.at(j);
			if (i + 1 == j) {
				double distance = getDistanceIJ(c1, c2);
				sum = sum + distance;
			}
		}
	}
	this->cost = sum;
	return sum;
}

void Route::setCost(double cost) {
	this->cost = cost;
}

double Route::getDistanceIJ(Customer c1, Customer c2) {
	double dx = 0.0, dy = 0.0, dr = 0.0;
	dx = pow((c2.getX() - c1.getX()), 2);
	dy = pow((c2.getY() - c1.getY()), 2);

	dr = sqrt(dx + dy);
	return dr;
}

