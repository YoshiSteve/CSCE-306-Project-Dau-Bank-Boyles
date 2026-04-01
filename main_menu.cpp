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
        cout << "1. Add a Customer \n" << "2. Search for a customer \n" << "3. Customer Sale \n" << "4. Add to Rainbow Waitlist\n"<< "5. Show Sales Report\n" <<"0. Exit" << endl;
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
            int amount;
            int customer_index;
            while (true) {
                // get customer ID info
                while (true) {

                    
                    cout << "Enter Customer ID of the buyer:";
                    cin >> c_id;
                    customer_index = searchId(c_id);
                    if (customer_index != -1) { break; }
                    cout << "Customer ID does not exist" << endl;
                    break;
                }
                if (customer_index == -1) { break; }
                while (true) {
                    // Get year info
                    cout << "\nEnter the current day of the month: ";
                    cin >> day;
                    cout << "\nEnter the current month abbreviation (January = Jan): ";
                    cin >> month;
                    cout << "\nEnter the current year: ";
                    cin >> year;
                    int int_year = stoi(year) % 100;
                    shortened_year = to_string(int_year);
                    merged_date = day + "-" + month + "-" + shortened_year;
                    break;

                }
                while (true) {
                	string choice;
                    // get tribble amount and price buyer wants
                	cout<< "\nWould you like to buy regular or rainbow tribbles? (1 for regular,  2 for rainbow): ";
                	cin >> choice;
                	if( choice=="1"){
                    cout << "\nEnter the amount of tribbles the customer wants to buy: ";
                    try {
                    	cin >> amount;
                        price = get_price(amount);
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
                cin >> input;
                if (input == "1"){
                    write_order(c_id, merged_date, amount, price);
                    cout << " " << endl;
                    break;
                }
            }
        }

        else if(option=="4"){
        	string id;
        	cout<<"Please enter customer ID:"<<endl;
        	cin>>id;
        	orderRainbow(id);
        }
        else if (option == "5") {
            printSalesReport();
 }
        else if (option == "0") {
            cout << "Bye!";
            
            break;

        }
        else {
            cout << "Invalid Option" << endl;
        }
    }
}
