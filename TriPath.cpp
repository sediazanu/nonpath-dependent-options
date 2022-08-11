#include "TriModel.h"
#include "TriPath.h"

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


void TriPath::PathByNumber(int x, int* path)         {

        int a=pow(3,N);

        int y = x;
        for(int n = 1; n <= N; n++)
        {
            if(y <= a/3)
                {path[n-1]=2;
                a=a/3;}
            else if(y <= (2*a)/3) //creates an array N long detailing every permutation 1:3^N
                {path[n-1]=1;
                a=(2*a)/3;
                y=y-(a%y);}
            else
                {path[n-1]=0;
                a=a;
                y=y-(2*(a%y));}



        }
        }

 void TriPath::PriceByPath(int *path, double *prices)
{


    double x = Get_dx(); //creates an array N+1 long that includes S0 and then uses path to increase or decrease S0
    prices[0] =Get_S0();
    double track=0;
    for(int i=0;i<N;i++)
    {
        if(path[i]==0){track--;}
        if(path[i]==1){track=track;}
        if(path[i]==2){track++;}
        prices[i+1]=S(track);
    }
}


 }

 double TriPath::ProbabilityByPath(int *path)
 {

double qu =RiskNeutProb_up(); //uses riskneutprob to calculate a probability for each path array based on each entry
double qd= RiskNeutProb_down();
double qm = 1-qu-qd;
double probability=1;
for(int i=0;i<N;i++)
    {
        if(path[i]==0){probability=probability*qd;}
        if(path[i]==1){probability=probability*qm;}
        if(path[i]==2){probability=probability*qu;}

    }
return probability;
}



 }
