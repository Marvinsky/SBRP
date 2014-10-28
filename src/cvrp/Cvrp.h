/*
 * Cvrp.h
 *
 *  Created on: 28/10/2014
 *      Author: Marvin
 */

#ifndef CVRP_H_
#define CVRP_H_

#include <vector>
#include "Customer.h"
#include "../clustering/Vrp.h"

#include <iostream>
using namespace std;

class CVRP {
private:
	int nroCustomers;
	std::vector<Customer> allCustomers;
	//A set of K identical vehicles, each with capacity C
	int K;
	int C;
	//The minimal number of vehicles to serve all the customers
	int Kmin;
	Customer depot;
	//Demanda de cada Customer
	std::vector<int> p;
	VRP vrp;

public:
	void init(VRP vrp);
	int getNroCustomers();
	void setNroCustomers(int customersIncludingDepot);

	std::vector<Customer> getAllCustomers();
	void setAllCustomers(std::vector<Customer> allCustomers);

	int getK();
	void setK(int K);
	int getC();
	void setC(int C);
	int getKmin();
	void setKmin(int Kmin);
	Customer getDepot();
	void setDepot(Customer c);

	std::vector<int> getP();
	void setP(std::vector<int> demands);

	VRP getVRP();
	void setVRP(VRP vrp);

	CVRP getVRP(VRP vrp);
};

#endif /* CVRP_H_ */
