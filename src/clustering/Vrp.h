/*
 * Vrp.h
 *
 *  Created on: 15/10/2014
 *      Author: Marvin
 */

#ifndef VRP_H_
#define VRP_H_

#include "Stop.h"
#include "Student.h"

#include <vector>
#include <map>

#include <iostream>
#include <queue>
#include <iomanip>

struct Stud {
	//int x;
	//int y;
	Student s;
	double distance;
};

struct StopBus {
	Stop s;
	double distance;
};

class CompareStud {
public:
	bool operator()(Stud& s1, Stud& s2) {
		if (s1.distance > s2.distance) {
			return true;
		}
		return false;
	}
};

class CompareStopBus {
public:
	bool operator()(StopBus& s1, StopBus& s2) {
		if (s1.distance > s2.distance) {
			return true;
		}
		return false;
	}
};

class VRP {
private:
	int nroStops;
	int nroStudents;
	/*
	 * Number the stops assigned to a
	 * bus
	 */
	int nroStopsAssigned;
	/*
	 * Radio of the mini-cluster
	 */
	double radio;
	/**
	 * Number of students in stop
	 */
	int nroStudentsByStop;
	/*
	 * Number of Students by bus
	 */
	int nroStudentsByBus;
	/**
	 * coordinates for each stop
	 */
	int** coordStops;

	/*
	 * Cij
	 */
	double** C;
	/*
	 * Cost to go from Student house to
	 * stop
	 */
	double** Cls;
	int* capacityOfEachV;
	int** coorSchool; //coordinate of the depot.
	/* variable Xij
	 * i!=j binary variable equal to 1
	 * if and only if arc(i, j) appears in the
	 * optimal solution and o otherwise
	 */
	int** X;
	std::vector<Stop> vStops;
	std::vector<Student> vStudents;
	std::vector<Stop> busStopAssigned;

	//std::map<Student, int> queue;
	std::vector<Student> queue;
	std::vector<Student> queue2;
	std::vector<Stop> emptyBusStopsByDistance;
	std::vector<Stop> emptyBusStopsByAssignment;
	//std::vector<Stop> lessStudentsInStopBus;
	std::vector<Student> studentNotAssigned;
	std::map<int, std::vector<Student> > map;

public:
	int getNroStops();
	void setNroStops(int stops);
	int getNroStudents();
	void setNroStudents(int students);
	int** getCoordStops();
	void setCoordStops(int** coordStops);
	void uploadFile(char pathFile[]);
	double getDistanceIJ(Stop s1, Stop s2);
	double getDistanceLS(Student s1, Stop s2);
	std::vector<Stop> getStops();
	void setStops(std::vector<Stop> vStops);
	std::vector<Student> getStudentds();
	void setStudents(std::vector<Student> vStudents);
	std::vector<Stop> getBusStops();
	void setBusStops(std::vector<Stop> busses);

	double getRadio();
	void setRadio(double r);

	double** getC();
	void setC(double** C);
	double** getCLS();
	void setCLS(double** CLS);
	//Objective Function
	double getObjectiveFunction();
	double getRestriction1();
	double getRestriction2();
	double getRestriction3();
	/*
	 * Cluster: Each student must be assigned to one
	 * stop. They way to do it is using a greedy algorithm
	 * to select one stop and associate to it.
	 */
	std::vector<Student> getStudentsByStop(Stop s1);
	bool isInGlobalVector(Student s1);
	bool compare(Student s1, Student s2);
	void init();

	std::vector<Stop> getStopsOrderedByStudents(Student student);

	//Determine for each student which stop he/she
	//should move to.
	Stop getStopByStudent(Student student);

};

#endif /* VRP_H_ */
