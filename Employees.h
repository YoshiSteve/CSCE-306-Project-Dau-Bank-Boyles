/*
 * Employees.h
 *
 * Author: Stella & Mack
 *
 * Mack: I have modified the file, in order to import stuff correctly the manager needs to have a boss id, so I have removed the
 * Sales employee class and put everything under employee
 *
 * 
 */
#ifndef EMPLOYEES_H_
#define EMPLOYEES_H_
#include <vector>
#include <string>
#include "Ordering.h"

using namespace std;

class Employee{
protected:
    string title; 
    string name; 
    string salesID;
    string bossID; 
    vector<Ordering> sales; 
public:
    virtual string get_title(){return title;}
    virtual string get_Name(){return name;}
    virtual void set_name(string n){name=n;}
    virtual string get_SalesID(){return salesID;}
    virtual void set_SalesID(string id){salesID= id;}
    virtual void add_Sale(Ordering order){sales.push_back(order);}
    // Use ordering object to display sales 
    virtual void display_Sales(); 
    // function to be overwritten by different types of employees
    virtual double get_commission(){return 0;}
    // helper function to at total sale prices to calculate commission
    virtual double total_Sales();
    virtual string get_bossID(){return bossID;}
    virtual void set_bossID(string id){bossID=id;} 
};


class Sales: public Employee{
private: 
public:
    Sales(){title="Sales";}
    double get_commission() override{
        return total_Sales()*0.05;
    }
};

class SuperSales: public Employee{
public:
    SuperSales(){title="SuperSales";}
    double get_commission() override{
        return total_Sales()*0.065; 
    }
};

class Supervisor: public Employee{
protected:
public:
    void displaySubordinates();
    // vector of salespeople they supervise 
    vector<Employee *>oversight;
    Supervisor(){title="Supervisor"; }
    void add_employee(Employee * o){oversight.push_back(o);}
    double get_commission() override; 
}; 
 
class Manager: public Employee{
private:
    // vector of people they supervise 
    vector<Supervisor *> oversee; 
public:
    Manager(){title="Manager";}
    void addSubordinate(Supervisor * e){oversee.push_back(e);}
    double get_commission() override;
    void displaySubordinates();
}; 
double Employee::total_Sales(){
    double total; 
    for(auto element:sales){
        total+= std::stod(element.get_payment()); 
    }
    return total; 
};

void Employee:: display_Sales(){
    cout<<"Title:" << title <<" Name:" << name << " Sales ID:"<< salesID << endl;
    cout << "Commission: $" << get_commission() << endl;
    cout << "Sales:" << endl;
    for(auto element:sales){
        cout <<"Order ID:" << element.get_orderID() << endl; 
    }
}



double Supervisor::get_commission(){
    double supTotal=total_Sales() * 0.065; 
    double empTotal; 
    
    // calculates total sales from salespeople they supervise
    for (auto element:oversight){
        empTotal+=element->total_Sales();
    }
    empTotal *= 0.03; 

    return supTotal+empTotal; 
    
}; 

double Manager::get_commission(){
    double manTotal= total_Sales() * 0.065; 
    double empTotal; 

    // calculates total of supervisor and supervisors salespeoples total commission
    for(auto element:oversee){
        empTotal+= element->total_Sales();
        for (auto it: element->oversight){
            empTotal+=it->total_Sales(); 
        }
    }
    empTotal *= 0.03;

    return manTotal + empTotal;    
};

void Supervisor::displaySubordinates(){
    cout << "Oversees:" << endl;
    for(auto o: oversight){
        cout << o->get_Name() << endl;
    }
}

void Manager::displaySubordinates(){
    cout << "Oversees:" << endl;
    for(auto o: oversee){
        cout << o->get_Name() << endl;
    }
}


#endif