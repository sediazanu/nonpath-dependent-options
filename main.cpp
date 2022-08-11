
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "ReadCSVFile.h"
#include "TriPath.h"
#include "TriModel.h"
#include "PathDependentOptions.h"

using namespace std;

int main()
{
    StockType1 test1;
    vector<vector<string>> test;
    test1.ReadCSVfile(test);
    test1.DisplayDoubleVector(test);
    double S0 =stod(test.at(2).at(1)); //Obtains the initial Tesla price from the vector
    double r =stod(test.at(2).at(2)); //obtains the Tesla r from the vector
    double sigma =stod(test.at(2).at(3)); //obtains Tesla sigma from the vector


    PathDependentOptions options;

    for(int i=0; i<=4; i++) //gives the user an output for all 4 options required
    {

            TriPath pricing(S0,sigma,r,1,6,i); //takes all the values from above and puts them in the subclass
            if(i==1)
            {
                cout<<"Asian Price: "<<options.PriceByExpectation(pricing)<<endl;
            }
            if(i==2)
            {
                cout<<" Lookback Price: "<<options.PriceByExpectation(pricing)<<endl;
            }
            if(i==3)
            {
                cout<<" Knockout Price: "<<options.PriceByExpectation(pricing)<<endl;
            }
            if(i==4)
            {
                cout<<" Parisian Price: "<<options.PriceByExpectation(pricing)<<endl;
            }

        cout<<endl;
    }


    S0 =stod(test.at(3).at(1)); //Obtains initial Ford price from the vector
    r =stod(test.at(3).at(2)); //obtains initial ford r value from
    sigma =stod(test.at(3).at(3)); //obtains initial ford sigma value


    PathDependentOptions options2;

    for(int i=1; i<=4; i++) //gives the user an output for all 4 options required
    {

            TriPath pricing(S0,sigma,r,1,6,i);
            if(i==1)
            {
                cout<<" Asian Price: "<<options2.PriceByExpectation(pricing)<<endl;
            }
            if(i==2)
            {
                cout<<" Lookback Price: "<<options2.PriceByExpectation(pricing)<<endl;
            }
            if(i==3)
            {
                cout<<" Knockout Price: "<<options2.PriceByExpectation(pricing)<<endl;
            }
            if(i==4)
            {
                cout<<" Parisian Price: "<<options2.PriceByExpectation(pricing)<<endl;
            }

        cout<<endl;
    }
system("pause");
    return 0;

}
