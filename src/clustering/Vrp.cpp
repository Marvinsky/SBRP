/*
 * Vrp.cpp
 *
 *  Created on: 15/10/2014
 *      Author: Marvin
 */

#include "Vrp.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

int VRP::getNroStops() {
	return this->nroStops;
}

void VRP::setNroStops(int stops) {
	this->nroStops = stops;
}

int VRP::getNroStudents() {
	return this->nroStudents;
}

void VRP::setNroStudents(int students) {
	this->nroStudents = students;
}

int** VRP::getCoordStops() {
	return this->coordStops;
}

void VRP::setCoordStops(int** coordStops) {
	this->coordStops = coordStops;
}

std::vector<Stop> VRP::getStops() {
	return this->vStops;
}

void VRP::setStops(std::vector<Stop> vStops) {
	this->vStops = vStops;
}

std::vector<Student> VRP::getStudentds() {
	return this->vStudents;
}

void VRP::setStudents(std::vector<Student> vStudent) {
	this->vStudents = vStudent;
}

std::vector<Stop> VRP::getBusStops() {
	return this->busStopAssigned;
}

void VRP::setBusStops(std::vector<Stop> busses) {
	this->busStopAssigned = busses;
}

//For CVRP
int VRP::getK() {
	return this->K;
}

void VRP::setK(int K) {
	this->K = K;
}

int VRP::getCk() {
	return this->Ck;
}

void VRP::setCk(int Ck) {
	this->Ck = Ck;
}

int VRP::getKmin() {
	return this->Kmin;
}

void VRP::setKmin(int Kmin) {
	this->Kmin = Kmin;
}

Stop VRP::getCoorSchool() {
	return this->coorSchool;
}

void VRP::setCoorSchool(Stop stop) {
	this->coorSchool = stop;
}

double VRP::getDistanceIJ(Stop s1, Stop s2) {
	double dx = 0.0, dy = 0.0, dr = 0.0;
	dx = pow((s2.getX() - s1.getX()), 2);
	dy = pow((s2.getY() - s1.getY()), 2);

	dr = sqrt(dx + dy);
	return dr;
}

double VRP::getDistanceLS(Student s1, Stop s2) {
	double dx, dy, dr;
	dx = pow((s2.getX() - s1.getCoord_x()), 2);
	dy = pow((s2.getY() - s1.getCoord_y()), 2);

	dr = sqrt(dx + dy);
	return dr;
}

double** VRP::getC() {
	return this->C;
}

void VRP::setC(double** C) {
	this->C = C;
}

double** VRP::getCLS() {
	return this->Cls;
}

void VRP::setCLS(double** CLS) {
	this->Cls = CLS;
}

double VRP::getRadio() {
	return this->radio;
}

void VRP::setRadio(double r) {
	this->radio = r;
}

double VRP::getObjectiveFunction() {
	double result = 0;
	for (int i = 0; i < getNroStops(); i++) {
		for (int j = 0; j < getNroStops(); j++) {
			if (i != j) {
				result = result + C[i][j] * X[i][j];
			}
		}
	}

	return result;
}

double VRP::getRestriction1() {
	double result = 0;
	for (int i = 0; i < getNroStops(); i++) {
		double suma = 0;
		for (int j = 0; j < getNroStops(); j++) {
			suma = suma + X[i][j];
		}
	}
	return result;
}

double VRP::getRestriction2() {
	double result = 0;
	for (int i = 0; i < getNroStops(); i++) {
		double suma = 0;
		for (int j = 0; j < getNroStops(); j++) {
			suma = suma + X[j][i];
		}
	}
	return result;
}

double VRP::getRestriction3() {
	return 0.0;
}

std::vector<Student> VRP::getStudentsByStop(Stop stop) {
	std::vector<Student> allStudents = getStudentds();
	std::vector<Student> result;
	priority_queue<Stud, vector<Stud>, CompareStud> pq;

	double distance = 0;
	int p = 0;
	double radio = getRadio();
	for (std::vector<Student>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		distance = getDistanceLS(student, stop);
		if (distance <= radio) {
			p++;
			Stud stud = { student, distance };
			pq.push(stud);
		}
	}

	int k = 0;
	//k < nroStudents
	while (!pq.empty()) {
		Stud t = pq.top();
		result.insert(result.begin() + k, t.s);
		pq.pop();
		k++;
	}
	return result;
}

std::vector<Stop> VRP::getStopsOrderedByStudents(Student student) {
	std::vector<Stop> allStops = getStops();
	std::vector<Stop> result;
	priority_queue<StopBus, vector<StopBus>, CompareStopBus> pq2;
	double distance = 0;
	double radio = getRadio();
	for (std::vector<Stop>::size_type i = 0; i != allStops.size(); i++) {
		Stop stop = allStops.at(i);
		distance = getDistanceLS(student, stop);
		if (distance <= radio) {
			StopBus stopBus = { stop, distance };
			pq2.push(stopBus);
		}
	}
	int k = 0;
	while (!pq2.empty()) {
		StopBus t = pq2.top();
		result.insert(result.begin() + k, t.s);
		pq2.pop();
		k++;
	}
	return result;
}

void VRP::greedy() {

	std::vector<Stop> allStops = getStops();
	int m = 0;
	int g = 0;
	int l = 0;
	for (std::vector<Stop>::size_type p = 0; p != allStops.size(); p++) {
		Stop initialStop = allStops.at(p);
		std::vector<Student> students = getStudentsByStop(initialStop);

		if (!students.empty()) {
			//int capacity = initialStop.getCapacity();
			int k = 0;
			for (std::vector<Student>::size_type i = 0; i != students.size();
					i++) {
				if (!isInGlobalVector(students.at(i))) {
					//Add the students into each vector stop
					queue.insert(queue.begin() + k, students.at(i));
					queue2.insert(queue2.begin() + k, students.at(i));
					k++;
				}
			}
			//int queue2Capacity = queue2.size();
			if (queue2.empty()) {
				emptyBusStopsByAssignment.insert(
						emptyBusStopsByAssignment.begin() + g, initialStop);
				g = g + 1;
			} else {
				map.insert(
						pair<int, std::vector<Student> >(initialStop.getId(),
								queue2));
				initialStop.setCapacity(queue2.size());
				busAssigned.insert(busAssigned.begin() + l, initialStop);
				cout << "Stop (" << initialStop.getX() << ", "
						<< initialStop.getY() << ")" << endl;
				for (std::map<Student, int>::size_type i = 0;
						i != queue2.size(); i++) {
					Student s = queue2.at(i);
					cout << "(" << s.getCoord_x() << ", " << s.getCoord_y()
							<< ")" << endl;
				}
				l = l + 1;
				cout << "=======================" << endl;
				queue2.clear();
			}
		} else {
			emptyBusStopsByDistance.insert(emptyBusStopsByDistance.begin() + m,
					initialStop);
			m++;
		}
	}

	std::vector<Student> allStudents = getStudentds();
	int r = 0;
	int o = 0;
	for (std::vector<int>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		bool isInsertedInTheQueue = false;
		for (std::vector<int>::size_type j = 0; j != queue.size(); j++) {
			Student student2 = queue.at(j);
			if (student.isEqualTo(student2)) {
				isInsertedInTheQueue = true;
			}
		}
		if (!isInsertedInTheQueue) {
			studentNotAssigned.insert(studentNotAssigned.begin() + r, student);
			r++;
		} else {
			studentAssigned.insert(studentAssigned.begin() + o, student);
		}
	}
	cout << "========================================" << endl;
	cout << "List of students that are not assigned to queue." << endl;
	for (std::vector<Student>::size_type i = 0; i != studentNotAssigned.size();
			i++) {
		Student s = studentNotAssigned.at(i);
		cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")" << endl;
	}

	cout << "List of students that are not assigned to queue." << endl;
	for (std::vector<Student>::size_type i = 0; i != studentAssigned.size();
			i++) {
		Student s = studentAssigned.at(i);
		cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")" << endl;
	}
	setBussAssigned(busAssigned);
	cout << "List of Stops that are used.." << endl;
	for (std::vector<Stop>::size_type i = 0; i != busAssigned.size(); i++) {
		Stop s = busAssigned.at(i);
		cout << "(" << s.getX() << ", " << s.getY() << ")" << endl;
	}

}

void VRP::init() {
	std::vector<Stop> allStops = getStops();
	int m = 0;
	int g = 0;
	//int l = 0;
	for (std::vector<Stop>::size_type p = 0; p != allStops.size(); p++) {
		Stop initialStop = allStops.at(p);
		std::vector<Student> students = getStudentsByStop(initialStop);

		if (!students.empty()) {
			int capacity = initialStop.getCapacity();
			int k = 0;
			for (std::vector<Student>::size_type i = 0; i != students.size();
					i++) {
				if (!isInGlobalVector(students.at(i)) && k < capacity) {
					//Add the students into each vector stop
					queue.insert(queue.begin() + k, students.at(i));
					queue2.insert(queue2.begin() + k, students.at(i));
					k++;
				}
			}
			//int queue2Capacity = queue2.size();
			if (queue2.empty()) {
				emptyBusStopsByAssignment.insert(
						emptyBusStopsByAssignment.begin() + g, initialStop);
				g = g + 1;
			} else {
				map.insert(
						pair<int, std::vector<Student> >(initialStop.getId(),
								queue2));
				cout << "Stop (" << initialStop.getX() << ", "
						<< initialStop.getY() << ")" << endl;
				for (std::map<Student, int>::size_type i = 0;
						i != queue2.size(); i++) {
					Student s = queue2.at(i);
					cout << "(" << s.getCoord_x() << ", " << s.getCoord_y()
							<< ")" << endl;
				}
				cout << "=======================" << endl;
				queue2.clear();
			}
		} else {
			emptyBusStopsByDistance.insert(emptyBusStopsByDistance.begin() + m,
					initialStop);
			m++;
		}
	}

	cout << "List of stop bus empties by distance." << endl;
	for (std::map<Student, int>::size_type i = 0;
			i != emptyBusStopsByDistance.size(); i++) {
		Stop s = emptyBusStopsByDistance.at(i);
		cout << "(" << s.getX() << ", " << s.getY() << ")" << endl;
	}
	cout << "=======================" << endl;

	cout << "List of stop bus empties  by assignment." << endl;
	for (std::map<Student, int>::size_type i = 0;
			i != emptyBusStopsByAssignment.size(); i++) {
		Stop s = emptyBusStopsByAssignment.at(i);
		cout << "(" << s.getX() << ", " << s.getY() << ")" << endl;
	}
	cout << "=======================" << endl;
	/*
	 cout << "List of stop bus with less than the capacity." << endl;
	 for (std::map<Student, int>::size_type i = 0;
	 i != lessStudentsInStopBus.size(); i++) {
	 Stop s = lessStudentsInStopBus.at(i);
	 cout << "(" << s.getX() << ", " << s.getY() << ")" << endl;
	 }
	 cout << "=======================" << endl;
	 */
	cout << "List of students added to the queue." << endl;
	for (std::map<Student, int>::size_type i = 0; i != queue.size(); i++) {
		Student s = queue.at(i);
		cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")" << endl;
	}
	cout << "=======================" << endl;

	std::vector<Student> allStudents = getStudentds();
	int r = 0;
	for (std::vector<int>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		bool isInsertedInTheQueue = false;
		for (std::vector<int>::size_type j = 0; j != queue.size(); j++) {
			Student student2 = queue.at(j);
			if (student.isEqualTo(student2)) {
				isInsertedInTheQueue = true;
			}
		}
		if (!isInsertedInTheQueue) {
			studentNotAssigned.insert(studentNotAssigned.begin() + r, student);
			r++;
		}
	}

	cout << "List of students that are not assigned to queue." << endl;
	for (std::vector<Student>::size_type i = 0; i != studentNotAssigned.size();
			i++) {
		Student s = studentNotAssigned.at(i);
		cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")" << endl;
	}

	cout << "All stops near to each student." << endl;
	for (std::vector<Student>::size_type i = 0; i != studentNotAssigned.size();
			i++) {
		Student studentToBeAssigned = studentNotAssigned.at(i);
		std::vector<Stop> allStops = getStopsOrderedByStudents(
				studentToBeAssigned);
		//Assign the student to the first stop
		Stop firstStop = allStops.at(0);
		cout << "The stop nearest from this student ("
				<< studentToBeAssigned.getCoord_x() << ", "
				<< studentToBeAssigned.getCoord_y() << ") is : ("
				<< firstStop.getX() << ", " << firstStop.getY() << ")" << endl;
		//Get the students assigned to this selected stop:
		std::map<int, std::vector<Student> >::iterator mapIter = map.find(
				firstStop.getId());

		if (mapIter != map.end()) {
			std::vector<Student> studentsAlreadyAssignedToStop = mapIter->second;
			cout << "List of students that were already assigned to stop."
					<< endl;
			int tam = studentsAlreadyAssignedToStop.size();
			for (std::vector<Student>::size_type i = 0;
					i != studentsAlreadyAssignedToStop.size(); i++) {
				Student s = studentsAlreadyAssignedToStop.at(i);
				cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")"
						<< endl;
			}
			studentsAlreadyAssignedToStop.insert(
					studentsAlreadyAssignedToStop.begin() + tam,
					studentToBeAssigned);
			//Updating the vector of students in the selected stop bus
			mapIter->second = studentsAlreadyAssignedToStop;

			cout << "Bus Stop students after update." << endl;
			for (std::vector<Student>::size_type i = 0;
					i != studentsAlreadyAssignedToStop.size(); i++) {
				Student s = studentsAlreadyAssignedToStop.at(i);
				cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")"
						<< endl;
			}
		} else {
			cout << "Error - can not find the element in the map." << endl;
		}
		cout << "end  for this stop." << endl;
	}
	cout << "size stops = " << allStops.size() << endl;
	std::vector<Stop> v_busStopsAssigned;
	int u = 0;
	for (std::vector<Stop>::size_type q = 0; q != allStops.size(); q++) {
		Stop stop = allStops.at(q);
		int capacityStop = stop.getCapacity();
		std::map<int, std::vector<Student> >::iterator mapIter = map.find(
				stop.getId());

		if (mapIter != map.end()) {
			std::vector<Student> studentsInBusStop = mapIter->second;
			int capacityStopIter = studentsInBusStop.size();
			if (capacityStop == capacityStopIter) {
				cout << "Perfect assignment" << endl;
			} else if (capacityStopIter < capacityStop) {
				cout << "Less students that the allowed." << endl;
			} else if (capacityStopIter > capacityStop) {
				cout << "More students that the allowed." << endl;
			}
			//Update to the new capacity for each included stop.
			stop.setCapacity(capacityStopIter);
			v_busStopsAssigned.insert(v_busStopsAssigned.begin() + u, stop);
			u++;
		} else {
			cout << "no encuentra a alguno" << endl;
			cout << "(" << stop.getX() << ", " << stop.getY() << ")" << endl;
		}
	}
	//The bus stops final
	setBusStops(v_busStopsAssigned);
	cout << "algo " << endl;
	cout << "size = " << getBusStops().size() << endl;
	for (std::vector<Stop>::size_type i = 0; i != getBusStops().size(); i++) {
		Stop stop2 = getBusStops().at(i);
		cout << "(" << stop2.getX() << ", " << stop2.getY() << ")" << endl;
		cout << "the new Capacity is = " << stop2.getCapacity() << endl;
	}

	for (std::vector<Student>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		Stop stop = getStopByStudent(student);
		cout << "The student located at place (" << student.getCoord_x() << ", "
				<< student.getCoord_y() << ")" << endl;

		cout << " goes to the bus stop in the position (" << stop.getX() << ", "
				<< stop.getY() << ")" << endl;
	}

	//Fill the new vector of Stops with the school coordinates

}

Stop VRP::getStopByStudent(Student student) {
	std::vector<Stop> allStops = getStops();
	Stop result(0, 0);
	for (std::vector<Stop>::size_type i = 0; i != allStops.size(); i++) {
		Stop stop = allStops.at(i);
		int id = stop.getId();
		std::map<int, std::vector<Student> >::iterator mapIter2 = map.find(id);

		if (mapIter2 != map.end()) {
			std::vector<Student> studentList = mapIter2->second;
			for (std::vector<Student>::size_type j = 0; j != studentList.size();
					j++) {
				Student studentIter = studentList.at(j);
				if (student.isEqualTo(studentIter)) {
					return stop;
				}
			}
		}
	}
	return result;
}

bool VRP::isInGlobalVector(Student s1) {

	for (std::vector<Student>::size_type i = 0; i != queue.size(); i++) {
		Student s2 = queue.at(i);
		if (compare(s1, s2)) {
			return true;
		}
	}
	return false;
}

std::vector<Stop> VRP::getBusAssigned() {
	return this->busAssigned;
}

void VRP::setBussAssigned(std::vector<Stop> assignedStops) {
	this->busAssigned = assignedStops;
}

bool VRP::compare(Student s1, Student s2) {
	if ((s1.getCoord_x() == s2.getCoord_x())
			&& (s1.getCoord_y() == s2.getCoord_y())) {
		return true;
	}
	return false;
}

void VRP::uploadFile(char pathFile[]) {
	std::cout.imbue(
			std::locale(std::cout.getloc(), new punct_facet1<char, ','>));
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(2);

	std::fstream file(pathFile);
	char str[100];
	int nro_stops;
	int nro_students;
	int nro_vehicles;
	int capacity_vehicle;
	int nro_vehicles_min;
	int coord_depot_x;
	int coord_depot_y;
	double radio;

	file >> str;
	file >> nro_stops;
	file >> str;
	file >> nro_students;
	file >> str;
	file >> nro_vehicles;
	file >> str;
	file >> nro_vehicles_min;
	file >> str;
	file >> capacity_vehicle;
	file >> str;
	file >> radio;
	file >> str;
	file >> str;
	file >> str;
	file >> coord_depot_x;
	file >> coord_depot_y;

	file >> str;
	file >> str;
	file >> str;
	file >> str;
	file >> str;

	setNroStops(nro_stops);
	setNroStudents(nro_students);
	setK(nro_vehicles);
	setKmin(nro_vehicles_min);
	setCk(capacity_vehicle);
	setRadio(radio);
	Stop coord_school(coord_depot_x, coord_depot_y);
	setCoorSchool(coord_school);

//#############################################
	int** coord_Stops = new int*[nroStops];
	int** X_s = new int*[nro_stops];
	C = new double*[nroStops];

//Initialize Stops
	for (int i = 0; i < nroStops; i++) {
		coord_Stops[i] = new int[4];
		C[i] = new double[nroStops];
		X_s[i] = new int[1];
	}

	for (int i = 0; i < nroStops; i++) {
		for (int j = 0; j < 4; j++) {
			file >> coord_Stops[i][j];
		}
	}
	setCoordStops(coord_Stops);

	std::vector<Stop> v_stops;
	for (int i = 0; i < nroStops; i++) {
		Stop s(coord_Stops[i][0], coord_Stops[i][1], coord_Stops[i][2],
				coord_Stops[i][3]);
		v_stops.insert(v_stops.begin() + i, s);
	}
	setStops(v_stops);

	for (int i = 0; i < nroStops; i++) {
		for (int j = 0; j < nroStops; j++) {
			double distance = getDistanceIJ(v_stops.at(i), v_stops.at(j));
			cout << distance << " ";
			C[i][j] = distance;
		}
		cout << "\n";
	}
	cout << "Imprimir costos from j to j." << endl;
	for (int i = 0; i < nroStops; i++) {
		for (int j = 0; j < nroStops; j++) {
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}

	//setC(C_s);

//###########################################
//Initialize Students
	file >> str;
	file >> str;
	file >> str;
	file >> str;

	int** coord_Students = new int*[nroStudents];
	for (int i = 0; i < nroStudents; i++) {
		coord_Students[i] = new int[3];
	}

	Cls = new double*[nroStudents];
	for (int i = 0; i < nroStudents; i++) {
		Cls[i] = new double[nroStops];
	}

	for (int i = 0; i < nroStudents; i++) {
		for (int j = 0; j < 3; j++) {
			file >> coord_Students[i][j];
		}
	}

	std::vector<Student> v_students;
	for (int i = 0; i < nroStudents; i++) {
		Student s(coord_Students[i][1], coord_Students[i][2]);
		v_students.insert(v_students.begin() + i, s);
	}

	setStudents(v_students);

	for (int i = 0; i < nroStudents; i++) {
		for (int j = 0; j < nroStops; j++) {
			Cls[i][j] = getDistanceLS(v_students.at(i), v_stops.at(j));
		}
	}

	//setCLS(C_ls);
}
