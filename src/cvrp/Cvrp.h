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

using namespace std;

template<class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
	charT do_decimal_point() const {
		return sep;
	}
};

class CVRP {
private:
	int nroCustomers;
	std::vector<Customer> allCustomers;
	std::vector<Customer> allCustNoDepot;
	//A set of K identical vehicles, each with capacity C
	int K;
	int C;
	//The minimal number of vehicles to serve all the customers
	int Kmin;
	Customer depot;
	//Demanda de cada Customer
	std::vector<int> p;
	VRP vrp;
	std::map<int, std::vector<Customer> > map;

	//Parameters to determinate the objective function
	double** d;
	bool** x;
	double** s;
public:
	void init(VRP vrp);
	int getNroCustomers();
	void setNroCustomers(int customersIncludingDepot);

	std::vector<Customer> getAllCustomers();
	void setAllCustomers(std::vector<Customer> allCustomers);

	std::vector<Customer> getAllCustNoDepot();
	void setAllCustNoDepot(std::vector<Customer> allCustNoDepot);

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

	//Formulate
	double getFO();
	double getDistanceIJ(Customer c1, Customer c2);
	bool compareCustomers(Customer c1, Customer c2);
	bool validarPrimeraCondicion(Customer depot, Customer c1);
	bool validarSegundaCondicion(Customer c2, Customer depot);
	/*std::vector<std::vector<Customer> > modify(
	 std::vector<std::vector<Customer> > vCustomers, Customer c1,
	 Customer c2, int route1, int route2);
	 */
};

#endif /* CVRP_H_ */
