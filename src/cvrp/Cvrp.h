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
#include "Saving.h"

#include <locale>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

template<class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
	charT do_decimal_point() const {
		return sep;
	}
};

struct CustomerDD {
	Customer c;
	double distance;
	int demand;
};

class CompareCustomerSDD {
public:
	bool operator()(CustomerDD c1, CustomerDD c2) {
		if (c1.distance > c2.distance) {
			return true;
		}
		return false;
	}
};

class CVRP {
private:
	int nroCustomers;
	std::vector<Customer> allCustomers;
	std::vector<Customer> allCustNoDepot;
	std::vector<std::vector<Customer> > allRoutesGreedy;
	std::vector<std::vector<Customer> > allRoutesSaving;
	//A set of K identical vehicles, each with capacity C
	int K;
	int C;
	//The minimal number of vehicles to serve all the customers
	int Kmin;
	Customer depot;
	//Demanda de cada Customer
	std::vector<int> p;
	VRP vrp;
	std::map<int, Customer> map;

	//Parameters to determinate the objective function
	double** d;
	bool** x;
	double** s;
public:
	void init(VRP vrp);
	void greedy(VRP vrp);
	int getNroCustomers();
	void setNroCustomers(int customersIncludingDepot);

	std::vector<Customer> getAllCustomers();
	void setAllCustomers(std::vector<Customer> allCustomers);

	std::vector<Customer> getAllCustNoDepot();
	void setAllCustNoDepot(std::vector<Customer> allCustNoDepot);

	std::vector<std::vector<Customer> > getAllRoutesGreedy();
	void setAllRoutesGreedy(std::vector<std::vector<Customer> > allRoutes);

	std::vector<std::vector<Customer> > getAllRoutesSaving();
	void setAllRoutesSaving(
			std::vector<std::vector<Customer> > allRoutesSaving);

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
	//Operations to calculate the
	double** getD();
	void setD(double ** cop);
	bool** getX();
	void setX(bool** X);
	double** getS();
	void setS(double** s);

	//Formulate
	double getFO();
	double getDistanceIJ(Customer c1, Customer c2);
	bool compareCustomers(Customer c1, Customer c2);

	//New Implementation
	Customer getCustomerLessDemand(std::vector<Customer> customers);
	Customer getCustomerLessDistance(std::vector<Customer> customers,
			Customer customer);
	std::vector<Customer> removeCustomerFromRoute(
			std::vector<Customer> customers, Customer customer);
	bool isInFinalRoute(std::vector<Customer> customers, Customer customer);
	std::vector<Customer> expand(std::vector<Customer> allCustomers,
			Customer customer);
	void savingAlgorithm();
	int getRouteDemand(std::vector<Customer> customers);

	//Generate Reports
	void initialSolutionReport();

};

#endif /* CVRP_H_ */
