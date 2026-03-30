#include <iostream>
using namespace std;
#include "model.h"
#include <fstream>



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

// Python code I had left over that includes some ascii for making a gameboard could use it for table display
// def display(gb):
//     # 2D array representing game board
//     print("\u250f\u2501\u2533\u2501\u2533\u2501\u2513")
//     print("\u2503", gb[0][0],"\u2503", gb[0][1], "\u2503", gb[0][2], "\u2503", sep='')
//     print("\u2523\u2501\u254b\u2501\u252b\u2501\u252b")
//     print("\u2503", gb[1][0],"\u2503", gb[1][1], "\u2503", gb[1][2], "\u2503", sep='')
//     print("\u2523\u2501\u254b\u2501\u252b\u2501\u252b")
//     print("\u2503", gb[2][0],"\u2503", gb[2][1], "\u2503", gb[2][2], "\u2503", sep='')

