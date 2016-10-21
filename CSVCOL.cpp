#include "CSVCOL.h"

/*
 CSV column constructor. Initializes the data vector.
 */
CSVCOL::CSVCOL()
{
  col.resize(0);
}
/*
 CSV column copy constructor. Equates the data vector to another vector.
 */
CSVCOL::CSVCOL(vector<string> col_temp)
{
  col = col_temp;
}

/*
  Merge function for the Merge Sort
 */
vector<double> CSVCOL::merge(vector<double> l_arr,vector<double> r_arr)
{
  vector<double> res;
  while(l_arr.size()>0 || r_arr.size()>0)
  {
    if(l_arr.size() > 0 && r_arr.size()>0)
    {
      if(l_arr.front() <= r_arr.front())
      {
        res.push_back(l_arr.front());
        l_arr.erase(l_arr.begin());
      }
      else
      {
        res.push_back(r_arr.front());
        r_arr.erase(r_arr.begin());
      }
    }
    else if(l_arr.size()>0)
    {
      for(int i=0;i<l_arr.size();i++)
        res.push_back(l_arr[i]);
      break;
    }
    else if(r_arr.size()>0)
    {
      for(int i=0;i<r_arr.size();i++)
        res.push_back(r_arr[i]);
      break;
    }
  }
    return res;
}

/*
  Merge Sort Helper for sorting a vector and using it to find statistics
  of a column.
 */
vector<double> CSVCOL::merge_sort(vector<double> column)
{
  if(column.size() <=1)
    return column;

  vector<double> l_arr;
  vector<double> r_arr;
  vector<double> res;
  int mid = (column.size()+1)/2;

  for(int i=0;i<mid;i++)
  {
    l_arr.push_back(column[i]);
  }
  for(int i=mid;i<column.size();i++)
  {
    r_arr.push_back(column[i]);
  }

  l_arr = merge_sort(l_arr);
  r_arr = merge_sort(r_arr);
  res = merge(l_arr,r_arr);
  return res;
}


/*
  Prints stats of a column
 */
void CSVCOL::print_statistics()
{
  const auto size_of_col = col.size();  // finds the size of data vector
  vector<double> col_numerical(size_of_col);
  transform(col.begin(),col.end(), col_numerical.begin(),[](const string& val){
     return stod(val);
  }); // converts the column to double for sorting and for finding statistics

  //sort(col_numerical.begin(),col_numerical.end());

  col_numerical = merge_sort(col_numerical);  // sort the column
  auto max_col = col_numerical[size_of_col-1]; // max value is the last value in the column
  auto min_col = col_numerical[0];            // min value is the first value in the column
  auto average_col = accumulate(col_numerical.begin(),col_numerical.end(),0.0)/size_of_col; // average is the sum of all values divided by the total number of values
  auto median=0.0;
  if(col_numerical.size()%2==0) // the median when there are even number of elements
  {
    median = (col_numerical[size_of_col/2 - 1] + col_numerical[size_of_col/2])/2;
  }
  else
  {
    median = col_numerical[size_of_col/2]; // the median when there are odd number of elements
  }
  cout<<"The max of this column is "<< max_col<<endl;
  cout<<"The min of this column is "<< min_col<<endl;
  cout<<"The average of this column is "<< average_col<<endl;
  cout<<"The median of this column is "<< median<<endl;
}
