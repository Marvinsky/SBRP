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

double VRP::getDistanceIJ(Stop s1, Stop s2) {
	double dx, dy, dr;
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
	for (std::vector<Student>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		distance = getDistanceLS(student, stop);
		if (distance <= 6) {
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

	for (std::vector<Stop>::size_type i = 0; i != allStops.size(); i++) {
		Stop stop = allStops.at(i);
		distance = getDistanceLS(student, stop);
		if (distance <= 6) {
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
			} /*else if (queue2Capacity < capacity) {
			 lessStudentsInStopBus.insert(lessStudentsInStopBus.begin() + l,
			 initialStop);
			 l = l + 1;
			 } */else {
				map.insert(
						pair<int, std::vector<Student>>(initialStop.getId(),
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

bool VRP::compare(Student s1, Student s2) {
	if ((s1.getCoord_x() == s2.getCoord_x())
			&& (s1.getCoord_y() == s2.getCoord_y())) {
		return true;
	}
	return false;
}

void VRP::uploadFile(char pathFile[]) {
	std::fstream file(pathFile);
	char str[100];
	int nro_stops;
	int nro_students;
	file >> str;
	file >> nro_stops;
	file >> str;
	file >> nro_students;

	file >> str;
	file >> str;
	file >> str;
	file >> str;
	file >> str;

	setNroStops(nro_stops);
	setNroStudents(nro_students);

	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(1);

//#############################################
	int** coord_Stops = new int*[nroStops];
	int** X_s = new int*[nro_stops];
	double** C_s = new double*[nroStops];

//Initialize Stops
	for (int i = 0; i < nroStops; i++) {
		coord_Stops[i] = new int[4];
		C_s[i] = new double[nroStops];
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
			C_s[i][j] = getDistanceIJ(v_stops.at(i), v_stops.at(j));
		}
	}

	setC(C_s);

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

	double** C_ls = new double*[nroStudents];
	for (int i = 0; i < nroStudents; i++) {
		C_ls[i] = new double[6];
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
	cout << "size of students = " << v_students.size() << endl;

	for (int i = 0; i < nroStudents; i++) {
		for (int j = 0; j < nroStops; j++) {
			C_ls[i][j] = getDistanceLS(v_students.at(i), v_stops.at(j));
		}
	}

	setCLS(C_ls);
}
