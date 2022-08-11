#ifndef ReadCSVFile.h
#define ReadCSVFile.h
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;




class StockType1
{
private:


public:
    void ReadCSVfile(vector<vector<string>>& test)

    {
        int r = 0;
        ifstream fin("StockDataMar2022.csv"); //loads the .csv file
        string line;
        test.clear(); //clears the initial vector to avoid issues
        while (r <3 && getline(fin,line))
        {
            vector<string> row;
            stringstream iss(line);
            int c = 0;
            string variable;

            // while c < 4 and getline gives correct result
            while (c < 4 && getline(iss, variable, ','))
            {
                // pushes the row values into the list
                row.push_back(variable);

            } //pushes the entire row into the 2d array
            test.push_back(row);


        }
        fin.close();
    }
 template <typename T>
  void DisplayDoubleVector(const vector<vector<T>>& test)
    {
        for (int i = 0; i < test.size(); i++)
        {
            for (int j = 0; j < test[i].size(); j++)
            {
                cout << test[i][j]<< " ";//gets the value in the position i,j
            }
            cout << endl;
        }
    }
};




#endif





