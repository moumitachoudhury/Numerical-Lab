#include<stdio.h>
#include<math.h>
#define mx 10
double eps;

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

    }

    double res = fr * ans;

    table[itr++] = res;
    printf("table x = %f, f(x) = %f\n", x, res);

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


void bisection(double a, double b, int n, int k)
{
    if (func(a, n, k) * func(b, n, k) >= 0)
    {
        printf("No root is possible.\n");

        return;
    }

    double c = a;
    double prev=0.0, error;
    int ff = 0;
    printf("Iterations    Upper value     Lower Value    Xm    f(Xm)    Relative approx. error\n");
    while ((b-a) >= eps)
    {
        prev = c;

        if(ff!=0)
        error = ((c-prev)/c);

        c = (a+b)/2;

        printf("%d   %d     %d    %f    %f    %f\n",ff,a,b,c,func(a,n,k),error);
        ff++;
        if (func(c, n, k) == 0.0)
            break;

        else if (func(c, n, k)*func(a, n, k) < 0)
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
        func(i,0,5);
    }
    printf("%f %f\n",func(1,0,5),func(3,0,5));
    double a,b;
    scanf("%f %f %f",&a, &b, &eps);
    bisection(a, b, 0, 5);
    return 0;
}

