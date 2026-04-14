/*
 * model.h
 *
 *  Created on: Feb 21, 2026
 *      Author: Mack Dau
 * Goal : File that includes functions to parse data and edit data
 *
 * Includes: Customer records (address, name etc.), created random Ids for users. can search and add customers
 * Phase 3 Modifications: Added Employee Import and Search functions
 */
#ifndef MODEL_H_
#define MODEL_H_
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include "customer.h"
#include "Employees.h"

using namespace std;
std::vector<customer> customerList;
std::vector<Employee*> employeeList;
customer getRecord(int index){
    return customerList[index];
}

void import(){
    //Function to import customer records for quicker searching
    customerList.clear(); //Clears customer list so that importing again updates
    string storage[8];
    string temp;
    string fileIn;
    int size;
    char filename[] = "customers.txt";
    ifstream infile(filename, ios::in); 
    if (!infile) {
        cerr << "Error - cannot open "<< filename << endl;
        exit (1);
    }
    cout << "Importing Customer Records" << endl;
    while (!infile.eof()){
        getline(infile, fileIn); //Gets file and stores into fileIn
        stringstream data(fileIn); //converts fileIn to stringstream and stores into data
        int i = 0;
        while(getline(data, temp, ';')){
            //Runs until end of current line
            storage[i] = temp; //stores current piece of data into storage array
            i++;
        }

        //Creates a customer using the given data from storage then places into an array for later access
        customerList.push_back(customer(storage[0], storage[2], storage[3], storage[4], storage[5], storage[6], storage[7], storage[1]));
}
    infile.close();
}

int searchName(string lastName){
    //Function that finds a customer by Name returns the index of that customers location in the customer list vector, if no customer returns -1
    std::vector<int> foundCustomers;
    string selectedNumber;
    //Loop for locating customers with given last name and placing their index location into a vector for later
    for(int i = 0; i < customerList.size(); i++){
        if (customerList[i].get_last_name() == lastName){
            foundCustomers.push_back(i);
        }
    }
    //If only one customer is found returns the index of that customer
    if (foundCustomers.size() == 1){
        return foundCustomers[0];
    }
    //If more than one is found prompts the user to pick a customer and displays each customer with a number attached, then returns selected customers index
    else if(foundCustomers.size()> 1){
        cout << "Multiple Customers Found. Please Type the number of the customer you want to select." << endl;
        for(int i=0; i<foundCustomers.size(); i++){
            cout << "Customer " << i << ":" << endl;
            customerList[foundCustomers[i]].print();
        }
        cout << "Enter a number: ";
        getline(cin, selectedNumber);
        int selectedInt = stoi(selectedNumber);
        return foundCustomers[selectedInt];
    }
    //If no customer is found returns -1
    return -1;
}

int searchId(string id){
    //Function that finds a customer by ID returns the index of that customers location in the customer list vector, if no customer returns -1
    string selectedNumber;
    //Loop for locating customer with given ID
    for(int i = 0; i < customerList.size(); i++){
        if (customerList[i].get_id() == id){
            return i;
        }
    }
    //if no customer found returns -1
    return -1;
}


int searchEmployee(string id){
    //Function that finds a customer by ID returns the index of that customers location in the customer list vector, if no customer returns -1
    string selectedNumber;
    //Loop for locating customer with given ID
    for(int i = 0; i < employeeList.size(); i++){
        if (employeeList[i]->get_SalesID() == id){
            return i;
        }
    }
    //if no customer found returns -1
    return -1;
}

void customerAdd(){
    //Prompts user for Inputs and generates unique id then puts customer at back of customer list and puts info into customers.txt
    string id, first_name, last_name, address, city, state, zip_code;
    string password = "tribbles";
    char filename[] = "customers.txt";
    cout << "Enter First Name: ";
    getline(cin, first_name); 
    cout << "Enter Last Name: ";
    getline(cin, last_name);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter city: ";
    getline(cin, city);
    cout << "Enter State: ";
    getline(cin, state);
    cout << "Enter Zip Code: ";
    getline(cin, zip_code);
    //Generator for random Id. Creates random number, makes sure it has 6 digits and puts leading 0s to make id 6 digits,
    // then checks if the id exists. Runs until unique id is made
    while(true){
        int zeros;
        id = to_string(rand());
        zeros = 6 - id.length();
        for(int i = 0; i<zeros; i++){
            id = "0" + id;
        }
        if(searchId(id) == -1){
            break;
        }
    }
    //Places new customer onto customerList vector
    customerList.push_back(customer(id, first_name, last_name, address, city, state, zip_code, password));
    ofstream outfile(filename, ios::app);
    if (!outfile) {
        cerr << "Error - cannot open "<< filename << endl;
        exit (1);
    }
    //Puts new customer at end of file with correct formatting
    outfile << id + ";" + first_name + ";" + last_name + ";" + address + ";" + city + ";" + state + ";" + zip_code + "\n";
    outfile.close();
    cout << "Customer Successfully added!" << endl;
}

void employeeImport(){
    //Function to employees
    employeeList.clear(); //Clears employee list so that importing again updates
    string storage[4];
    string temp;
    string fileIn;
    string filename = "salesStaff.txt";
    int size;
    vector <Manager*> managers;
    vector <Supervisor*> supervisors;
    ifstream infile(filename, ios::in); 
    if (!infile) {
        cerr << "Error - cannot open "<< filename << endl;
        exit (1);
    }
    cout << "Importing Employee Records" << endl;
    while (!infile.eof()){
        getline(infile, fileIn); //Gets file and stores into fileIn
        stringstream data(fileIn); //converts fileIn to stringstream and stores into data
        int i = 0;
        string prevId = storage[2];
        while(getline(data, temp, ';')){
            //Runs until end of current line
            storage[i] = temp; //stores current piece of data into storage array
            i++;
        }
        if (prevId == storage[2]){ //Prevents duplicates and empty lines from importing
            continue;
        }
        //Determines type of employee and creates and employee based on that
        if (storage[0] == "Sales"){
            Sales * employee = new Sales;
            employee->set_name(storage[1]);
            employee->set_SalesID(storage[2]);
            employee->set_bossID(storage[3]);
            employeeList.push_back(employee);

        }
        else if (storage[0] == "SuperSales"){
            SuperSales * employeeptr = new SuperSales;
            employeeptr->set_name(storage[1]);
            employeeptr->set_SalesID(storage[2]);
            employeeptr->set_bossID(storage[3]);
            employeeList.push_back(employeeptr);
        }
        else if (storage[0] == "Supervisor"){
            Supervisor * employeeptr = new Supervisor;
            employeeptr->set_name(storage[1]);
            employeeptr->set_SalesID(storage[2]);
            employeeptr->set_bossID(storage[3]);
            supervisors.push_back(employeeptr);
        }
        else{
            Manager * employeeptr = new Manager;
            employeeptr->set_name(storage[1]);
            employeeptr->set_SalesID(storage[2]);
            employeeptr->set_bossID(storage[3]);
            managers.push_back(employeeptr);
        }

        
}
    infile.close();
    for(auto e:employeeList){
        for (auto s:supervisors){
            if (e->get_bossID() == s->get_SalesID()){
                s->add_employee(e);
            }
        }
    }
    for(auto s:supervisors){
        for(auto m:managers){
            if(s->get_bossID() == m->get_SalesID()){
                m->addSubordinate(s);
            }
        }
        employeeList.push_back(s);
    }
    for(auto m:managers){
        employeeList.push_back(m);
    }

}
bool check_Password(string id, string p){
    string pass=decryptString(p);

    if(searchId(id)==-1){
        return false; 
    }
    customer cust=getRecord(searchId(id));
    if(cust.get_password()==pass){
            return true;
    }
    else{
        return false; 
    }
};

void change_Password(string id, string p){
    string pass= encryptString(p); 
    customer cust=getRecord(searchId(id)); 
    cust.set_password(pass); 
    
}

string findMonth(int month){
    if (month == 1){return "Jan";}
    else if (month == 2){return "Feb";}
    else if (month == 3){return "Mar";}
    else if (month == 4){return "Apr";}
    else if (month == 5){return "May";}
    else if (month == 6){return "Jun";}
    else if (month == 7){return "Jul";}
    else if (month == 8){return "Aug";}
    else if (month == 9){return "Sep";}
    else if (month == 10){return "Oct";}
    else if (month == 11){return "Nov";}
    else if (month == 12){return "Dec";}
    else {return "goober";}
}
#endif
