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
	cout << "\nMinimize the routes.\n\n" << endl;
	double costGreedy = CV.getFO(CV.getAllRoutesGreedy());
	cout << "Cost Greedy = " << costGreedy << endl;
	double costSaving = CV.getFO(CV.getAllRoutesSaving());
	cout << "Cost Saving = " << costSaving << endl;
	cout << "\nTwo opt in a route.\n\n" << endl;
	double minTwoOptGreedy = CV.twoOptRoute(CV.getAllRoutesGreedy());
	cout << "Min two-opt in a route greedy = " << minTwoOptGreedy << endl;
	double minTwoOptSaving = CV.twoOptRoute(CV.getAllRoutesSaving());
	cout << "Min two-opt in a route saving = " << minTwoOptSaving << endl;
	cout << "\nTwo opt between routes.\n\n" << endl;
	double minTwoOptBetweenRoutesGreedy = CV.exchangingBetweenRoutes(
			CV.getAllRoutesGreedy());
	cout << "Min exchanging between routes greedy = "
			<< minTwoOptBetweenRoutesGreedy << endl;

	double minTwoOptBetweenRoutesSaving = CV.exchangingBetweenRoutes(
			CV.getAllRoutesSaving());
	cout << "Min exchaning between routes saving = "
			<< minTwoOptBetweenRoutesSaving << endl;

	cout << "\nMetaheuristics:\n\n" << endl;
	double minILSGreedy = CV.ILSInTheRoute(CV.getAllRoutesGreedy());
	cout << "Min ILS greedy with 2opt in the route = " << minILSGreedy << endl;
	double minILSSaving = CV.ILSInTheRoute(CV.getAllRoutesSaving());
	cout << "Min ILS saving with 2opt in the route = " << minILSSaving << endl;

	//CV.printRoutes(CV.getAllRoutesGreedy());
	double minILS2optBRGreedy = CV.ILSBetweenRoutes(CV.getAllRoutesGreedy());
	cout << "Min ILS greedy with exchanging customers between routes = " << minILS2optBRGreedy
			<< endl;
	//CV.printRoutes(CV.getAllRoutesSaving());
	double minILS2optBRSaving = CV.ILSBetweenRoutes(CV.getAllRoutesSaving());
	cout << "Min ILS saving with exchanging customers between routes = " << minILS2optBRSaving
			<< endl;

	return 0;
}
