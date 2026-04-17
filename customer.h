/*
 * Author: Mack dau
 *
 * Includes: Address, name, id, and setter and getter methods for each
 *
 * Goal: Stores information for customers
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <iostream>
#include "cipher.h"
#include <vector>
#include "Ordering.h"
using namespace std;

class customer{
    private:
        string address;
        string zip_code;
        string first_name;
        string last_name;
        string id;
        string city;
        string state;
        string password;
        std:: vector<Ordering> orders;

    public:
        customer(){}
        customer(string id, string first_name, string last_name, string address, string city,  string state, string zip_code, string password){
            this->id = id;
            this->first_name = first_name;
            this->last_name = last_name;
            this->address = address;
            this->city = city;
            this->state = state;
            this->zip_code = zip_code;
            this->password = password;
        }
        string get_address(){return address;}
        string get_zip_code(){return zip_code;}
        string get_first_name(){return first_name;}
        string get_last_name(){return last_name;}
        string get_id(){return id;}
        string get_state(){return state;}
        string get_city(){return city;}
        string get_password(){return password;}
        void set_city(string c){city = c;}
        void set_state(string s){state = s;}
        void set_address(string a){address = a;}
        void set_zipCode(string z){zip_code = z;}
        void set_firstName(string f){first_name = f;}
        void set_lastName(string l){last_name = l;}
        void set_id(string i){id = i;}
        void addOrder(const Ordering& o){orders.push_back(o);}
        void set_password(string p){password=encryptString(p);}
        void print();
        void showOrders();
};

void customer::print(){
    cout << "Id: " << id << endl;
    cout << "Name: " << first_name << ' ' << last_name << endl;
    cout << "Address: " << address << ", " << city << ", " << state << ", " << zip_code << endl;
    if(orders.empty()){
    	cout<<"No orders for this customer"<<endl;
    }
    else{
    	for(int i=0; i < orders.size(); i++){
    		cout<<"-------------------"<<endl;
    		cout<< "Order Id: "<< orders[i].get_orderID()<<endl;
    		cout<< " Date: "<< orders[i].get_date()<<endl;
    		cout<< " Number: "<< orders[i].get_tribbleNum()<<endl;
    		cout<< " Payment:  $"<< orders[i].get_payment()<<endl;
    	}
    }
}

void customer::showOrders(){
    for(int i=0; i < orders.size(); i++){
    		cout<<"-------------------"<<endl;
    		cout<< "Order Id: "<< orders[i].get_orderID()<<endl;
    		cout<< " Date: "<< orders[i].get_date()<<endl;
    		cout<< " Number: "<< orders[i].get_tribbleNum()<<endl;
    		cout<< " Payment:  $"<< orders[i].get_payment()<<endl;
    	}
}



#endif /*CUSTOMER_H_ */
