#include "CSVTOOL.h"

/*
 CSV Tool constructor. Initializes the data vector.
 */
CSVTOOL::CSVTOOL()
{
  data.resize(0);
}
/*
 CSV Tool constructor. Fills the data vector with contents of a
 file specified by the user.
 */
CSVTOOL::CSVTOOL(string fname)
{
  ifstream file_data(fname);
  string line;
  char sep = ',';
  while(getline(file_data,line))
  {
    auto temp = read_record(line,sep);
    if(data.size()==0)
    {
      data.resize(temp.size()); // updates the data matrix size with respect to the number of columns found in the first row
      update_col_indices();
    }
    update_data_matrix(temp);

  }
}

//Helper Function
/*
 Updates the data matrix such that for every element in a particular row of data
 fills in the data to every column of the data matrix.
 */
void CSVTOOL::update_data_matrix(vector<string> temp)
{
  for(int i=0;i<data.size();i++)
  {
    data[i].col.push_back(temp[i]);
  }
}

//Helper Function
/*
  Reads a row from a file and fills it into a vector
  to be used for filling into the data matrix
*/
vector<string> CSVTOOL::read_record(string line,char sep)
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

/*
  updates the column indices for
  later use.
*/
void CSVTOOL::update_col_indices()
{
  for(int i=0;i<data.size();i++)
  {
    data[i].col_idx = i;
  }
}
/*
  Prints the whole data matrix.
  Reuses the print the particular columns function.
*/
void CSVTOOL::print_data()
{
    vector<int> arr;
    for(auto j=0;j<data.size();j++)
    {
      arr.push_back(j);
    }
    print_particular_cols(arr);
}
/*
  Prints the particular columns specified
  by the user in an array.
*/
void CSVTOOL::print_particular_cols(vector<int> arr)
{
  for(int i=0;i<data[0].col.size();i++)
  {
    for(int j=0;j<arr.size();j++)
    {
      cout<<data[arr[j]].col[i]<<'\t';
    }
    cout<<endl;
  }
}
/*
  Adds a new column to the data matrix
  with the formula specified between 2 column indices
  input by the user
*/
void CSVTOOL::add_new_column(int col1_idx,int col2_idx,char operation)
{
  cout<<data.size()<<endl;
  vector<string> new_col;   // new column vector to be added to the data matrix
  vector<double> temp_calc; // temporary vector for the mathematical calculation
  temp_calc.reserve(data[col1_idx].col.size());

  //Converting the first column for mathematical computation into a temporary column
  vector<double> col1(data[col1_idx].col.size());
  transform(data[col1_idx].col.begin(),data[col1_idx].col.end(), col1.begin(),[](const string& val){
     return stod(val);
  });

  //Converting the second column for mathematical computation into a temporary column
  vector<double> col2(data[col2_idx].col.size());
  transform(data[col2_idx].col.begin(),data[col2_idx].col.end(),col2.begin(), [](const string& val)
  {
    return stod(val);
  });

  // Performing the operation specified by the user
  // Using the transfrom method of STL
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
  else if(operation=='/')
  {
    transform(col1.begin(), col1.end(), col2.begin(),
                   back_inserter(temp_calc), divides<double>());
  }

  // Transform the new column of double type to string
  // to append to the data matrix
  transform(begin(temp_calc),
               end(temp_calc),
               back_inserter(new_col),
               [](double d) { return to_string(d); }
              );
  CSVCOL temp; // new CSVCOL for pushing back to the data matrix of CSVCOL type
  temp.col = new_col;
  data.push_back(temp);
}
