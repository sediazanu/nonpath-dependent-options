#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>  // std::vector
#include <string>  // std:: stold
#include <iomanip> // std::setprecision
#include "ReadCSVFile.h"
#include "PathDependentOptions.h"
#include "TriPath.h"
using namespace std;

double PathDependentOptions::PriceByExpectation(TriPath Model)
{
int h =Model.Get_h();  //gets a counter that is used to run through each of the option types
    double r = Model.Get_r(); //gets the r obtained from the csv file
    int T = Model.Get_T(); //obtains the time period
    int N = Model.Get_N(); //obtains the number of time steps
    int pricepath=pow(3,N); //obtains the number of steps used in the path
    int* path = new int[N]; //path used to point to each of the funtctions
    double* prices = new double[N+1]; //prices used to point in each function
    StockType1 test1;
    vector<vector<string>> test;
    double S0 =Model.Get_S0();
    double B;
    double K;
    int M;
    if(S0==120)
    {
        B=160;    //sets B barrier for the Tesla derivative
        K=130;    //Sets K Strike for the Tesla Derivative
        M=2;      //Sets M period-limit for the Tesla derivative
    }
    if(S0==150)
    {
        B=200;//sets B barrier for the Ford derivative
        K=160;//Sets K Strike for the Ford Derivative
        M=2;//Sets M period-limit for the Ford derivative
    }
    double expected; //this stores the expected payoff for each option.
    AsianOption as; //obtains object from class asianoption
LookbackOption Lo; //obtains object from class lookback
KnockoutOption Kn; //obtains object from knockout
ParisianOption Pa; //obtains object from parisian


if (h==1)
{
    for(int i=1;i<=pricepath;i++)
    {
        Model.PathByNumber(i,path);
        Model.PriceByPath(path,prices);
        expected += Model.ProbabilityByPath(path)*as.Payoff(prices,N);
    }
}
if (h==2)
{
    for(int i=1;i<=pricepath;i++)
    {
        Model.PathByNumber(i,path);
        Model.PriceByPath(path,prices);
        expected += Model.ProbabilityByPath(path)*Lo.Payoff(prices,N);
    }
}

if (h==3)
{
    for(int i=1;i<=pricepath;i++)
    {
        Model.PathByNumber(i,path);
        Model.PriceByPath(path,prices);
        expected += Model.ProbabilityByPath(path)*Kn.Payoff(prices,N,K,B);
    }
}

if (h==4)
{
    for(int i=1;i<=pricepath;i++)
    {
        Model.PathByNumber(i,path);
        Model.PriceByPath(path,prices);
        expected += Model.ProbabilityByPath(path)*Pa.Payoff(prices,N,K,B,M);
    }
}
double finalprice;
finalprice = pow(1/(1+r),T)*expected; // Stores the final price using equation (2)

return finalprice;





}


