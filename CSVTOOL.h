/**
* @file Csv_tool.h
* @author Maghav Kumar
* @date Created: October 11th, 2016
* @date Modified :
*/

#ifndef CSVTOOL_H
#define CSVTOOL_H

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include "CSVCOL.h"
using namespace std;

class CSVTOOL {
//private:


public:
  vector<CSVCOL> data; // The data matrix of CSV columns
  CSVTOOL();   // Constructor
  CSVTOOL(string fname); // Constructor that reads from a file
  
  void print_data(); // Printing entire data matrix
  void print_particular_cols(vector<int> arr); // Printing particular columns
  void add_new_column(int col1_idx,int col2_idx,char operation); // Adding a new column with respect to a particular operation
  void update_col_indices(); // Update teh column indices

  //Helper Functions
  void update_data_matrix(vector<string> temp);
  vector<string> read_record(string line,char sep);
};


#endif
