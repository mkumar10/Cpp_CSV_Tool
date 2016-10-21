#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "CSVTOOL.h"
#include "CSVCOL.h"

using namespace std;

vector<string> file_status; // Stores the files that have been read till yet
/*
 Function to print the number and names of files read.
 */
void print_file_status()
{
  if(file_status.size()==0)
  {
    cout<<"No file has been read till yet"<<endl;
  }
  for(int i=0;i<file_status.size();i++)
  {
    cout<<i<<" - "<<file_status[i]<<endl;
  }
}

/*
 Function to take an input from user for file name
 and reading the file using CSVTOOL Constructor.
 */
CSVTOOL read_file()
{
  cout<<"Please enter the file name:";
  string fname;
  cin>>fname;
  file_status.push_back(fname); // updating file status vector
  CSVTOOL file_csv(fname);
  cout<<fname<<"  has been read."<<endl;
  return file_csv;
}

/*
 Function to print a contents of a csv file
 that user inputs.
 */
void print_file(vector<CSVTOOL> all_files)
{
  print_file_status();
  int num;
  cout<<"Please choose the file number you would like to print:";
  cin>>num;
  if(num<0 || num>all_files.size()-1)
  {
    cout<<"Please enter a valid choice";
    cin>>num;
  }
  all_files[num].print_data();
}
/*
 Function to print particular columns of a particular csv file
 that user inputs.
 */
void read_particular_cols(vector<CSVTOOL> all_files)
{
  print_file_status();
  int siz_of_vec,num;
  if(all_files.size()>1)
  {
    cout<<"Please choose the file number you would like to print from:";
    cin>>num;
    cout<<endl;
  }
  else{
    num =0;
  }
  cout<<"Please enter the number of columns you would like to print:";
  cin>>siz_of_vec;
  cout<<endl;
  while(siz_of_vec>all_files[num].data.size()-1)
  {
    cout<<"Please enter a valid number of columns you would like to print:";
    cin>>siz_of_vec;
    cout<<endl;
  }
  vector<int> arr;
  arr.resize(siz_of_vec);
  cout<<"Now please enter the columns:-"<<endl;
  for(int i=0;i<siz_of_vec;i++)
  {
    int temp;
    cin>>temp;
    if(temp>all_files[num].data.size()-1)
    {
      cout<<"Please enter a valid choice: ";
      i--;
    }
    else
    {
    arr[i] = temp;
    }
  }
  all_files[num].print_particular_cols(arr);
}

/*
 Function to print stats of a column of a particular csv file
 that user inputs.
 */
void print_stats_of_col(vector<CSVTOOL> all_files)
{
  print_file_status();
  int col_num,num;

  cout<<"Please choose the file number you would like to print from:";
  cin>>num;
  cout<<endl;

  while(num>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>num;
    cout<<endl;
  }

  cout<<"Please choose the column number you would like to print:";
  cin>>col_num;
  while(col_num>all_files[num].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_num;
    cout<<endl;
  }
  all_files[num].data[col_num].print_statistics();

}

/*
 Function for adding a new column to a file the user chooses
 using the operation and column indices also provided by the user.
 */
void add_new_col(vector<CSVTOOL> &all_files)
{
  print_file_status();
  int col_idx1,col_idx2,num;

  cout<<"Please choose the file number you would like to print from:";
  cin>>num;
  cout<<endl;

  while(num>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>num;
    cout<<endl;
  }
  cout<<"Enter the first column index:"<<endl;
  cin>>col_idx1;
  cout<<endl;
  while(col_idx1>all_files[num].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_idx1;
    cout<<endl;
  }
  cout<<"Enter the second column index:"<<endl;
  cin>>col_idx2;
  cout<<endl;
  while(col_idx2>all_files[num].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_idx2;
    cout<<endl;
  }
  char operation;
  cout<<"Please enter a valid operation +,-,*,/:";
  cin>>operation;
  all_files[num].add_new_column(col_idx1,col_idx2,operation);
  cout<<"New column has been added to "<<file_status[num]<<endl;
}

/*
 Function for doing an inner join between two files and a column
 for each file to create a new file.
 */

void inner_join(vector<CSVTOOL> &all_files)
{
  print_file_status();
  int file_num1,file_num2;
  cout<<"Choose the number of the first file:";
  cin>>file_num1;
  cout<<endl;

  while(file_num1>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>file_num1;
    cout<<endl;
  }

  cout<<"Choose the number of the second file:";
  cin>>file_num2;
  cout<<endl;

  while(file_num2>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>file_num2;
    cout<<endl;
  }

  int col_num1,col_num2;
  cout<<"Choose the column of the first file:";
  cin>>col_num1;
  cout<<endl;

  while(col_num1>all_files[file_num1].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_num1;
    cout<<endl;
  }

  cout<<"Choose the column of the second file:";
  cin>>col_num2;
  cout<<endl;

  while(col_num2>all_files[file_num2].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_num2;
    cout<<endl;
  }

  map<int,vector<int>> my_map; // String in first file as key ; value is [index of file1, index of file2]

  // make map of elements in map1
  for(int i=0;i<all_files[file_num1].data[col_num1].col.size();i++)
  {
    vector<int> temp;
    temp.push_back(i);
    my_map[stoi(all_files[file_num1].data[col_num1].col[i])] = temp;
  }
  // find the intersection of elements
  for(int i=0;i<all_files[file_num2].data[col_num2].col.size();i++)
  {
    if(my_map.find(stoi(all_files[file_num2].data[col_num2].col[i]))!=my_map.end())
    {
      my_map[stoi(all_files[file_num2].data[col_num2].col[i])].push_back(i);
    }
  }

  // Make the new file
  CSVTOOL new_file;
  CSVCOL curr;
  // resize the file's data matrix of CSV col type
  new_file.data.resize(all_files[file_num1].data.size()+all_files[file_num2].data.size()-1,curr);


  for(auto it = my_map.begin();it!=my_map.end();++it)
  {
    // If map's value vector consists of 2 indices
    // generate a new row and each element to a column
    if(it->second.size()==2)
    {
      vector<string> temp;
      temp.push_back(to_string(it->first));
      int index1 = it->second[0];
      // put the values in temp row vector from file1's row using the index found
      for(int j=0;j<all_files[file_num1].data.size();j++)
      {
        if(j!=col_num1)
        {
          temp.push_back(all_files[file_num1].data[j].col[index1]);
        }
      }
      // put the values in temp row vector from file2's row using the index found
      int index2 = it->second[1];
      for(int j=0;j<all_files[file_num2].data.size();j++)
      {
        if(j!=col_num2)
        {
          temp.push_back(all_files[file_num2].data[j].col[index2]);
        }
      }
      // call update the data matrix to append the row's element to each column
      new_file.update_data_matrix(temp);
    }
  }
  string s;
  s.append("Inner join of ");
  s.append(file_status[file_num1]);
  s.append(" and of ");
  s.append(file_status[file_num2]);
  s.append(" for columns ");
  s.append(to_string(col_num1));
  s.append(" and ");
  s.append(to_string(col_num2));
  file_status.push_back(s); // update the files read vector
  all_files.push_back(new_file); // update the files vector of CSVTOOLS
  cout<<"New file with an Inner join has been created"<<endl;

}

/*
 Function for doing an inner join between two files and a column
 for each file to create a new file.
 */

void outer_join(vector<CSVTOOL> &all_files)
{
  print_file_status();
  int file_num1,file_num2;
  cout<<"Choose the number of the first file:";
  cin>>file_num1;
  cout<<endl;

  while(file_num1>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>file_num1;
    cout<<endl;
  }

  cout<<"Choose the number of the second file:";
  cin>>file_num2;
  cout<<endl;

  while(file_num2>all_files.size()-1)
  {
    cout<<"Please enter a valid choice: ";
    cin>>file_num2;
    cout<<endl;
  }

  int col_num1,col_num2;
  cout<<"Choose the column of the first file:";
  cin>>col_num1;
  cout<<endl;

  while(col_num1>all_files[file_num1].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_num1;
    cout<<endl;
  }

  cout<<"Choose the column of the second file:";
  cin>>col_num2;
  cout<<endl;

  while(col_num2>all_files[file_num2].data.size()-1)
  {
    cout<<"Please enter a valid column number:";
    cin>>col_num2;
    cout<<endl;
  }

  map<int,vector<int>> my_map; // String in first file as key ; value is [index of file1, index of file2]
                                  // if element not in file2 put value as [index of file1, -1]
                                  // if element not in file1 put value as [-1,index of file2]

  // make map of elements in map1
  for(int i=0;i<all_files[file_num1].data[col_num1].col.size();i++)
  {
    vector<int> temp;
    temp.push_back(i);
    temp.push_back(-1);
    my_map[stoi(all_files[file_num1].data[col_num1].col[i])] = temp;
  }

  // find the union of elements and updating the map with respect how specified above
  for(int i=0;i<all_files[file_num2].data[col_num2].col.size();i++)
  {
    if(my_map.find(stoi(all_files[file_num2].data[col_num2].col[i]))!=my_map.end())
    {
      my_map[stoi(all_files[file_num2].data[col_num2].col[i])][1] = i;
    }
    else
    {
      vector<int> temp;
      temp.push_back(-1);
      temp.push_back(i);
      my_map[stoi(all_files[file_num2].data[col_num2].col[i])] = temp;
    }
  }
  // Creating the new file

  CSVTOOL new_file;
  CSVCOL curr;

  // resize the file's data matrix of CSV col type
  new_file.data.resize(all_files[file_num1].data.size()+all_files[file_num2].data.size()-1,curr);

  for(auto it = my_map.begin();it!=my_map.end();++it)
  {
    // Generate a new temporary vector
    // which acts as a row
    vector<string> temp;
    temp.push_back(to_string(it->first));
    int index1 = it->second[0];
    for(int j=0;j<all_files[file_num1].data.size();j++)
    {
      if(j!=col_num1)
      {
        if(index1!=-1) // if index is not -1 append the value of the column at that index to the row vector
          temp.push_back(all_files[file_num1].data[j].col[index1]);
        else      // else append NULL
          temp.push_back("NULL");
      }
    }
    int index2 = it->second[1];
    for(int j=0;j<all_files[file_num2].data.size();j++)
    {
      if(j!=col_num2)
      {
        if(index2!=-1) // if index is not -1 append the value of the column at that index to the row vector
          temp.push_back(all_files[file_num2].data[j].col[index2]);
        else          // else append NULL
          temp.push_back("NULL");
      }
    }
    new_file.update_data_matrix(temp);
  }
  string s;
  s.append("Outer join of ");
  s.append(file_status[file_num1]);
  s.append(" and of ");
  s.append(file_status[file_num2]);
  s.append(" for columns ");
  s.append(to_string(col_num1));
  s.append(" and ");
  s.append(to_string(col_num2));
  file_status.push_back(s);   // update the files read vector
  all_files.push_back(new_file); // update the files vector of CSVTOOLS
  cout<<"New file with an Outer join has been created"<<endl;

}
/*
  main function
*/
int main()
{
  cout<<"Welcome to the world of CSV's"<<endl;
  int choice ;
  vector<CSVTOOL> all_files;

  cout<<"For reading a new file"<<endl;
  all_files.push_back(read_file());
  all_files[0].print_data();

  while(choice!=9)
  {
    cout<<"\nPlease choose what would you like to do"<<endl;
    cout<<"1 - For reading a new file"<<endl;
    cout<<"2 - For printing a file"<<endl;
    cout<<"3 - For printing particular columns of a file"<<endl;
    cout<<"4 - For printing the statistics of a column of a file"<<endl;
    cout<<"5 - For performing an operation on a file and adding a new column"<<endl;
    cout<<"6 - For performing an inner join"<<endl;
    cout<<"7 - For performing an outer join"<<endl;
    cout<<"8 - Print File status"<<endl;
    cout<<"9 - To quit"<<endl;
    cout<<"Enter your choice:";
    cin>>choice;
    cout<<endl;

    if(choice==1)
    {
      all_files.push_back(read_file());
    }
    else if(choice==2)
    {
      print_file(all_files);
    }
    else if(choice==3)
    {
      read_particular_cols(all_files);
    }
    else if(choice==4)
    {
      print_stats_of_col(all_files);
    }

    else if(choice==5)
    {
      add_new_col(all_files);
    }

    else if(choice==6)
    {
      inner_join(all_files);
    }
    else if(choice==7)
    {
      outer_join(all_files);
    }
    else if(choice==8)
    {
      print_file_status();

    }
    else if(choice==9)
    {
      cout<<"Thanks for using this tool."<<endl;
    }
    else
    {
      cout<<"Please enter a valid choice."<<endl;
    }

  }
  return 0;

}
