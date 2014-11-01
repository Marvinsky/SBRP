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

void CVRP::init2(VRP V) {
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
	cout << "Routes generated greedy." << endl;
	for (size_t i = 0; i < addRoutes.size(); i++) {
		std::vector<Customer> route = addRoutes.at(i);
		for (size_t j = 0; j < route.size(); j++) {
			Customer c = route.at(j);
			cout << c.getId() << ": (" << c.getX() << ", " << c.getY() << ")"
					<< endl;
		}
	}

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

/*
 std::vector<std::vector<Customer> > CVRP::modify(
 std::vector<std::vector<Customer> > vCustomers, Customer c1,
 Customer c2, int r1, int r2) {

 std::vector<Customer> route1 = vCustomers.at(r1);
 std::vector<Customer> route2 = vCustomers.at(r2);
 route1.insert(route1.end(), route2.begin(), route2.end());

 for (size_t i = 0; i < route1.size(); i++) {
 Customer customer = route1.at(i);
 cout << "(" << customer.getX() << ", " << customer.getY() << ")"
 << endl;
 }
 }
 */
bool CVRP::validarPrimeraCondicion(Customer depot, Customer c1) {
	return false;
}

bool CVRP::validarSegundaCondicion(Customer c1, Customer depot) {
	return false;
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

bool CVRP::compareCustomers(Customer c1, Customer c2) {
	if ((c1.getX() == c2.getX()) && (c1.getY() == c2.getY())) {
		return true;
	}
	return false;
}
