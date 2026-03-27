/*
 * Ordering.h
 *
 *  Created on: Mar 4, 2026
 *      Author: barkl
 */

#ifndef ORDERING_H_
#define ORDERING_H_
#include<string>

using namespace std;

class Ordering {
private:
	string orderID;
	string tribbleNum;
	string date;
	string payment;
public:
	Ordering();
	string get_orderID() { return orderID;}
	string get_tribbleNum(){return tribbleNum;}
	string get_payment(){return payment;}
	string get_date(){return date;}
	void set_orderID(string i){orderID=i;}
	void set_tribbleNum(string n){tribbleNum=n;}
	void set_payment(string p){payment=p;}
	void set_date(string d){date=d;}
	void print();
	virtual ~Ordering();
};
#include "Ordering.h"

Ordering::Ordering() {
	// TODO Auto-generated constructor stub

}

Ordering::~Ordering() {
	// TODO Auto-generated destructor stub
}


#endif /* ORDERING_H_ */
