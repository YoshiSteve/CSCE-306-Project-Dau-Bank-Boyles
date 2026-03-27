/*
 * Rainbow.h
 *
 *  Created on: Mar 2, 2026
 *      Author: Stella
 *
 *      Goal: Have an organized structure to keep track of raibow tribbles orders and put customers on waitlist if needed
 *
 *      Includes:  Total rainbow numbers, waitlist, and orders for rainbow tribbles
 */

#ifndef RAINBOW_H_
#define RAINBOW_H_
#include <vector>
#include <string>


using namespace std;

class Rainbow {
private:
	std::vector<string> rainbowOrders;
	std::vector<string> waitList;

public:
	Rainbow();
	int get_waitlistsize(){return waitList.size();}
	void add_Waitlist(string custID){waitList.push_back(custID);}
	void add_Order(string custID){rainbowOrders.push_back(custID);}
	string get_Next(){return waitList[0];}
	void remove_order(){ waitList.erase(waitList.begin());}

};
/*
 * Rainbow.cpp
 *
 *  Created on: Mar 3, 2026
 *      Author: Stella
 *
 *      Goal: Initialize rainbow
 */


#include "Rainbow.h"

Rainbow::Rainbow(){

}



#endif /* RAINBOW_H_ */
