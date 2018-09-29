#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    double f = 8*sin(x)*exp(-x)-1;
    return f;
}

double relativeError(double oldValue, double newValue)
{
    if(newValue!=0.0)
        return fabs((newValue-oldValue)/newValue);

    return 0.0000;
}

void printFunction(int itr, double lo, double hi, double Xm, double fXm, double error)
{
    char l1[11]="Iter";
    char l2[11]="Lower";
    char l3[11]="Upper";
    char l4[11]="Xm";
    char l5[11]="fXm";
    char l6[11]="Error(%)";
    if(itr == 1)
    {
        printf("-----------------------------------Secant Method-------------------------------\n");
        printf("|%12s |%12s |%12s |%12s |%12s |%12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12s|\n", itr, lo,hi,Xm,fXm,"N/A");

    }
    else
    {
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f| %-12f|\n", itr, lo,hi,Xm,fXm,error);
    }

}


void secant(double x1, double x2, double E)
{
    double n = 0, xm=0, x0, c;
    while(1)
    {
        x0 = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));
        c = f(x1) * f(x0);

        x1 = x2;
        x2 = x0;

        printFunction(n,x1,x2,x0,f(x0),relativeError(x1,x2));
        if(n>0)
        {
            if(relativeError(x1,x2)<E) break;
        }
        n++;
        if (c == 0)
            break;
    }
    cout << "Root of the given equation=" << x0 << endl;

}


int main()
{
    double x1 = 0.4, x2 = 0.5, E;
    cout<<"Enter the desired accuracy"<<endl;
    cin>>E;
    secant(x1, x2, E);
    return 0;
}

