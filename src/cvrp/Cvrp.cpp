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

std::vector<Customer> CVRP::getAllCustNoDepot() {
	return this->allCustNoDepot;
}

void CVRP::setAllCustNoDepot(std::vector<Customer> allCustNoDepot) {
	this->allCustNoDepot = allCustNoDepot;
}

std::vector<std::vector<Customer> > CVRP::getAllRoutesGreedy() {
	return this->allRoutesGreedy;
}

void CVRP::setAllRoutesGreedy(std::vector<std::vector<Customer> > allRoutes) {
	this->allRoutesGreedy = allRoutes;
}

std::vector<std::vector<Customer> > CVRP::getAllRoutesSaving() {
	return this->allRoutesSaving;
}

void CVRP::setAllRoutesSaving(
		std::vector<std::vector<Customer> > allRoutesSaving) {
	this->allRoutesSaving = allRoutesSaving;
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

double** CVRP::getS() {
	return this->s;
}

void CVRP::setS(double** s) {
	this->s = s;
}

void CVRP::greedy(VRP V) {
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(2);
	std::cout.imbue(
			std::locale(std::cout.getloc(), new punct_facet<char, ','>));

	bool init1 = false;

	if (init1) {
		setNroCustomers(V.getBusStops().size() + 1);
		Customer depot(0, V.getCoorSchool().getX(), V.getCoorSchool().getY(),
				V.getCoorSchool().getCapacity());

		std::vector<Stop> a;
		a.insert(a.begin() + 0, V.getCoorSchool());
		std::vector<Stop> b = V.getBusStops();
		//Set AllCustomer but not depot
		std::vector<Customer> allCustNotDepot;
		for (size_t i = 0; i < V.getBusStops().size(); i++) {
			Stop stop = V.getBusStops().at(i);
			Customer customer(i + 1, stop.getX(), stop.getY(),
					stop.getCapacity());
			allCustNotDepot.insert(allCustNotDepot.begin() + i, customer);
		}
		setAllCustNoDepot(allCustNotDepot);

		a.insert(a.end(), b.begin(), b.end());
		std::vector<Customer> allCustomers;
		for (size_t i = 0; i < a.size(); i++) {
			Stop stop = a.at(i);
			Customer customer(i, stop.getX(), stop.getY(), stop.getCapacity());
			allCustomers.insert(allCustomers.begin() + i, customer);
		}

		for (size_t i = 0; i < allCustomers.size(); i++) {
			Customer customer = allCustomers.at(i);
			cout << "(" << customer.getX() << ", " << customer.getY() << ", "
					<< customer.getDemand() << ")" << endl;
		}
		setDepot(depot);
		setAllCustomers(allCustomers);
		setK(V.getK());
		setC(V.getCk());
		setKmin(V.getKmin());
	} else {
		setNroCustomers(V.getBusAssigned().size() + 1);
		Customer depot(0, V.getCoorSchool().getX(), V.getCoorSchool().getY(),
				V.getCoorSchool().getCapacity());

		std::vector<Stop> a;
		a.insert(a.begin() + 0, V.getCoorSchool());
		std::vector<Stop> b = V.getBusAssigned();

		//Set AllCustomer but not depot
		std::vector<Customer> allCustNotDepot;
		for (size_t i = 0; i < V.getBusAssigned().size(); i++) {
			Stop stop = V.getBusAssigned().at(i);
			Customer customer(i + 1, stop.getX(), stop.getY(),
					stop.getCapacity());
			allCustNotDepot.insert(allCustNotDepot.begin() + i, customer);
		}
		setAllCustNoDepot(allCustNotDepot);

		a.insert(a.end(), b.begin(), b.end());
		std::vector<Customer> allCustomers;
		for (size_t i = 0; i < a.size(); i++) {
			Stop stop = a.at(i);
			Customer customer(i, stop.getX(), stop.getY(), stop.getCapacity());
			allCustomers.insert(allCustomers.begin() + i, customer);
		}
		cout << "List of customers! the first customert is the depot." << endl;
		for (size_t i = 0; i < allCustomers.size(); i++) {
			Customer customer = allCustomers.at(i);
			cout << "(" << customer.getX() << ", " << customer.getY() << ", "
					<< customer.getDemand() << ")" << endl;
		}

		x = new bool*[allCustomers.size()];
		for (size_t i = 0; i < allCustomers.size(); i++) {
			x[i] = new bool[allCustomers.size()];
		}

		for (size_t i = 0; i < allCustNotDepot.size(); i++) {
			for (size_t j = 0; j < allCustomers.size(); j++) {
				x[i][j] = false;
			}
		}

		setDepot(depot);
		setAllCustomers(allCustomers);
		setK(V.getK());
		setC(V.getCk());
		setKmin(V.getKmin());
	}

	//Initialization
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
	setS(s_cvpr);
	setX(x_cvpr);

	//Implementar
	/*
	 * So, for the second part you to create bus routes.
	 A constructive (simple) algorithm would be choose the nearest bus stop that does not exceed the capactity
	 When no more stops can be visited by the bus, it goes to the school
	 And a new route is started.
	 */

	std::vector<Customer> allCustomersAssignedToAmap;
	size_t totalCustomers = allCustomers.size();
	unsigned int counter = 0;
	std::vector<std::vector<Customer> > addRoutes;
	while (counter < totalCustomers) {
		cout << "size of the assigned map = "
				<< allCustomersAssignedToAmap.size() << endl;

		std::vector<Customer> customerUpdated = allCustNoDepot;
		map.insert(pair<int, Customer>(0, getDepot()));
		std::vector<Customer> route;
		int sumaDemand = 0;
		while (!map.empty()) {
			cout << "size of the assigned map = "
					<< allCustomersAssignedToAmap.size() << endl;
			int index = map.begin()->first;
			Customer pivot = map.begin()->second;
			map.erase(index);
			route.push_back(pivot);
			allCustomersAssignedToAmap.push_back(pivot);
			counter++;

			std::vector<Customer> succNodes = expand(customerUpdated, pivot);
			int k = 0;
			for (size_t i = 0; i < succNodes.size(); i++) {
				//Pruning
				int count = 0;
				while (k < 1 && count < 1) {
					Customer node = succNodes.at(i);
					std::map<int, Customer>::iterator mapIt = map.find(
							node.getId());
					if ((mapIt == map.end())
							&& (!isInFinalRoute(allCustomersAssignedToAmap,
									node))) {
						if (sumaDemand + node.getDemand() <= getC()) {
							sumaDemand = sumaDemand + node.getDemand();
							map.insert(pair<int, Customer>(node.getId(), node));
							k++;
						} else {
							//sumaDemand = 0;
						}
					} else {
						cout
								<< "Encuentra el elemento en el mapa y no hace nada"
								<< endl;
					}
					count++;
					cout << "Customer added to the map (" << node.getX() << ", "
							<< node.getY() << ")" << endl;
				}
			}
		}
		route.push_back(getDepot());
		addRoutes.push_back(route);
	}
	setAllRoutesGreedy(addRoutes);
	cout << "Routes generated greedy." << endl;
	for (size_t i = 0; i < addRoutes.size(); i++) {
		std::vector<Customer> route = addRoutes.at(i);
		cout << "----------------------------------" << endl;
		for (size_t j = 0; j < route.size(); j++) {
			Customer c = route.at(j);
			cout << c.getId() << ": (" << c.getX() << ", " << c.getY() << ")"
					<< endl;
		}
	}

}

void CVRP::savingAlgorithm() {

	//CREATE CONSTRUCTIVE - Saving Computation
	/**
	 * This algorithm naturally applies to problems for which
	 * the number of vehicles is a decision variable.
	 */
	std::vector<Saving> savingList;
	std::vector<Saving> savingPrev;
	int count1 = 0;
	unsigned int nro_customers = getAllCustNoDepot().size();
	std::vector<Customer> allCSaving = getAllCustNoDepot();
	std::vector<vector<Customer> > allRoutes = getAllRoutesGreedy();

	cout << "----------Customers and weigth----------------" << endl;
	for (unsigned int i = 0; i < getAllCustNoDepot().size(); i++) {
		Customer c = getAllCustNoDepot().at(i);
		cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getDemand()
				<< ")" << endl;
	}
	cout << "----------------------------------------------" << endl;
	for (unsigned int i = 0; i < nro_customers; i++) {
		Customer customer = allCSaving.at(i);
		for (unsigned int j = 0; j < nro_customers; j++) {
			//if (i != j) {
			if (i < j) {
				Customer pivot = allCSaving.at(j);
				double d1 = getD()[i][0];
				double d2 = getD()[0][j];
				double d3 = getD()[i][j];

				getS()[i][j] = d1 + d2 - d3;
				Saving save(customer, pivot, getS()[i][j]);
				savingList.insert(savingList.begin() + count1, save);
				count1++;
			}
			//}
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
	int m = 0;
	for (size_t i = 0; i < savingList.size(); i++) {
		Saving save = savingList.at(i);
		Customer c1 = save.getSavingC1();
		Customer c2 = save.getSavingC2();
		double peso = save.getSavingPeso();
		cout << "i = (" << c1.getX() << ", " << c1.getY() << ") j = ("
				<< c2.getX() << ", " << c2.getY() << ") peso = " << peso
				<< endl;
	}

	cout << "Insertion." << endl;
	std::vector<std::vector<Customer> > routes;
	for (unsigned int i = 0; i < nro_customers; i++) {
		Customer customer = getAllCustNoDepot().at(i);
		//Create routes
		std::vector<Customer> route;
		route.insert(route.begin() + 0, getDepot());
		route.insert(route.begin() + 1, customer);
		route.insert(route.begin() + 2, getDepot());
		routes.insert(routes.begin() + m, route);
		m++;
		route.clear();
	}

	//Routes
	cout << "Print route for each new route:" << endl;
	for (size_t i = 0; i < routes.size(); i++) {
		std::vector<Customer> customers = routes.at(i);
		cout << "route #" << i << endl;
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		cout << "\n";
	}

	//Best feasible merge
	//1.- look for 0, j
	/*
	 * Step 2. Best feasible merge (Parallel version)
	 Starting from the top of the savings list, execute the following:
	 Given a saving sij, determine whether there exist two routes that can
	 feasibility be merged:
	 One starting with (0,j)
	 One ending with (i,0)
	 Combine these two routes by deleting (0,j) and (i,0) and introducing (i,j).
	 *
	 */

	cout << "=========================================================="
			<< endl;
	cout << "Starting saving List process" << endl;

	for (size_t i = 0; i < savingList.size(); i++) {
		bool firstCondition = false;
		unsigned int route_number = 0;
		bool secondCondition = false;
		unsigned int route_number2 = 0;

		Saving saving = savingList.at(i);
		Customer customer1 = saving.getSavingC1();
		Customer customer2 = saving.getSavingC2();

		Customer firstElement;
		Customer secondElement;
		cout << "=======Print route each time new SavingList is used========="
				<< endl;
		cout << "For saving customer1 = (" << customer1.getX() << ", "
				<< customer1.getY() << ")" << endl;
		cout << "For saving customer2 = (" << customer2.getX() << ", "
				<< customer2.getY() << ")" << endl;
		for (size_t i = 0; i < routes.size(); i++) {
			std::vector<Customer> customers = routes.at(i);
			cout << "route #" << i << endl;
			for (size_t j = 0; j < customers.size(); j++) {
				Customer c = customers.at(j);
				cout << "(" << c.getX() << ", " << c.getY() << ") - ";
			}
			cout << "\n";
		}

		//First Condition
		for (size_t j = 0; j < routes.size(); j++) {
			std::vector<Customer> customersRoutes = routes.at(j);

			bool c1IsFound = false;
			bool depotIsFound = false;
			unsigned int pivot = 0;

			for (size_t k = 0; k < customersRoutes.size(); k++) {

				Customer c = customersRoutes.at(k);
				if (compareCustomers(c, customer1)) {
					c1IsFound = true;
					pivot = k;
				}
				if (c1IsFound && (pivot + 1 == k)) {
					if (compareCustomers(getDepot(), c)) {
						depotIsFound = true;
						firstElement = customersRoutes.at(pivot);
						cout << "first Element = (" << firstElement.getX()
								<< ", " << firstElement.getY() << ")" << endl;
						route_number = j;
					}
				}
			}
			if (c1IsFound && depotIsFound) {
				firstCondition = true;
			} else {
				cout << "Not" << endl;
			}

		}
		//Second condition
		for (size_t j = 0; j < routes.size(); j++) {
			std::vector<Customer> customersRoutes = routes.at(j);
			bool c2IsFound = false;
			bool depot2IsFound = false;
			unsigned int pivot2 = 0;

			for (size_t k = 0; k < customersRoutes.size(); k++) {
				Customer c = customersRoutes.at(k);

				if (compareCustomers(getDepot(), c)) {
					depot2IsFound = true;
					pivot2 = k;
				}
				if (depot2IsFound && (pivot2 + 1 == k)) {
					if (compareCustomers(c, customer2)) {
						c2IsFound = true;
						secondElement = customersRoutes.at(pivot2 + 1);
						cout << "second Element = (" << secondElement.getX()
								<< ", " << secondElement.getY() << ")" << endl;
						route_number2 = j;
					}
				}
			}

			if (depot2IsFound && c2IsFound) {
				secondCondition = true;
			} else {
				cout << "Not2" << endl;
			}

		}
		if (firstCondition && secondCondition) {
			if (route_number != route_number2) {
				cout << "route 1 = " << route_number << endl;
				cout << "route 2 = " << route_number2 << endl;

				std::vector<Customer> route1 = routes.at(route_number);
				std::vector<Customer> route2 = routes.at(route_number2);
				int demandRoute1 = getRouteDemand(route1);
				int demandRoute2 = getRouteDemand(route2);
				int capacidade = getC();
				if (demandRoute1 + demandRoute2 <= capacidade) {
					for (size_t r = 0; r < route1.size(); r++) {
						Customer c = route1.at(r);
						cout << "(" << c.getX() << ", " << c.getY() << ") -";
					}
					cout << endl;
					//This operation is for: i(Customer1)->depot
					//remote the depot
					unsigned int depotIndex = route1.size() - 1;
					route1.erase(route1.begin() + depotIndex);
					cout << "After remove last i->depot." << endl;
					for (size_t r = 0; r < route1.size(); r++) {
						Customer c = route1.at(r);
						cout << "(" << c.getX() << ", " << c.getY() << ") -";
					}
					cout << endl;

					for (size_t r = 0; r < route2.size(); r++) {
						Customer c = route2.at(r);
						cout << "(" << c.getX() << ", " << c.getY() << ") -";
					}
					cout << endl;
					//This operation is for: depot->j(Customer2)
					unsigned int depotIndex2 = 0;
					route2.erase(route2.begin() + depotIndex2);
					cout << "After remove last depot->j." << endl;
					for (size_t r = 0; r < route2.size(); r++) {
						Customer c = route2.at(r);
						cout << "(" << c.getX() << ", " << c.getY() << ") -";
					}
					cout << endl;

					route1.insert(route1.end(), route2.begin(), route2.end());
					cout << "Nueva ruta generada por las rutas " << route_number
							<< " y " << route_number2 << endl;
					for (size_t l = 0; l < route1.size(); l++) {
						Customer customer = route1.at(l);
						cout << "(" << customer.getX() << ", "
								<< customer.getY() << ") - ";
					}
					//Take care when you remove a element from a vector. The update is automatically
					if (route_number < route_number2) {
						routes.erase(routes.begin() + route_number);
						routes.erase(routes.begin() + route_number2 - 1);
					} else {
						routes.erase(routes.begin() + route_number);
						routes.erase(routes.begin() + route_number2);
					}

					cout << "After remove the routes " << route_number
							<< " and " << route_number2 << endl;
					for (size_t i = 0; i < routes.size(); i++) {
						std::vector<Customer> customers = routes.at(i);
						cout << "route #" << i << endl;
						for (size_t j = 0; j < customers.size(); j++) {
							Customer c = customers.at(j);
							cout << "(" << c.getX() << ", " << c.getY()
									<< ") - ";
						}
						cout << "\n";
					}

					routes.push_back(route1);
					cout << "--------------------------------" << endl;
					cout << "after add the new  route: FINAL merge." << endl;
					for (size_t i = 0; i < routes.size(); i++) {
						std::vector<Customer> customers = routes.at(i);
						cout << "route #" << i << endl;
						for (size_t j = 0; j < customers.size(); j++) {
							Customer c = customers.at(j);
							cout << "(" << c.getX() << ", " << c.getY()
									<< ") - ";
						}
						cout << "\n";
					}
					cout << "Number of routes after merge. = " << routes.size()
							<< endl;
					cout << "Customer i = (" << firstElement.getX() << ", "
							<< firstElement.getY() << ")" << endl;
					cout << "Customer j = (" << secondElement.getX() << ", "
							<< secondElement.getY() << ")" << endl;

					cout << "------------end--------------------" << endl;

				}
			}
			cout << "=======end saving element from the list=========" << endl;
		} else {
			//Not to merge
		}
	}
	setAllRoutesSaving(routes);
	//Routes
	cout << "Print routes after the first merge process:" << endl;
	for (size_t i = 0; i < routes.size(); i++) {
		std::vector<Customer> customers = routes.at(i);
		cout << "route #" << i << endl;
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		cout << "\n";
	}

}

int CVRP::getRouteDemand(std::vector<Customer> customers) {
	int totalDemand = 0;
	for (size_t i = 0; i < customers.size(); i++) {
		Customer customer = customers.at(i);
		totalDemand = totalDemand + customer.getDemand();
	}
	return totalDemand;
}

std::vector<Customer> CVRP::expand(std::vector<Customer> allCustomers,
		Customer customer) {
	std::vector<Customer> result;
	priority_queue<CustomerDD, vector<CustomerDD>, CompareCustomerSDD> pq;
	for (size_t j = 0; j < allCustomers.size(); j++) {
		Customer pivot = allCustomers.at(j);

		double distance = getDistanceIJ(customer, pivot);
		int demand = pivot.getDemand();
		CustomerDD c = { pivot, distance, demand };
		pq.push(c);
	}

	int k = 0;
	cout << "---------------" << endl;
	while (!pq.empty()) {
		CustomerDD t = pq.top();
		result.insert(result.begin() + k, t.c);
		cout << "id = " << t.c.getId() << endl;
		cout << "(" << t.c.getX() << ", " << t.c.getY() << ")" << endl;
		cout << "distance = " << t.distance << endl;
		cout << "demand = " << t.demand << endl;
		cout << "--------------------" << endl;
		pq.pop();
		k++;
	}

	for (size_t k = 0; k < result.size(); k++) {
		Customer c = result.at(k);
		cout << "(" << c.getX() << ", " << c.getY() << ") demand = "
				<< c.getDemand() << endl;
	}

	return result;
}

bool CVRP::isInFinalRoute(std::vector<Customer> customers, Customer customer) {
	for (size_t i = 0; i < customers.size(); i++) {
		Customer pivot = customers.at(i);
		if (compareCustomers(customer, pivot)) {
			return true;
		}
	}
	return false;
}

Customer CVRP::getCustomerLessDistance(std::vector<Customer> customers,
		Customer pivot) {
	double menor = 999;
	Customer result = pivot;
	for (size_t i = 0; i < customers.size(); i++) {
		Customer customer = customers.at(i);
		double distance = getDistanceIJ(pivot, customer);
		if (distance < menor) {
			menor = distance;
			result = customer;
		}
	}
	return result;
}

Customer CVRP::getCustomerLessDemand(std::vector<Customer> customers) {
	int menor = 999;
	Customer cmenor;
	for (size_t i = 0; i < customers.size(); i++) {
		Customer c = customers.at(i);
		if (c.getDemand() < menor) {
			menor = c.getDemand();
			cmenor = c;
		}
	}
	return cmenor;
}

void CVRP::initialSolutionReport() {

	ofstream result;
	char output[] =
			"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\results\\is\\results.txt";

	result.open(output);
	result
			<< "\t\tInitial Solutions generated by Greedy and Saving Algorithms.\n";
	result << "\n";
	result << "\t\tGreedy Algorithm.\n";
	result << "\n";
	std::vector<std::vector<Customer> > allRoutesGreedy = getAllRoutesGreedy();
	cout << "Print routes generated by greedy algorithm." << endl;
	for (size_t i = 0; i < allRoutesGreedy.size(); i++) {
		std::vector<Customer> customers = allRoutesGreedy.at(i);
		cout << "route #" << i << endl;
		result << "route # " << i << ":\n";
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			result << "(" << c.getX() << ", " << c.getY() << ") ->";
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		result << "\n";
		cout << "\n";
	}
	result << "\n";
	cout << "--------------------------------------------" << endl;
	std::vector<std::vector<Customer> > allRoutesSaving = getAllRoutesSaving();
	cout << "Print routes generated by saving algorithm." << endl;
	result << "\t\tSaving Algorithm.\n";
	result << "\n";
	for (size_t i = 0; i < allRoutesSaving.size(); i++) {
		std::vector<Customer> customers = allRoutesSaving.at(i);
		cout << "route #" << i << endl;
		result << "route # " << i << ":\n";
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			result << "(" << c.getX() << ", " << c.getY() << ") ->";
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		result << "\n";
		cout << "\n";
	}
	cout << "--------------------------------------------" << endl;
	result.close();
}

double CVRP::twoOptRoute(std::vector<std::vector<Customer> > routes) {
	double sumAllFO = 0.0;
	for (unsigned int i = 0; i < routes.size(); i++) {
		std::vector<Customer> route = routes.at(i);
		double routeFO = getFO(route);
		std::vector<Customer> newRoute;
		std::vector<Customer> bestRoute = route;
		double bestFO = routeFO;
		/*
		 cout << "--------route#" << i << "-----------------" << endl;
		 for (size_t m = 0; m < bestRoute.size(); m++) {
		 Customer c = bestRoute.at(m);
		 cout << "(" << c.getX() << ", " << c.getY() << ")-> ";
		 }
		 cout << "\n";
		 cout << cout << "-------------------------" << endl;
		 */
		for (unsigned int j = 0; j < bestRoute.size() - 1; j++) {
			for (unsigned int k = 0; k < bestRoute.size() - 1; k++) {
				newRoute = doTwoOpt(j, k, bestRoute);
				/*
				 cout << "----new-route-generated#-----------------" << endl;
				 for (size_t m = 0; m < newRoute.size(); m++) {
				 Customer c = newRoute.at(m);
				 cout << "(" << c.getX() << ", " << c.getY() << ")-> ";
				 }
				 cout << "\n";
				 cout << cout << "-------------------------" << endl;
				 */
				double newFO = getFO(newRoute);
				if (newFO < bestFO) {
					bestFO = newFO;
					bestRoute = newRoute;
				}
			}
		}
		sumAllFO = sumAllFO + bestFO;
		//cout << "bestFO = " << bestFO << endl;
	}

	return sumAllFO;
}

double CVRP::getFO(std::vector<Customer> route) {
	Route r;
	r.setRoute(route);
	double cost = r.getCost();
	return cost;
}

std::vector<Customer> CVRP::doTwoOpt(int c1, int c2,
		std::vector<Customer> route) {
	int size = route.size();
	Customer* newRoute = new Customer[size];
	std::vector<Customer> result;
	int temp = c2;
	for (int i = 0; i <= c1; i++) {
		newRoute[i] = route[i];
	}

	for (int i = c1; i <= c2; i++) {
		if (i == 0) {
			newRoute[i] = route[i];
		} else {
			newRoute[i] = route[temp];
			temp = temp - 1;
		}
	}

	for (int i = c2 + 1; i < size; i++) {
		newRoute[i] = route[i];
	}

	for (int i = 0; i < size; i++) {
		result.insert(result.begin() + i, newRoute[i]);
	}

	return result;
}

std::vector<Customer> CVRP::removeCustomerFromRoute(
		std::vector<Customer> customers, Customer customer) {
	for (size_t i = 0; i < customers.size(); i++) {
		Customer c = customers.at(i);
		if (compareCustomers(c, customer)) {
			customers.erase(customers.begin() + i);
		}
	}
	return customers;
}

double CVRP::ILSInTheRoute(std::vector<std::vector<Customer> > routes) {
	int maxIter = 20;
	std::vector<std::vector<Customer> > SCero = routes;
	std::vector<std::vector<Customer> > S = twoOptRouteILS(SCero);
	double Svalue = getFO(S);
	int iter = 0;
	int permutationNumber = 3;
	do {
		iter = iter + 1;
		//Perturbation
		std::vector<std::vector<Customer> > SPrima = perturbationInTheRoute(S,
				permutationNumber);
		std::vector<std::vector<Customer> > STwoPrima = twoOptRouteILS(SPrima);
		double STwoPrimaValue = getFO(STwoPrima);
		if (STwoPrimaValue < Svalue) {
			Svalue = STwoPrimaValue;
		}
	} while (iter < maxIter);
	return Svalue;
}

double CVRP::ILSBetweenRoutes(std::vector<std::vector<Customer> > routes) {
	int maxIter = 5;
	std::vector<std::vector<Customer> > SCero = routes;
	std::vector<std::vector<Customer> > S = exchangingBetweenRoutesILS(SCero);
	double Svalue = getFO(S);
	double iter = 0;
	int permutationNumber = 2;
	std::vector<std::vector<Customer> > allBestRoutes = routes;
	do {
		iter = iter + 1;
		//Pertubation
		std::vector<std::vector<Customer> > SPrima = perturbationBetweenRoutes(
				S, permutationNumber);

		std::vector<std::vector<Customer> > STwoPrima =
				exchangingBetweenRoutesILS(SPrima);
		double STwoPrimaValue = getFO(STwoPrima);
		if (STwoPrimaValue < Svalue) {
			Svalue = STwoPrimaValue;
			allBestRoutes = STwoPrima;
		}
	} while (iter < maxIter);
	return Svalue;
}

std::vector<std::vector<Customer> > CVRP::perturbationInTheRoute(
		std::vector<std::vector<Customer> > S, int n) {
	std::vector<std::vector<Customer> > result;

	int size = S.size();
	int count = 0;

	do {
		for (int i = 0; i < size; i++) {
			int r1 = 0;
			int r2 = 0;
			int sizeMax = S.at(i).size();
			srand(time(NULL));
			r1 = rand() % sizeMax;
			r2 = rand() % sizeMax;

			if (sizeMax == 3) {
				r1 = 1;
				r2 = 1;
			} else {
				while (r1 == r2) {
					r1 = rand() % sizeMax;
					r2 = rand() % sizeMax;
				}

			}
			S.at(i) = doTwoOpt(r1, r2, S.at(i));
		}
		count = count + 1;
	} while (count < n);

	return S;
}

std::vector<std::vector<Customer> > CVRP::perturbationBetweenRoutes(
		std::vector<std::vector<Customer> > S, int n) {

	int size = S.size();
	int count = 0;

	do {
		std::vector<std::vector<Customer> > result;

		for (int i = 0; i < size; i++) {
			int r1 = 0;
			int r2 = 0;
			srand(time(NULL));
			r1 = rand() % size;
			r2 = rand() % size;

			while (r1 == r2) {
				r1 = rand() % size;
				r2 = rand() % size;
			}

			vector<Customer> route = S.at(r1);
			vector<Customer> pivot = S.at(r2);
			result = doExchangingtRoutes(route, pivot);

			route = result.at(0);
			pivot = result.at(1);
			S.at(r1) = result.at(0);
			S.at(r2) = result.at(1);

		}
		count = count + 1;
	} while (count < n);

	return S;
}

std::vector<std::vector<Customer> > CVRP::twoOptRouteILS(
		std::vector<std::vector<Customer> > routes) {
	double sumAllFO = 0.0;
	std::vector<std::vector<Customer> > allBestRoutes;
	for (unsigned int i = 0; i < routes.size(); i++) {
		std::vector<Customer> route = routes.at(i);
		double routeFO = getFO(route);
		std::vector<Customer> newRoute;
		std::vector<Customer> bestRoute = route;
		double bestFO = routeFO;

		for (unsigned int j = 0; j < bestRoute.size() - 1; j++) {
			for (unsigned int k = 0; k < bestRoute.size() - 1; k++) {
				newRoute = doTwoOpt(j, k, bestRoute);

				double newFO = getFO(newRoute);
				if (newFO < bestFO) {
					bestFO = newFO;
					bestRoute = newRoute;
				}
			}
		}
		allBestRoutes.insert(allBestRoutes.begin() + i, bestRoute);
		sumAllFO = sumAllFO + bestFO;
		//cout << "bestFO = " << bestFO << endl;
	}

	return allBestRoutes;
}

std::vector<std::vector<Customer> > CVRP::exchangingBetweenRoutesILS(
		std::vector<std::vector<Customer> > routes) {

	std::vector<std::vector<Customer> > result;
	std::vector<std::vector<Customer> > allBestRoutes = routes;
	double bestSumRoutes = getFO(routes);
	std::vector<Customer> bestRoute;
	std::vector<Customer> bestPivot;
	for (unsigned int i = 0; i < routes.size(); i++) {
		//std::vector<std::vector<Customer> > AllRoutes = routes;
		std::vector<Customer> route = routes.at(i);
		for (unsigned int j = 0; j < routes.size(); j++) {
			std::vector<Customer> pivot = routes.at(j);
			if (i != j) {
				result = doExchangingtRoutes(route, pivot);

				route = result.at(0);
				pivot = result.at(1);
				routes.at(i) = result.at(0);
				routes.at(j) = result.at(1);

				double newSumRoutes = getFO(routes);
				if (newSumRoutes < bestSumRoutes) {
					bestSumRoutes = newSumRoutes;
					bestRoute = route;
					bestPivot = pivot;
					allBestRoutes = routes;
				}
			}
		}
	}
	return allBestRoutes;
}

double CVRP::exchangingBetweenRoutes(
		std::vector<std::vector<Customer> > routes) {
//printRoutes(routes);
	std::vector<std::vector<Customer> > result;
	std::vector<std::vector<Customer> > allBestRoutes;
	double bestSumRoutes = getFO(routes);
	std::vector<Customer> bestRoute;
	std::vector<Customer> bestPivot;
	for (unsigned int i = 0; i < routes.size(); i++) {
		//std::vector<std::vector<Customer> > AllRoutes = routes;
		std::vector<Customer> route = routes.at(i);
		for (unsigned int j = 0; j < routes.size(); j++) {
			std::vector<Customer> pivot = routes.at(j);
			if (i != j) {
				//Remove from the routes the routes that are being changed.
				/*if (i < j) {
				 AllRoutes.erase(AllRoutes.begin() + i);
				 AllRoutes.erase(AllRoutes.begin() + (j - 1));
				 } else {
				 AllRoutes.erase(AllRoutes.begin() + i);
				 AllRoutes.erase(AllRoutes.begin() + j);
				 }*/

				//printRoute(route);
				//printRoute(pivot);
				result = doExchangingtRoutes(route, pivot);
				//printRoute(result.at(0));
				//printRoute(result.at(1));
				route = result.at(0);
				pivot = result.at(1);
				routes.at(i) = result.at(0);
				routes.at(j) = result.at(1);

				//cout << "---Print after doTwoOptRoutes---" << endl;
				//printRoutes(result);
				//cout << "---end Print after doTwoOptRoutes---" << endl;
				//Insert the routes that were removed, but now they are modified
				/*AllRoutes.insert(AllRoutes.begin() + AllRoutes.size(),
				 result.at(0));
				 AllRoutes.insert(AllRoutes.begin() + AllRoutes.size(),
				 result.at(1));
				 */
				double newSumRoutes = getFO(routes);
				if (newSumRoutes < bestSumRoutes) {
					bestSumRoutes = newSumRoutes;
					bestRoute = route;
					bestPivot = pivot;
					allBestRoutes = routes;
				}
			}
		}
	}

	return bestSumRoutes;
}

std::vector<std::vector<Customer> > CVRP::doExchangingtRoutes(
		std::vector<Customer> route, std::vector<Customer> pivot) {
	std::vector<std::vector<Customer> > result;
	double bestSumRoutes = getFO(route) + getFO(pivot);
	std::vector<Customer> bestRoute = route;
	std::vector<Customer> bestPivot = pivot;
	for (unsigned int i = 1; i < route.size() - 1; i++) {
		Customer c1 = route.at(i);
		for (unsigned int j = 1; j < pivot.size() - 1; j++) {
			Customer c2 = pivot.at(j);
			route.at(i) = c2;
			pivot.at(j) = c1;
			//swapCustomers(c1, c2);
			//printRoute(route);
			//printRoute(pivot);
			int route1Demand = getRouteDemand(route);
			int route2Demand = getRouteDemand(pivot);
			int capacidade = getC();
			if ((route1Demand <= capacidade) && (route2Demand <= capacidade)) {
				double newSumRoutes = getFO(route) + getFO(pivot);
				if (newSumRoutes < bestSumRoutes) {
					bestSumRoutes = newSumRoutes;
					bestRoute = route;
					bestPivot = pivot;
				}
			}
			route.at(i) = c1;
			pivot.at(j) = c2;
			//cout << "Return to the same route and pivot." << endl;
			//printRoute(route);
			//printRoute(pivot);
			//cout << "end return to the same route and pivot." << endl;
		}
	}
	result.insert(result.begin() + 0, bestRoute);
	result.insert(result.begin() + 1, bestPivot);

	return result;
}

void CVRP::printRoute(std::vector<Customer> route) {
	cout << "------------Route-----------" << endl;
	for (unsigned i = 0; i < route.size(); i++) {
		Customer c = route.at(i);
		cout << "(" << c.getX() << ", " << c.getY() << ") -> ";
	}
	cout << "\n\n";
	cout << "----------End Route-----------" << endl;
}

void CVRP::printRoutes(std::vector<std::vector<Customer> > routes) {
	cout << "-------------Routes------------" << endl;
	for (unsigned i = 0; i < routes.size(); i++) {
		std::vector<Customer> route = routes.at(i);
		for (unsigned j = 0; j < route.size(); j++) {
			Customer c = route.at(j);
			cout << "(" << c.getX() << ", " << c.getY() << ") -> ";
		}
		cout << "\n";
	}
	cout << "------------End Routes-----------" << endl;
}

void CVRP::swapCustomers(Customer &c1, Customer &c2) {
	Customer temp;
	temp = c1;
	c1 = c2;
	c2 = temp;
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
		//Set AllCustomer but not depot
		std::vector<Customer> allCustNotDepot;
		for (size_t i = 0; i < V.getBusStops().size(); i++) {
			Stop stop = V.getBusStops().at(i);
			Customer customer(stop.getX(), stop.getY(), stop.getCapacity());
			allCustNotDepot.insert(allCustNotDepot.begin() + i, customer);
		}
		setAllCustNoDepot(allCustNotDepot);

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
		setDepot(depot);
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

		//Set AllCustomer but not depot
		std::vector<Customer> allCustNotDepot;
		for (size_t i = 0; i < V.getBusAssigned().size(); i++) {
			Stop stop = V.getBusAssigned().at(i);
			Customer customer(stop.getX(), stop.getY(), stop.getCapacity());
			allCustNotDepot.insert(allCustNotDepot.begin() + i, customer);
		}
		setAllCustNoDepot(allCustNotDepot);

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
		setDepot(depot);
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
	std::vector<Customer> allCSaving = getAllCustNoDepot();

	for (int i = 0; i < nro_buses; i++) {
		Customer customer = allCSaving.at(i);
		for (int j = 0; j < nro_buses; j++) {
			if (i != j) {
				Customer pivot = allCSaving.at(j);
				double d1 = d_cvpr[i][0];
				double d2 = d_cvpr[0][j];
				double d3 = d_cvpr[i][j];

				s_cvpr[i][j] = d1 + d2 - d3;
				Saving save(customer, pivot, s_cvpr[i][j]);
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
	int m = 0;
	for (size_t i = 0; i < savingList.size(); i++) {
		Saving save = savingList.at(i);
		Customer c1 = save.getSavingC1();
		Customer c2 = save.getSavingC2();
		double peso = save.getSavingPeso();
		cout << "i = (" << c1.getX() << ", " << c1.getY() << ") j = ("
				<< c2.getX() << ", " << c2.getY() << ") peso = " << peso
				<< endl;
	}
	cout << "Insertion." << endl;
	std::vector<std::vector<Customer> > routes;
	for (int i = 0; i < nro_buses; i++) {
		Customer customer = getAllCustNoDepot().at(i);
		//Create routes
		std::vector<Customer> route;
		route.insert(route.begin() + 0, getDepot());
		route.insert(route.begin() + 1, customer);
		route.insert(route.begin() + 2, getDepot());
		routes.insert(routes.begin() + m, route);
		m++;
		route.clear();

	}

//Routes
	cout << "Print route for each new route:" << endl;
	for (size_t i = 0; i < routes.size(); i++) {
		std::vector<Customer> customers = routes.at(i);
		cout << "route #" << i << endl;
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		cout << "\n";
	}

//Best feasible merge
//1.- look for 0, j
	/*
	 * Step 2. Best feasible merge (Parallel version)
	 Starting from the top of the savings list, execute the following:
	 Given a saving sij, determine whether there exist two routes that can
	 feasibility be merged:
	 One starting with (0,j)
	 One ending with (i,0)
	 Combine these two routes by deleting (0,j) and (i,0) and introducing (i,j).
	 *
	 */
	cout << "=========================================================="
			<< endl;
	cout << "Starting saving List process" << endl;
	for (size_t i = 0; i < savingList.size(); i++) {
		bool firstCondition = false;
		unsigned int route_number = 0;
		bool secondCondition = false;
		unsigned int route_number2 = 0;

		Saving saving = savingList.at(i);
		Customer customer1 = saving.getSavingC1();
		Customer customer2 = saving.getSavingC2();
		Customer firstElement;
		Customer secondElement;
		cout << "=======Print route each time new SavingList is used========="
				<< endl;
		cout << "For saving customer1 = (" << customer1.getX() << ", "
				<< customer1.getY() << ")" << endl;
		cout << "For saving customer2 = (" << customer2.getX() << ", "
				<< customer2.getY() << ")" << endl;
		for (size_t i = 0; i < routes.size(); i++) {
			std::vector<Customer> customers = routes.at(i);
			cout << "route #" << i << endl;
			for (size_t j = 0; j < customers.size(); j++) {
				Customer c = customers.at(j);
				cout << "(" << c.getX() << ", " << c.getY() << ") - ";
			}
			cout << "\n";
		}

		//First Condition
		for (size_t j = 0; j < routes.size(); j++) {
			std::vector<Customer> customersRoutes = routes.at(j);

			bool c1IsFound = false;
			bool depotIsFound = false;
			unsigned int pivot = 0;

			for (size_t k = 0; k < customersRoutes.size(); k++) {

				Customer c = customersRoutes.at(k);
				if (compareCustomers(c, customer1)) {
					c1IsFound = true;
					pivot = k;
				}
				if (c1IsFound && (pivot + 1 == k)) {
					if (compareCustomers(getDepot(), c)) {
						depotIsFound = true;
						firstElement = customersRoutes.at(pivot);
						cout << "first Element = (" << firstElement.getX()
								<< ", " << firstElement.getY() << ")" << endl;
						route_number = j;
					}
				}
			}
			if (c1IsFound && depotIsFound) {
				firstCondition = true;
			} else {
				cout << "Not" << endl;
			}

		}
		//Second condition
		for (size_t j = 0; j < routes.size(); j++) {
			std::vector<Customer> customersRoutes = routes.at(j);
			bool c2IsFound = false;
			bool depot2IsFound = false;
			unsigned int pivot2 = 0;

			for (size_t k = 0; k < customersRoutes.size(); k++) {
				Customer c = customersRoutes.at(k);

				if (compareCustomers(getDepot(), c)) {
					depot2IsFound = true;
					pivot2 = k;
				}
				if (depot2IsFound && (pivot2 + 1 == k)) {
					if (compareCustomers(c, customer2)) {
						c2IsFound = true;
						secondElement = customersRoutes.at(pivot2 + 1);
						cout << "second Element = (" << secondElement.getX()
								<< ", " << secondElement.getY() << ")" << endl;
						route_number2 = j;
					}
				}
			}

			if (depot2IsFound && c2IsFound) {
				secondCondition = true;
			} else {
				cout << "Not2" << endl;
			}

		}
		if (firstCondition && secondCondition) {
			if (route_number != route_number2) {
				cout << "route 1 = " << route_number << endl;
				cout << "route 2 = " << route_number2 << endl;
				cout << "first Element = (" << firstElement.getX() << ", "
						<< firstElement.getY() << ")" << endl;
				cout << "second Element = (" << secondElement.getX() << ", "
						<< secondElement.getY() << ")" << endl;
				cout << "soy sensacional" << endl;
				std::vector<Customer> route1 = routes.at(route_number);
				for (size_t r = 0; r < route1.size(); r++) {
					Customer c = route1.at(r);
					cout << "(" << c.getX() << ", " << c.getY() << ") -";
				}
				cout << endl;
				//remote the depot
				for (size_t r = 0; r < route1.size(); r++) {
					Customer customer = route1.at(r);
					if (compareCustomers(customer, getDepot())) {
						route1.erase(route1.begin() + r);
					}
				}
				std::vector<Customer> route2 = routes.at(route_number2);
				for (size_t r = 0; r < route2.size(); r++) {
					Customer c = route2.at(r);
					cout << "(" << c.getX() << ", " << c.getY() << ") -";
				}
				cout << endl;
				for (size_t r = 0; r < route2.size(); r++) {
					Customer customer = route2.at(r);
					if (compareCustomers(customer, getDepot())) {
						route2.erase(route2.begin() + r);
					}
				}
				route1.insert(route1.end(), route2.begin(), route2.end());
				cout << "Nueva ruta generada por las rutas " << route_number
						<< " y " << route_number2 << endl;
				for (size_t l = 0; l < route1.size(); l++) {
					Customer customer = route1.at(l);
					cout << "(" << customer.getX() << ", " << customer.getY()
							<< ") - ";
				}
				routes.erase(routes.begin() + route_number);
				routes.erase(routes.begin() + route_number2 - 1);

				cout << "After remove the routes " << route_number << " and "
						<< route_number2 << endl;
				for (size_t i = 0; i < routes.size(); i++) {
					std::vector<Customer> customers = routes.at(i);
					cout << "route #" << i << endl;
					for (size_t j = 0; j < customers.size(); j++) {
						Customer c = customers.at(j);
						cout << "(" << c.getX() << ", " << c.getY() << ") - ";
					}
					cout << "\n";
				}

				routes.push_back(route1);
				cout << "after add the new  route merged." << endl;
				for (size_t i = 0; i < routes.size(); i++) {
					std::vector<Customer> customers = routes.at(i);
					cout << "route #" << i << endl;
					for (size_t j = 0; j < customers.size(); j++) {
						Customer c = customers.at(j);
						cout << "(" << c.getX() << ", " << c.getY() << ") - ";
					}
					cout << "\n";
				}
				cout << "routes.size() = " << routes.size() << endl;

			}
			cout << "=======end saving element from the list=========" << endl;
		} else {
			//Not to merge
		}
	}

//Route Extension
//Routes
	cout << "Print routes after the first merge process:" << endl;
	for (size_t i = 0; i < routes.size(); i++) {
		std::vector<Customer> customers = routes.at(i);
		cout << "route #" << i << endl;
		for (size_t j = 0; j < customers.size(); j++) {
			Customer c = customers.at(j);
			cout << "(" << c.getX() << ", " << c.getY() << ") - ";
		}
		cout << "\n";
	}

}

double CVRP::getFO(std::vector<std::vector<Customer> > allRoutes) {
	double results = 0;
	for (size_t i = 0; i < allRoutes.size(); i++) {
		std::vector<Customer> route = allRoutes.at(i);
		Route r;
		r.setRoute(route);
		double cost = r.getCost();
		results = results + cost;
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

bool CVRP::compareCustomers(Customer c1, Customer c2) {
	if ((c1.getX() == c2.getX()) && (c1.getY() == c2.getY())) {
		return true;
	}
	return false;
}

