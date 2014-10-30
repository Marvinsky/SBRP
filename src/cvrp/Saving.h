/*
 * Saving.h
 *
 *  Created on: 29/10/2014
 *      Author: Marvin
 */

#ifndef SAVING_H_
#define SAVING_H_


class Saving {
private:
	int x;
	int y;
	double peso;

public:
	Saving();
	Saving(int x, int y, double peso);
	int getSavingX();
	void setSavingX(int x);
	int getSavingY();
	void setSavingY(int y);
	double getSavingPeso();
	void setSavingPeso(double peso);

};

#endif /* SAVING_H_ */
