/*
 * Cvrp.cpp
 *
 *  Created on: 28/10/2014
 *      Author: Marvin
 */

#include "Cvrp.h"

int CVRP::getNroCustomers() {
	return this->nroCustomers;
}

void CVRP::setNroCustomers(int customersInclundingDepor) {
	this->nroCustomers = customersInclundingDepor;
}

std::vector<Customer> CVRP::getAllCustomers() {
	return this->allCustomers;
}

void CVRP::setAllCustomers(std::vector<Customer> allCustomers) {
	this->allCustomers = allCustomers;
}

int CVRP::getK() {
	return this->K;
}

void CVRP::setK(int K) {
	this->K = K;
}

int CVRP::getC() {
	return this->C;
}

void CVRP::setC(int C) {
	this->C = C;
}

int CVRP::getKmin() {
	return this->Kmin;
}

void CVRP::setKmin(int Kmin) {
	this->Kmin = Kmin;
}

Customer CVRP::getDepot() {
	return this->depot;
}

void CVRP::setDepot(Customer c) {
	this->depot = c;
}

std::vector<int> CVRP::getP() {
	return this->p;
}

void CVRP::setP(std::vector<int> demands) {
	this->p = demands;
}

VRP CVRP::getVRP() {
	return this->vrp;
}

void CVRP::setVRP(VRP vrp) {
	this->vrp = vrp;
}

void CVRP::init(VRP V) {
	setNroCustomers(V.getBusStops().size() + 1);
	Customer depot(V.getCoorSchool().getX(), V.getCoorSchool().getY(),
			V.getCoorSchool().getCapacity());

	std::vector<Stop> a;
	a.insert(a.begin() + 0, V.getCoorSchool());
	std::vector<Stop> b = V.getBusStops();
	a.insert(a.end(), b.begin(), b.end());
	std::vector<Customer> allCustomers;
	for (size_t i = 0; i < a.size(); i++) {
		Stop stop = a.at(i);
		Customer customer(stop.getX(), stop.getY(), stop.getCapacity());
		allCustomers.insert(allCustomers.begin() + i, customer);
	}

	for (size_t i = 0; i < allCustomers.size(); i++) {
		Customer customer = allCustomers.at(i);
		cout << "(" << customer.getX() << ", " << customer.getY() << ", "
				<< customer.getDemand() << ")" << endl;
	}

	setAllCustomers(allCustomers);
	setK(V.getK());
	setC(V.getCk());
	setKmin(V.getKmin());

}

