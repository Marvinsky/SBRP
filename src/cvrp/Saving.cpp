/*
 * Saving.cpp
 *
 *  Created on: 29/10/2014
 *      Author: Marvin
 */

#include "Saving.h"

Saving::Saving() {
	//TODO
}

Saving::Saving(Customer c1, Customer c2, double peso) {
	this->c1 = c1;
	this->c2 = c2;
	this->peso = peso;
}

Customer Saving::getSavingC1() {
	return this->c1;
}

void Saving::setSavingC1(Customer c1) {
	this->c1 = c1;
}

Customer Saving::getSavingC2() {
	return this->c2;
}

void Saving::setSavingC2(Customer c2) {
	this->c2 = c2;
}

double Saving::getSavingPeso() {
	return this->peso;
}

void Saving::setSavingPeso(double peso) {
	this->peso = peso;
}
