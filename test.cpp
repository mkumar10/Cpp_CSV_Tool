#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <chrono>
#include <numeric>

using namespace std;


// Function to print the entire matrix of data
void print_data(vector<vector<string> > data)
{
  for(auto i=0;i<data[i].size();i++)
  {
    for(auto j=0;j<data.size();j++)
    {
      cout<<data[j][i];
      cout<<" ";
    }
    cout<<endl;
  }
}


// Function to read a particular line
// line - record line
// sep is the separator
vector<string> read_record(string line,char sep)
{
  vector<string> temp;
  stringstream lineStream(line);
  string cell;
  while(getline(lineStream,cell,sep))
  {
    temp.push_back(cell);
  }
  return temp;

}


// updating the data matrix
// Pushing back to vector of columns
void update_data_matrix(vector<vector<string> > &data, vector<string> temp)
{
  for(int i=0;i<data.size();i++)
  {
    data[i].push_back(temp[i]);
  }
  return;
}



// Printing particular columns
// arr consists of the indices of the columns to print
void print_particular_cols(vector<vector<string> > data, vector<int> arr)
{

  for(int i=0;i<data[i].size();i++)
  {
    for(int j=0;j<arr.size();j++)
    {
      cout<<data[arr[j]][i];
      cout<<" ";
    }
    cout<<endl;
  }
}

// data - data matrix
// col1_idx - column 1 index
// col2_idx - column 2 index
// operation - type of operation to perform

void add_new_column(vector<vector<string> > &data, int col1_idx,int col2_idx, char operation)
{
  vector<string> new_col;
  vector<double> temp_calc;
  temp_calc.reserve(data[col1_idx].size());
  vector<double> col1(data[col1_idx].size());
  transform(data[col1_idx].begin(),data[col1_idx].end(), col1.begin(),[](const string& val){
     return stod(val);
  });

  vector<double> col2(data[col2_idx].size());
  transform(data[col2_idx].begin(),data[col2_idx].end(),col2.begin(), [](const string& val)
  {
    return stod(val);
  });

  if(operation=='+')
  {
    transform(col1.begin(), col1.end(), col2.begin(),
                   back_inserter(temp_calc), plus<double>());
  }
  else if(operation=='-')
  {
    transform(col1.begin(), col1.end(), col2.begin(),
                   back_inserter(temp_calc), minus<double>());
  }
  else if(operation=='*')
  {
    transform(col1.begin(), col1.end(), col2.begin(),
                   back_inserter(temp_calc), multiplies<double>());
  }
  else if(operation=='/')
  {
    transform(col1.begin(), col1.end(), col2.begin(),
                   back_inserter(temp_calc), divides<double>());
  }

  transform(begin(temp_calc),
               end(temp_calc),
               back_inserter(new_col),
               [](double d) { return to_string(d); }
              );
  data.push_back(new_col);
}

// Write merge sort on arr
// Find min = arr[0]
// Find max = arr[arr.size()-1]
// Find median = formula
// mean/average = std::accumulate
/*void sort_vector(vector<double> &col)
{





}*/
void print_statistics(vector<string> col)
{
  const auto size_of_col = col.size();
  vector<double> col_numerical(size_of_col);
  transform(col.begin(),col.end(), col_numerical.begin(),[](const string& val){
     return stod(val);
  });
  sort(col_numerical.begin(),col_numerical.end());
  auto max_col = col_numerical[size_of_col-1];
  auto min_col = col_numerical[0];
  auto average_col = accumulate(col_numerical.begin(),col_numerical.end(),0.0)/size_of_col;
  auto median=0.0;
  if(col_numerical.size()%2==0)
  {
    median = col_numerical[size_of_col/2 - 1] + col_numerical[size_of_col/2];
  }
  else
  {
    median = col_numerical[size_of_col/2];
  }
  cout<<"The max of this column is "<< max_col<<endl;
  cout<<"The min of this column is "<< min_col<<endl;
  cout<<"The average of this column is "<< average_col<<endl;
  cout<<"The median of this column is "<< median<<endl;
}


// inner join





// outer join



int main()
{
  //auto start = chrono::high_resolution_clock::now();
  ifstream file_data("ratings.csv"); // file data
  string line;
  vector<vector<string> > data; // matrix of data
  char sep = ','; // type of separator
  while(getline(file_data,line))
  {
    auto temp = read_record(line,sep);
    if(data.size()==0)
    {
      int num_of_cols = temp.size();
      data.resize(num_of_cols);
    }
    update_data_matrix(data,temp);

  }
  //add_new_column(data,2,3,'/');
  //cout<<data[0].size()<<endl;

  print_data(data);
  // This code is for checking time taken for code to run. Shift start to start of code
  //print_statistics(data[3]);
  //auto start = chrono::high_resolution_clock::now();
  //auto elapsed = chrono::high_resolution_clock::now() - start;
  //long long microseconds = chrono::duration_cast<chrono::microseconds>(elapsed).count();
  //cout<<microseconds<<endl;


  //vector<int> arr;
  //arr.push_back(1);
  //arr.push_back(3);
  //arr.push_back(5);
  //print_particular_cols(data,arr);

  return 0;
}
