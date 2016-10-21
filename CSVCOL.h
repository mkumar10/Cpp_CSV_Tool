/**
* @file CSVCOL.h
* @author Maghav Kumar
* @date Created: October 11th, 2016
* @date Modified :
*/

#ifndef CSVCOL_H
#define CSVCOL_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <functional>

using namespace std;

class CSVCOL {

public:
  CSVCOL();  // Constructor
  CSVCOL(vector<string> col_temp); // Copy Constructor
  void print_statistics(); // Print stats of a particular column
  vector<string> col;  // Has the data of a column
  int col_idx;  // column index

  // Helper for stats
  vector<double> merge_sort(vector<double> column); 
  vector<double> merge(vector<double> l_arr,vector<double> r_arr);
};

#endif
