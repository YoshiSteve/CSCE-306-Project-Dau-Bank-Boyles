
/*
 * trans_class.h
 *
 * Author: Logan & Stella & Mack
 *
 * Implements functions from transactions
 * includes:  finding order ID, viewing orders, getting price, adding orders, and making orders for rainbow tribbles
 * Phase 3 Modifications: Modified load orders to add to employees
 * Goal: Manage ordering amongst customers and write information to files
 */

#include <iostream>
#include <fstream>
#include "Ordering.h"
#include "transactions.h"
#include "Rainbow.h"
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;



string find_order_id() {
    // gets the latest order ID from orders.txt and increments it by 1 for the next entry
    string last_id;
    string line;

    ifstream orders("orders.txt");
    if (!orders.is_open()) {
        cout << "Could not open orders.txt to get order id";
    }
    // finds the latest order ID
    while (getline(orders, line)){
        stringstream ss(line);
        string curr_id;

        if (getline(ss, curr_id, ';'))
            last_id = curr_id;
    }
    orders.close();

    // converts to an int and increments it by 1, before returning a 6-digit string 
    int id_int = stoi(last_id);
    id_int++;
    stringstream next_id;
    next_id << setfill('0') << setw(6) << id_int;
    return next_id.str();

}

double get_price(int tribble_num) {
    // finds the price for each quantity of tribbles, throws error if outside the range
    if (tribble_num == 1) return 9.50;
    else if (tribble_num == 2) return 16.15;
    else if (tribble_num == 3) return 25.88;
    else if (tribble_num == 4) return 28.15;
    else if (tribble_num == 5) return 30.00;
    else {
        throw invalid_argument("Tribble quanitity must be between 1 and 5");
    }
}

vector<transaction> all_transactions;

void write_order(string customer_id, string date, int tribble_num, double price) {
    // writes the transaction to 2 output files
    string order_id = find_order_id();
    transaction new_t(customer_id, order_id);
    all_transactions.push_back(new_t);
    ofstream trans_file("transactions.txt", ios::app);
    ofstream orders("orders.txt", ios::app);
    if (!trans_file.is_open() || !orders.is_open()) {
        cout << "Error opening file";
    }
    trans_file << customer_id << ";" << order_id << "\n";
    orders << order_id << ";" << date << ";" << tribble_num << ";" << price << "\n";
    orders.close();
    trans_file.close();

    int c= searchId(customer_id);

    Ordering newOrder;
    string num=to_string(tribble_num);
    string priced= to_string(price);

    newOrder.set_orderID(order_id);
    newOrder.set_date(date);
    newOrder.set_tribbleNum(num);
    newOrder.set_payment(priced);

    customerList[c].addOrder(newOrder);


    cout << "Order Added!" << endl;


}

void load_orders(){

	ifstream trans("transactions.txt");

	if(!trans.is_open()){
			cout<< "Error Opening transactions.txt!";
		}

	ifstream orders("orders.txt");

	if(!orders.is_open()){
				cout<< "Error Opening orders.txt!";
			}
	string line;
	string line2;

	// read transaction file and pair to orders file then add it to the customers class
	while(getline(trans,line)){
		stringstream ss(line);
		string customer;
		string employee;
		string data;

		getline(ss,customer,';');
		getline(ss,employee, ';');
		getline(ss,data, ';');

		//reset file
		orders.clear();
		orders.seekg(0);

		while(getline(orders, line2)){
			stringstream ss(line2);
			string orderID;

			getline(ss, orderID,';');

			if (orderID==data){
				int c= searchId(customer);
				int e = searchEmployee(employee);
				Ordering newOrder;
				string date, num, price;

				getline(ss,date,';');
				getline(ss,num,';');
				getline(ss, price, ';');

				newOrder.set_orderID(orderID);
				newOrder.set_date(date);
				newOrder.set_tribbleNum(num);
				newOrder.set_payment(price);
				if(c > -1){
					customerList[c].addOrder(newOrder);
				}
				if(e > -1){
					employeeList[e]->add_Sale(newOrder);
				}
			}
		}
	}
	trans.close();
	orders.close();

}

//initialize rainbow class for all rainbow purchases
Rainbow rainbow;

void orderRainbow(string custID){
// make rainbow purchase if it is available
	ofstream rain("rainbowList.txt", ios::app);
	if (!rain.is_open()) {
			    cout << "Error opening file to write rainbow order";
	}

	rainbow.add_Waitlist(custID);

	rain<<custID << endl;

	rain.close();

	cout<<custID<<" has been added to the waitlist"<<endl;

}
string sellRainbow(string date){
	if (rainbow.get_waitlistsize()==0){
		cout<<"There are no orders on the waitlist"<<endl;
	}
	string cust= rainbow.get_Next();

	rainbow.add_Order(cust);

	rainbow.remove_order();
	string order_id=find_order_id();
	ofstream trans("transactions.txt",ios::app);

	if (!trans.is_open()) {
			    cout << "Error opening file to write rainbow order";
	}

	trans<<cust<<";"<<order_id<<endl;

	trans.close();

	cout<<"You have placed a rainbow tribble order"<<endl;

	return cust;
}

void importRainbow(){
	fstream rain("rainbowList.txt");

	if(!rain.is_open()){
		cout<< "Error opening file rainbowlist.txt" << endl;
	}
	string line;
	while(getline(rain, line)){
		stringstream ss(line);
		string order;
		getline(ss, order);

		rainbow.add_Waitlist(order);

	}
	rain.close();
}


