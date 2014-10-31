/*
 * Saving.h
 *
 *  Created on: 29/10/2014
 *      Author: Marvin
 */

#ifndef SAVING_H_
#define SAVING_H_

#include "Customer.h"

class Saving {
private:
	Customer c1;
	Customer c2;
	double peso;

public:
	Saving();
	Saving(Customer c1, Customer c2, double peso);
	Customer getSavingC1();
	void setSavingC1(Customer c1);
	Customer getSavingC2();
	void setSavingC2(Customer c2);
	double getSavingPeso();
	void setSavingPeso(double peso);

};

#endif /* SAVING_H_ */
