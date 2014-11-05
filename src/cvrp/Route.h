/*
 * Route.h
 *
 *  Created on: 05/11/2014
 *      Author: Marvin
 */

#ifndef ROUTE_H_
#define ROUTE_H_
#include "Customer.h"
#include <vector>
#include <string>

class Customer;

class Route {
private:
	std::vector<Customer> route;
	double cost;
public:
	Route();
	Route(std::vector<Customer> route);
	std::vector<Customer> getRoute();
	void setRoute(std::vector<Customer> route);
	double getCost();
	void setCost(double cost);
	double getDistanceIJ(Customer c1, Customer c2);
};

#endif /* ROUTE_H_ */
