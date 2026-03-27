/*
 * Author: Logan
 *
 * Includes: Transaction data to be stored, functions outlined to be implemented
 *
 * Functions: get order ID, customer ID< price, writing orders, find orders, and order rainbow tribbles
 *
 */


#ifndef ORDERS_H_
#define ORDERS_H_

#include <iostream>

using namespace std;

class transaction{
private:
    string customer_id;
    string order_id;

public:
    transaction(string cID, string oID){
        this->customer_id = cID;
        this->order_id = oID;
    }

    string get_order_id() { return order_id;}
    string get_customer_id() { return customer_id;}
    double get_price(int tribble_num);
    void write_order(string customer_id, string date, int tribble_num, double price);
    void load_orders();
    string find_order_id();
    void orderRainbow(string custID, string date );
};



#endif // ORDERS_H_
