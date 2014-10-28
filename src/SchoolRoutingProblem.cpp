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
			"C:\\Users\\Marvin\\Desktop\\Metaheuristica\\seminario3\\instancias\\ex4_n6.pmv";
	V.uploadFile(input);
	V.init();

	CVRP CV;
	CV.init(V);
	return 0;
}
