/*
 * Stop.h
 *
 *  Created on: 15/10/2014
 *      Author: Marvin
 */

#ifndef STOP_H_
#define STOP_H_

class Stop {
private:
	int id;
	int x;
	int y;
	int capacity;
public:
	int getId();
	void setId(int id);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getCapacity();
	void setCapacity(int capacity);
	Stop(int x, int y);
	Stop(int x, int y, int capacity);
	Stop(int id, int x, int y, int capacity);
};

#endif /* STOP_H_ */
