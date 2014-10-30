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

Saving::Saving(int x, int y, double peso) {
	this->x = x;
	this->y = y;
	this->peso = peso;
}

int Saving::getSavingX() {
	return this->x;
}

void Saving::setSavingX(int x) {
	this->x = x;
}

int Saving::getSavingY() {
	return this->y;
}

void Saving::setSavingY(int y) {
	this->y = y;
}

double Saving::getSavingPeso() {
	return this->peso;
}

void Saving::setSavingPeso(double peso) {
	this->peso = peso;
}
