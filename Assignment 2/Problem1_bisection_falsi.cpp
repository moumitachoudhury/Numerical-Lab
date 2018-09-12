#include<bits/stdc++.h>
using namespace std;
double eps=0.0001;

double func(double x)
{
    double g = 9.8, c = 15.0, v = 35, t = 9;
    return ((g*x)/c) * (1-exp((-c/x) * t)) - v;
}


double relativeError(double oldValue, double newValue)
{
    if(newValue!=0.0)
    return fabs((newValue-oldValue))/newValue;

    return 0.0000;
}
void printBisection(int itr, double lowerValue, double upperValue, double Xm, double f, double error)
{
    char fileItr[25]="bisectionitr.csv",fileX[25]="bisectionX.csv";

    FILE *fpItr, *fpX;
    fpItr=fopen(fileItr,"a+");
    fpX=fopen(fileX,"a+");
    char l1[11]="Iter";
    char l2[11]="Xl";
    char l3[11]="Xh";
    char l4[11]="Xm";
    char l5[11]="Error(\%)";
    char l6[11]="f(Xm)";
    if(itr == 1)
    {
        printf("-----------------------------------Bisection Method----------------------------------\n");
        printf("|%12s |%12s |%12s |%12s |%12s |%12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12s|\n", itr, lowerValue, upperValue, Xm, f, "N/A");

    }
    else {
            printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12f|\n", itr, lowerValue, upperValue, Xm, f, error);
            fprintf(fpItr,"%lf, %lf\n",itr,error);
            fprintf(fpX,"%lf, %lf\n",Xm,error);
    }
    fclose(fpItr);
    fclose(fpX);
}

void printFalsi(int itr, double lowerValue, double upperValue, double Xm, double f, double error)
{
    char fileItr[20]="falsiitr.csv",fileX[20]="falsiX.csv";

    FILE *fpItr, *fpX;
    fpItr=fopen(fileItr,"a+");
    fpX=fopen(fileX,"a+");
    char l1[11]="Iter";
    char l2[11]="Xl";
    char l3[11]="Xh";
    char l4[11]="Xm";
    char l5[11]="Error(\%)";
    char l6[11]="f(Xm)";
    if(itr == 1)
    {
        printf("-------------------------------False Position Method---------------------------------\n");
        printf("|%12s |%12s |%12s |%12s |%12s |%12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12s|\n", itr, lowerValue, upperValue, Xm, f, "N/A");
    }
    else {
            printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12f|\n", itr, lowerValue, upperValue, Xm, f, error);
            fprintf(fpItr,"%lf, %lf\n",itr,error);
            fprintf(fpX,"%lf, %lf\n",Xm,error);
    }
    fclose(fpItr);
    fclose(fpX);
}
void bisection(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("No root is possible\n");
        return;
    }

    int itr = 1;
    double c = a,old;
    while (1)
    {
        old = c;
        c = (a+b)/2;
        if(relativeError(old,c)<=0.0001)
            break;

        printBisection(itr,a,b,c,func(c),relativeError(old,c));
        if (func(c) == 0.0)
            break;

        else if (func(c)*func(a) < 0)
            b = c;
        else
            a = c;
        itr++;
    }
    printf("The value of root is : %f\n",c);

}

void falsePosition(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("No root is possible\n");
        return;
    }

    double present = a;
    double prev, error=100.0;
    int i=0;
    for (i=0; error>eps ; i++)
    {
        prev = present;
        present = (a*func(b) - b*func(a))/ (func(b) - func(a));
        error = relativeError(prev,present);

        printFalsi(i+1,a,b,present,func(present),error);
        if (func(present)==0.0)
            break;

        else if (func(present)*func(a) < 0)
            b = present;
        else
            a = present;
    }
    printf("The value of root is : %f",present);

}
int main()
{
    char funcfile[20]="funcvalue.csv";
    FILE *fp1;
    fp1=fopen(funcfile,"w");
    double lo,hi,acc;
    cout<<"Enter the value of initial guesses & Accuracy: "<<endl;
    cin>>lo>>hi>>acc;
    eps = acc;
    printf("\n   X                           f(X)\n\n");
    for(double i = lo; i <= hi; i += 0.1)
    {
        fprintf(fp1, "%lf,%lf\n", i, func(i));
        printf("%lf                   %lf\n", i, func(i));
    }
    fclose(fp1);
    bisection(lo,hi);
    falsePosition(lo,hi);
    return 0;
}


