#include<stdio.h>
#include<math.h>
#define mx 10
#define eps 0.01

double table[200];
int itr = 0;
int firstp = 0;
double power(double x, int n)
{
    //printf("init %f %d\n",x,n);
    double ans = 1.0;
    for(int i=1;i<=n;i++)
    {

        ans *= (x*1.0);
        //printf("power  %f %f\n",x,ans);
    }
    return ans;
}
long long fac[10000];
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
        //printf("%f %f %f\n", up, lo, temp);
    }

    double res = fr * ans;

    table[itr++] = res;
    printf("table x = %f, f(x) = %f\n", x, res);
    csv(x,res);
    return res;

}

void csv(double x, double res)
{
    int i,j;
    char filename[11]="bs.csv";
    printf("\nCreating %s file",filename);
    FILE *fp;
    fp=fopen(filename,"a+");
    if(firstp==0)
    {
        fprintf(fp,"x, f(x)");
    }
    firstp++;

    fprintf(fp,"\n%f, %f",x,res);

    fclose(fp);
    printf("\n%sfile created",filename);
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


void bisection(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("You have not assumed right a and b\n");

        return;
    }

    double c = a;
    while ((b-a) >= eps)
    {
        // Find middle point
        c = (a+b)/2;

        // Check if middle point is root
        if (func(c) == 0.0)
            break;

        // Decide the side to repeat the steps
        else if (func(c)*func(a) < 0)
            b = c;
        else
            a = c;
    }
    printf("The value of root is : %f\n",c);

}
int main()
{
    fact();
    for(double i=0.0; i<=10.0; i+=0.1)
    {
        func(i,2,5);
    }
    double a =-2.5, b = -1.0;
    //bisection(a, b);
    return 0;
}

