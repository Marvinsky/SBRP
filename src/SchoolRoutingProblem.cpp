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
	//	"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\instancias\\002.vrp";
	//		"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\instancias\\ex4_n6.pmv";
			"C:\\workspaces\\metahuristica\\SchoolRoutingProblem\\src\\instancias\\003.vrp";
	//		"C:\\Users\\Marvin\\Desktop\\Metaheuristica\\seminario3\\instancias\\002.vrp";
	//		"C:\\Users\\Marvin\\Desktop\\Metaheuristica\\seminario3\\instancias\\ex4_n6.pmv";
	V.uploadFile(input);
	V.greedy();

	CVRP CV;
	CV.greedy(V);
	CV.savingAlgorithm();
	CV.initialSolutionReport();
	double costGreedy = CV.getFO(CV.getAllRoutesGreedy());
	cout << "Cost Greedy = " << costGreedy << endl;
	double costSaving = CV.getFO(CV.getAllRoutesSaving());
	cout << "Cost Saving = " << costSaving << endl;
	double maxTwoOptGreedy = CV.twoOptRoute(CV.getAllRoutesGreedy());
	cout << "Max two-opt greedy = " << maxTwoOptGreedy << endl;
	double maxTwoOptSaving = CV.twoOptRoute(CV.getAllRoutesSaving());
	cout << "Max two-opt saving = " << maxTwoOptSaving << endl;
	return 0;
}
