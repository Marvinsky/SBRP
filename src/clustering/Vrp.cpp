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
	for (std::vector<Student>::size_type i = 0; i != allStudents.size(); i++) {
		Student student = allStudents.at(i);
		distance = getDistanceLS(student, stop);
		Stud stud = { student, distance };
		pq.push(stud);
	}
	int nroStudents = stop.getCapacity();

	int k = 0;
	while (!pq.empty() && k < nroStudents) {
		Stud t = pq.top();
		result.insert(result.begin() + k, t.s);
		pq.pop();
		k++;
	}
	return result;
}

void VRP::init() {
	//Stop s(8, 7, 2);
	//(2, 4) == (1, 5), (3, 4)
	//(6, 1) == (1, 5), (3, 4), (3, 1), (4, 2)
	//(4, 2) == (1, 5), (3, 4), (3, 1), (4, 2)
	//(4, 8) == (1, 5), (3, 4), (5, 7)
	//(8, 7) == (1, 5), (3, 4), (8, 5)
	//std::vector<Student> students = getStudentsByStop(s);

	std::vector<Stop> allStops = getStops();
	for (std::vector<Stop>::size_type p = 0; p != allStops.size(); p++) {
		std::vector<Student> students = getStudentsByStop(allStops.at(p));

		int k = 0;
		for (std::vector<Student>::size_type i = 0; i != students.size(); i++) {
			if (!isInGlobalVector(students.at(i))) {
				//Add the students into each vector stop
				//queue.insert(pair<Student, int>(students.at(i), i));
				queue.insert(queue.begin() + k, students.at(i));
				k++;
			} else {
				queue.erase(queue.begin() + i);
			}
		}

		cout << "Stop (" << allStops.at(p).getX() << ", "
				<< allStops.at(p).getY() << ")" << endl;
		for (std::map<Student, int>::size_type i = 0; i != queue.size(); i++) {
			Student s = queue.at(i);
			cout << "(" << s.getCoord_x() << ", " << s.getCoord_y() << ")"
					<< endl;
		}
		cout << "=======================" << endl;
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
		Stop s(coord_Stops[i][1], coord_Stops[i][2], coord_Stops[i][3]);
		v_stops.insert(v_stops.begin() + i, s);
	}
	setStops(v_stops);

	for (int i = 0; i < nroStops; i++) {
		for (int j = 0; j < nroStops; j++) {
			C_s[i][j] = getDistanceIJ(v_stops.at(i), v_stops.at(j));
		}
	}

	setC(C_s);

	/*for (int i = 0; i < nroStops; i++) {
	 for (int j = 0; j < nroStops; j++) {
	 cout << C_s[i][j] << " ";
	 }
	 cout << "\n";
	 }*/
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

	/*for (int i = 0; i < nroStudents; i++) {
	 for (int j = 0; j < nroStops; j++) {
	 cout << this->Cls[i][j] << " ";
	 }
	 cout << "\n";
	 }*/
}
