/*
 * Cvrp.cpp
 *
 *  Created on: 28/10/2014
 *      Author: Marvin
 */

#include "Cvrp.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>

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

double** CVRP::getD() {
	return this->d;
}

void CVRP::setD(double** cop) {
	this->d = cop;
}

bool** CVRP::getX() {
	return this->x;
}

void CVRP::setX(bool** x) {
	this->x = x;
}

void CVRP::init(VRP V) {
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(2);
	std::cout.imbue(
			std::locale(std::cout.getloc(), new punct_facet<char, ','>));

	bool init1 = false;

	if (init1) {
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
	} else {
		setNroCustomers(V.getBusAssigned().size() + 1);
		Customer depot(V.getCoorSchool().getX(), V.getCoorSchool().getY(),
				V.getCoorSchool().getCapacity());

		std::vector<Stop> a;
		a.insert(a.begin() + 0, V.getCoorSchool());
		std::vector<Stop> b = V.getBusAssigned();
		a.insert(a.end(), b.begin(), b.end());
		std::vector<Customer> allCustomers;
		for (size_t i = 0; i < a.size(); i++) {
			Stop stop = a.at(i);
			Customer customer(stop.getX(), stop.getY(), stop.getCapacity());
			allCustomers.insert(allCustomers.begin() + i, customer);
		}
		cout << "List of customers! the first customert is the depot." << endl;
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
	//Validation of the numbers of enters to the depot
	//Initialization of x
	//Initialization of d

	std::vector<Customer> allCustomers = getAllCustomers();
	int nro_customers = getNroCustomers();
	double** d_cvpr = new double*[nro_customers];
	double** s_cvpr = new double*[nro_customers];
	bool** x_cvpr = new bool*[nro_customers];

	for (int i = 0; i < nro_customers; i++) {
		d_cvpr[i] = new double[nro_customers];
		x_cvpr[i] = new bool[nro_customers];
		s_cvpr[i] = new double[nro_customers];
	}
	cout << "Save the distance in a d array of array" << endl;
	for (int i = 0; i < nro_customers; i++) {
		Customer customer = allCustomers.at(i);
		cout << "(" << customer.getX() << ", " << customer.getY() << ")"
				<< endl;
		for (int j = 0; j < nro_customers; j++) {
			Customer pivot = allCustomers.at(j);
			double distance = getDistanceIJ(customer, pivot);
			d_cvpr[i][j] = distance;
			x_cvpr[i][j] = false;
		}
	}
	cout << "Imprimir distance from i to j:" << endl;
	for (int i = 0; i < nro_customers; i++) {
		for (int j = 0; j < nro_customers; j++) {
			cout << d_cvpr[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "Imprimir x from i to j." << endl;
	for (int i = 0; i < nro_customers; i++) {
		for (int j = 0; j < nro_customers; j++) {
			cout << x_cvpr[i][j] << " ";
		}
		cout << "\n";
	}

	setD(d_cvpr);

	//CREATE CONSTRUCTIVE - Saving Computation
	std::vector<Saving> savingList;
	int count1 = 0;
	int nro_buses = getK();
	for (int i = 0; i < nro_buses; i++) {
		for (int j = 0; j < nro_buses; j++) {
			if (i != j) {
				double d1 = d_cvpr[i][0];
				double d2 = d_cvpr[0][j];
				double d3 = d_cvpr[i][j];

				s_cvpr[i][j] = d1 + d2 - d3;
				Saving save(i, j, s_cvpr[i][j]);
				savingList.insert(savingList.begin() + count1, save);
				count1++;
			}
		}
	}

//Ordering
	Saving temp;
	int flag = 1;
	for (size_t i = 1; i < savingList.size() && flag; i++) {
		flag = 0;
		for (size_t j = 0; j < savingList.size() - 1; j++) {
			if (savingList.at(j + 1).getSavingPeso()
					> savingList.at(j).getSavingPeso()) {
				temp = savingList.at(j);
				savingList.at(j) = savingList.at(j + 1);
				savingList.at(j + 1) = temp;
				flag = 1;
			}
		}
	}
	cout << "Saving List after ordered." << endl;
	for (size_t i = 0; i < savingList.size(); i++) {
		Saving save = savingList.at(i);

		cout << "i = " << save.getSavingX() << ", j = " << save.getSavingY()
				<< ", s[i][j] = " << savingList.at(i).getSavingPeso() << endl;
	}

	//We have K vehicles, according to C.W. I have to create
	//K vehicles with routes (O, i, O) for i = 1, 2, 3, n

	//int nro_buses = getK();

}

double CVRP::getFO() {
	double results = 0;
	std::vector<Customer> allCustomers = getAllCustomers();
	for (size_t i = 0; i < allCustomers.size(); i++) {
		for (size_t j = 0; j < allCustomers.size(); j++) {
			results = results + d[i][j] * x[i][j];
		}
	}
	return results;
}

double CVRP::getDistanceIJ(Customer c1, Customer c2) {
	double dx = 0.0, dy = 0.0, dr = 0.0;
	int a = 0, b = 0;
	a = c1.getX() - c2.getX();
	b = c1.getY() - c2.getY();
	dx = pow(a, 2);
	dy = pow(b, 2);
	dr = sqrt(dx + dy);
	return dr;
}
