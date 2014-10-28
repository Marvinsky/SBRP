/*
 * Customer.h
 *
 *  Created on: 28/10/2014
 *      Author: Marvin
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
private:
	int x;
	int y;
	int demand;
public:
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getDemand();
	void setDemand(int demand);
	Customer();
	Customer(int x, int y, int demand);
};

#endif /* CUSTOMER_H_ */
