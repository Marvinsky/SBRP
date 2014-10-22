/*
 * Student.h
 *
 *  Created on: 16/10/2014
 *      Author: Marvin
 */

#ifndef STUDENT_H_
#define STUDENT_H_

class Student {
private:
	int coord_x;
	int coord_y;
public:
	Student();
	Student(int x, int y);
	int getCoord_x();
	void setCoord_x(int x);
	int getCoord_y();
	void setCoord_y(int y);
};

#endif /* STUDENT_H_ */
