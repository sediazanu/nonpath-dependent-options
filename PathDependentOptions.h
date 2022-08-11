#ifndef PATHDEPENDENTOPTIONS_H
#define PATHDEPENDENTOPTIONS_H
#include "TriPath.h"



/*  CLASS:  PATHDEPENDENTOPTIONS

    The class PathDependentOptions is a pure virtual class which prices path-dependent
    options. Note that the abstract function Payoff has been redefined from the
    BinModel class to take an array of prices by reference.

    You should implement the member function PriceByExpectation in a .cpp file and
    implement each exotic call option by using subclasses.
*/


class PathDependentOptions
{
public:
    virtual double Payoff(double *prices, int N)
    {
        return 0.0;
    }
    double PriceByExpectation (TriPath Model);
};

// Write your subclasses below this line.
class AsianOption : public PathDependentOptions
{
public:
    double Payoff(double *prices, int N)
    {
        double sum=0.0;
        for(int i=1; i<=N; i++) //finds the sum from 1 to N of the array, ignoring t=0
        {

            sum=sum+prices[i];
        }
        double mean = sum/N; //calculates the mean of the prices

        double file=0.0;
        for(int i =1; i <=N; i++)
        {

            if(file < prices[i])
            {
                file = prices[i];   //Leaves the largest value obtained from the price path.
            }
        }
        double finprice =file - mean; //takesaway the arithmetic mean from the largest value.
        if(finprice<=0)
        {
            finprice=0;   //sets value to 0 if the remainder is 0 or negative
        }
        return finprice;

    }
};

class LookbackOption : public PathDependentOptions
{
public:
    double Payoff(double *prices, int N)
    {
        double file=prices[N]; //sets file to be the final value in the prices array.
        for(int i = 0; i <= N; i++)
        {

            if(file > prices[i])
            {
                file = prices[i];
            }
        }
        double finprice= prices[N]-file; //takes away the maximum value from the current value and checks
                                         //to see if the remaining value is less than or equal to 0
        if (finprice<=0)
        {
            finprice=0;   //sets value to 0 if the remainder is 0 or negative
        }
        return finprice;


    }
};
class KnockoutOption : public PathDependentOptions
{
public:
    double Payoff(double *prices, int N, double K, double B)
    {
        double finprice=prices[N]-K;
        if(prices[N]<=K)//Checks to see if the strike price is higher than price at
                        //Time N, sets the value to 0 if this is the case.
        {
            finprice=0;
        }
        for(int i = 0; i <= N; i++)
        {

            if(prices[i]>B) //If the barrier is breached, then the price is set to 0
            {
                finprice=0;
            }
        }
        return finprice;

    }
};
class ParisianOption : public PathDependentOptions
{
public:
    double Payoff(double *prices, int N, double K, double B,int M)
    {
        double finprice=prices[N]-K; //checks to see if the maximum price exceeds the barrier
        if(prices[N]<=K)
        {
            finprice=0;
        }
        int m=0;
        int i=0;
        int j=0;
        int reset=0;
        while(i<=N)
        {
            if(prices[i]>B&&prices[i-1]>B)
            {
                j=i;
                while(prices[j]>B&&prices[j-1]>B)
                {
                    m=m+1;
                    j=j+1;
                    if(m >=M-1)
                    {
                        reset=1;
                    }
                }
                m=0;
                j=0;
            }
            i=i+1;
        }
        if(reset==1)
        {
            finprice=0;
        }
        return finprice;
    }
};


#endif // PATHDEPENDENTOPTIONS_H
