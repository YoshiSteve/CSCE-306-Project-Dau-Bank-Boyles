/*
 * menu.cpp
 *
 *  Created on: Feb 16, 2026
 *      Author: Mack Dau
 */

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "model.h"
#include "trans_class.h"
#include "SalesReport.h"
using namespace std;

int main() {
    string option;
import(); //Function that imports the data into an array for use
employeeImport();
load_orders();
importRainbow();

generateSalesReport();

    while (true) {

        //Menu logic, prompts user to enter a number then runs programs
        cout << "Welcome! Please Type the number of the option you want." << endl;
        cout << "1. Add a Customer \n" << "2. Search for a customer \n" << "3. Customer Sale \n" << "4. Add to Rainbow Waitlist\n"<< "5. Show Sales Report\n" << "6. Customer Portal\n" << "0. Exit" << endl;
        getline(cin, option);
        if (option == "1") {
            //Add logic
            cout << "Running Customer Add" << endl;
            customerAdd();
        }
        else if (option == "2") {
            int foundIndex;
            string selection;
            string id;
            while (true) {
                cout << "Running Customer Search" << endl;
                cout << "Search by 1. ID or 2. Last Name? Enter selection number: ";
                getline(cin, selection);
                if (selection == "1") {

                    cout << "What is the ID you want to search for?: ";
                    getline(cin, id);
                    foundIndex = searchId(id);
                    break;
                }
                else if (selection == "2") {
                    string lastName;
                    cout << "What is the last name you want to search for?: ";
                    getline(cin, lastName);
                    foundIndex = searchName(lastName);
                    break;
                }
                else {
                    cout << "Invalid Selection" << endl;
                    
                }
            }
            if (foundIndex == -1) {
                cout << "No customer found" << endl;
            }
            else {
                customer foundCust = getRecord(foundIndex);
                foundCust.print();
            }

        }
        else if (option == "3") {
            string input;
            string c_id;
            double price;
            string month;
            string day;
            string year;
            string shortened_year;
            string merged_date;
            string amount;
            int customer_index;
            while (true) {
                // get customer ID info
                while (true) {

                    
                    cout << "Enter Customer ID of the buyer:";
                    getline(cin, c_id);
                    customer_index = searchId(c_id);
                    if (customer_index != -1) { break; }
                    cout << "Customer ID does not exist" << endl;
                    break;
                }
                if (customer_index == -1) { break; }
                while (true) {
                    // Get year info
                    cout << "\nEnter the current day of the month: ";
                    getline(cin,day);
                    cout << "\nEnter the current month abbreviation (January = Jan): ";
                    getline(cin,month);
                    cout << "\nEnter the current year: ";
                    getline(cin,year);
                    int int_year = stoi(year) % 100;
                    shortened_year = to_string(int_year);
                    merged_date = day + "-" + month + "-" + shortened_year;
                    break;

                }
                while (true) {
                	string choice;
                    // get tribble amount and price buyer wants
                	cout<< "\nWould you like to buy regular or rainbow tribbles? (1 for regular,  2 for rainbow): ";
                	getline(cin,choice);
                	if( choice=="1"){
                    cout << "\nEnter the amount of tribbles the customer wants to buy: ";
                    try {
                    	getline(cin,amount);
                        price = get_price(stoi(amount));
                        break;
                    }
                    catch (invalid_argument) {
                        cout << "You can only buy between 1 and 5 tribbles" << endl;;
                    }

                	}
                    if(choice=="2"){
                    		c_id=sellRainbow(merged_date);
                    		amount=1;
                    		price=0;
                    		break;


                    }

                }
                // confirm data and write to files
                cout << "Are you sure about this info" << endl;
                cout << "Input '1' for yes, '2' for no" << endl;
                cout << " " << endl;
                cout << "ID: " << c_id << endl;
                cout << "Date: " << merged_date << endl;
                cout << amount << " Tribbles for $" << price << endl;
                getline(cin,input);
                if (input == "1"){
                    write_order(c_id, merged_date, stoi(amount), price);
                    cout << " " << endl;
                    break;
                }
            }
        }

        else if(option=="4"){
        	string id;
        	cout<<"Please enter customer ID:"<<endl;
        	getline(cin,id);
        	orderRainbow(id);
        }
        else if (option == "5") {
            printSalesReport();
        }
        else if (option == "6") {
            //Customer Menu
            bool customer_match;
            customer * foundCust;
            while (true) {
                string c_id;
                string pass;
                //Asks for id and password then checks them
                cout << "Please Sign in or '0' for both inputs to Exit the Menu" << endl;
                cout << "Enter Customer ID: " << endl;
                getline(cin, c_id);
                cout << "Enter Password: " << endl;
                getline(cin,pass);
                // Confirmation functions
                customer_match = check_Password(c_id, pass); // temp var until functions exist
                if (customer_match) {
                    foundCust = &customerList[searchId(c_id)];;
                    break;
                }
                else if (c_id == "0" && pass == "0") {
                    break;
                }
                else {
                    cout << "Incorrect Username or Password" << endl;
                }
            } 
            if (customer_match){
                string cust_choice;
                string password;
                while (true) {
                    cout << "Welcome " << foundCust->get_first_name() << "!" << endl;
                    cout << "Please enter the number of the option you want" << endl;
                    cout << "1. Change Password \n2. Order History \n3. Place Order \n0. Exit" << endl;
                    cout << " \n";
           
                    getline(cin, cust_choice);
                    if (cust_choice == "1") {
                        //change password logic
                        cout << "Enter a new password:";
                        getline(cin, password);
                        cout << endl;
                        foundCust->set_password(password);
                        cout << "New password set to " << password << "." << endl;
                    }
                    else if (cust_choice == "2") {
                        cout << "Displaying Orders" << endl;
                        foundCust->showOrders();
                    }
                    else if (cust_choice == "3") {
                        while(true){
                        //Place Order Logic
                        string input;
                        string c_id = foundCust->get_id();
                        double price;
                        //Uses time library in place of having user input time
                        time_t rawtime;
                        struct tm * timeinfo;
                        char cmonth [20];
                        char cday [20];
                        char cyear [20];
                        time (&rawtime);
                        timeinfo = localtime (&rawtime);
                        strftime (cmonth,20,"%b",timeinfo);
                        strftime (cday,20,"%d",timeinfo);
                        strftime (cyear, 20, "%g", timeinfo);
                        string month = string(cmonth);
                        string day = string(cday);
                        string year = string(cyear);
                        string merged_date;
                        string amount;
                        int customer_index;
    
                            merged_date = day + '-' + month + '-' + year;
                                

                            
                            while (true) {
                                cout << "\nHow many tribbles do you want to buy? (1 to 5): ";
                                
                                try {
                                    getline(cin, amount);
                                    price = get_price(stoi(amount));
                                    break;
                                }
                                catch (invalid_argument) {
                                    cout << "You can only buy between 1 and 5 tribbles" << endl;;
                                }
                            }
                            
                            // confirm data and write to files
                            cout << "Are you sure about this info" << endl;
                            cout << "Input '1' for yes, '2' for no" << endl;
                            cout << amount << " Tribbles for $" << price << endl;
                            getline(cin,input);
                            if (input == "1"){
                                write_order(c_id, merged_date, stoi(amount), price);
                                cout << " " << endl;
                                break;
                            }
                        }
                    }
                    else if (cust_choice == "0") {
                        cout << "Bye!" << endl;
                        cout << " \n";
                        break;
                    }
                    else
                    {
                        cout << "Option not available" << endl;
                        cout << " \n";
                        continue;
                    }
                }
                }
            }
        else if (option == "0") {
            cout << "Bye!" << endl;     
            break;

        }
        else {
            cout << "Invalid Option" << endl;
            cout << " \n" << endl;
            continue;
        }
    }
    save();
}

    

