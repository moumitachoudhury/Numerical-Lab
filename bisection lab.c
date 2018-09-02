#include<stdio.h>
#include<math.h>
double eps;
long long fac[10000];
double table[10000][10];

int itr = 0, firstp = 0;

double power(double x, int n)
{
    double ans = 1.0;
    for(int i=1;i<=n;i++)
    {
        ans *= (x*1.0);
    }
    return ans;
}

long long fact()
{
    int i = 1;
    fac[0] = 1;
    for(int i=1;i<=15;i++)
    {
        fac[i] = fac[i-1] * i;
    }
}

double func(double x, int n, int k)
{
    double fr = power(x/2.0, n);

    double ans = 0;
    for(int i=1;i<=k;i++)
    {
        double up = power((x*x)/4.0, i);
        long long lo = fac[i] * fac[n+i];
        double temp = up/(lo*1.0);
        if(i%2==1) temp = (-1) * temp;
        ans += temp;

    }

    double res = fr * ans;

    csvFunctionGraph(n,x, res);
    return res;

}

void csvFunctionGraph(int n,double x, double res)
{
    int i,j;
    char filename1[11]="bs11.csv";
    char filename2[11]="bs12.csv";
    char filename3[11]="bs13.csv";


    FILE *fp1, *fp2, *fp3;
    fp1=fopen(filename1,"a+");
    fp2=fopen(filename2,"a+");
    fp3=fopen(filename3,"a+");
    if(firstp==0)
    {
        if(n==0)
            fprintf(fp1,"x, f(x)");
        if(n==1)
            fprintf(fp2,"x, f(x)");
        if(n==2)
            fprintf(fp3,"x, f(x)");

    }
    firstp++;
    if(n==0)
    fprintf(fp1,"\n%f, %f",x,res);
    if(n==1)
    fprintf(fp2,"\n%f, %f",x,res);
    if(n==2)
    fprintf(fp3,"\n%f, %f",x,res);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

void csvBisectionGraph(int ff)
{
    int i,j;
    char filename[11]="bs2.csv";
    char filename2[11]="bs3.csv";

    FILE *fp, *fp2;
    fp=fopen(filename,"w+");
    fp2=fopen(filename2,"w+");

    fprintf(fp,"x, Relative Approx Error");

    for(int i=0;i<ff;i++)
    {
        fprintf(fp,"\n%f, %f",table[i][3],table[i][6]);
    }

    fprintf(fp2,"Iteration, Relative Approx Error");

    for(int i=0;i<ff;i++)
    {
        fprintf(fp2,"\n%d, %f",table[i][0],table[i][5]);
    }

    fclose(fp);
}

void printTable(int itr, double upperValue, double lowerValue, double Xm, double f, double error)
{
    int i = 0;
    table[itr][i++] = itr;
    table[itr][i++] = upperValue;
    table[itr][i++] = lowerValue;
    table[itr][i++] = Xm;
    table[itr][i++] = f;
    table[itr][i++] = error;
    if(itr == 1) printf("%d    %.5lf    %.5lf    %.5lf    %.5lf    %s\n", itr, upperValue, lowerValue, Xm, f, "N/A");
    else printf("%d    %.5lf    %.5lf    %.5lf    %.5lf    %.5lf\n", itr, upperValue, lowerValue, Xm, f, error);
}


void bisection(double a, double b, int n, int k)
{
    if (func(a, n, k) * func(b, n, k) >= 0)
    {
        printf("No root is possible.\n");

        return;
    }

    double c = a;
    double prev=0.0, error=0.0;
    int ff = 0;
    while ((b-a) >= eps)
    {
        prev = c;
        c = (a+b)/2;
        if(ff!=0)
        error = ((c-prev)/c);

        printTable(ff,a,b,c,func(a,n,k),error);

        if(error<=eps) break;
        ff++;
        if (func(c, n, k) == 0.0)
            break;

        else if (func(c, n, k)*func(a, n, k) < 0)
            b = c;
        else
            a = c;

    }
    csvBisectionGraph(ff);
    printf("The value of root is : %f\n",c);

}
int main()
{
    fact();
    for(double i=0.0; i<=10.0; i+=0.1)
    {
        func(i,0,5);
        func(i,1,5);
        func(i,2,5);
    }

    double a,b;
    scanf("%f %f %f",&a, &b, &eps);
    bisection(a, b, 0, 5);

    return 0;
}

