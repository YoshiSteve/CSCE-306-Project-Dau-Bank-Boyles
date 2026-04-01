#include <iostream>
using namespace std;
#include "model.h"
#include <fstream>
#include <sstream>
#include <string>



void generateSalesReport() {

	ofstream report("SalesReport.txt");
	if (!report.is_open()){
		cout << "Error Exporting to SalesReport.txt";
		return;
	}
	for (int i = 0; i < employeeList.size(); i++) {
		Employee* curr_emp = employeeList[i];
		report << curr_emp->get_Name() << ";"<< curr_emp->total_Sales() << ";" << curr_emp->get_commission() << endl;
	}

	report.close();
	cout << "Successfully Generated Sales Report!" << endl;
}

void printSalesReport() {
	string data, name, sales, comission;
	ifstream sReport("SalesReport.txt");
	if (!sReport.is_open()) {
		cout << "Error Opening SalesReport.txt" << endl;
	}
	cout << " " << endl;
	while (getline(sReport, data)) {
		stringstream ss(data);
		getline(ss, name, ';');
		getline(ss, sales, ';');
		getline(ss, comission, ';');
		cout << "Name: " << name << "\tSales: " << sales << "\tCommisions: " << comission << endl;
	}
}
