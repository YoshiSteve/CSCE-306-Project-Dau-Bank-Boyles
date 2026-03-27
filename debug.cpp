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
#include <vector>
#include "model.h"
#include "trans_class.h"

using namespace std;

int main(){
    employeeImport();
    import();
    load_orders();
    for(auto element:employeeList){
        element->display_Sales();
    }
}