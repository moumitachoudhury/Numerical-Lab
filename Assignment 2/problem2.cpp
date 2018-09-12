#include<bits/stdc++.h>
double eps=0.0001;
using namespace std;

double func1(double x)
{
    return -x*x+1.8*x+2.5;
}

double func2(double x)
{
    return exp(-0.5*x)*(4-x)-2;
}

double derivFunc1(double x)
{
    return -2*x+1.8;
}

double derivFunc2(double x)
{
    return -0.5*exp(-0.5*x)*(4-x)-exp(-0.5*x);
}

double relativeError(double oldValue, double newValue)
{
    if(newValue!=0.0)
        return fabs((newValue-oldValue)/newValue);

    return 0.0000;
}
void printFunction(int itr, double Xi, double f, double fprime, double error)
{
    char l1[11]="Iter";
    char l2[11]="Xi";
    char l3[11]="f(Xi)";
    char l4[11]="fprime(Xi)";
    char l5[11]="Error(\%)";
    if(itr == 1)
    {
        printf("--------------------------------Newton Raphson Method-------------------------------\n");
        printf("|%12s |%12s |%12s |%12s |%12s|\n",l1,l2,l3,l4,l5);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12f |%-12f |%-12f |%-12s|\n", itr, Xi, f, fprime,"N/A");

    }
    else
    {
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f|\n", itr, Xi, f, fprime,error);
    }

}
void newtonRaphson(double x, int choice)
{
    double h;
    if(choice==1) h = func1(x) / derivFunc1(x);
    else h = func2(x) / derivFunc2(x);

    int itr = 1;
    double old;

    while (1)
    {
        old = x;
        if(choice==1)  h = func1(x) / derivFunc1(x);
        else h = func2(x) / derivFunc2(x);
        x = x - h;
        double error = relativeError(old,x);
        if(choice==1) printFunction(itr,x,func1(x),derivFunc1(x),error);
        else printFunction(itr,x,func2(x),derivFunc2(x),error);

        cout<<error<<endl;

        if(error<eps) break;
        itr++;
    }

    cout << "The value of the root is : " << x<<endl;
}


int main()
{
    int choice;
    double x0;

    cout<<"Press 1 for problem(a), 2 for problem(b)"<<endl;

    while(cin>>choice)
    {


        if(choice==1)
        {
            cout<<"--------------------------Problem (a)-----------------------"<<endl;
            cout<<"Enter the value of initial guess & Accuracy: "<<endl;
            cin>>x0>>eps;
            newtonRaphson(x0,choice);
        }
        else
        {
            cout<<"--------------------------Problem (b)-----------------------"<<endl;
            for(int i = 1; i <= 3; i++)
            {
                cout<<"Enter the value of initial guess & Accuracy: "<<endl;
                cin>>x0>>eps;
                newtonRaphson(x0,choice);
            }
        }
    }

    return 0;
}
