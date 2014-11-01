//============================================================================
// Name        : SchoolRoutingProblem.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "clustering/Vrp.h"
#include "cvrp/Cvrp.h"

#include <vector>

int main() {

	VRP V;
	char input[] =
			"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\instancias\\002.vrp";
	//		"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\instancias\\ex4_n6.pmv";
	//		"C:\\Users\\Marvin\\Desktop\\Metaheuristica\\seminario3\\instancias\\002.vrp";
	//		"C:\\Users\\Marvin\\Desktop\\Metaheuristica\\seminario3\\instancias\\ex4_n6.pmv";
	V.uploadFile(input);
	V.init2();

	CVRP CV;
	CV.init2(V);
	return 0;
}
