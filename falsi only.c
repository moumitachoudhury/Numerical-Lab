#include<stdio.h>
#include<math.h>
#define mx 10

double table[50][50];
double func(double ca,double cb, double cc, double x)
{
    double up = (cc+x);
    double lo = (ca-(2*x));
    lo = (lo*lo) * (cb-x);
    return ((up*1.0)/lo)-0.016;
}

void csv()
{
    int i,j;
    char filename[11]="falsi.csv";
    printf("\nCreating %s file",filename);
    FILE *fp;
    fp=fopen(filename,"w+");
    fprintf(fp,"Iterations, Xl, Xh, Xm, Error(\%), f(Xm)");
    for(i=0; i<mx; i++)
    {
        fprintf(fp,"\n%d",i+1);

        for(j=1; j<6; j++)fprintf(fp,",%f ",table[i][j]);
    }
    fclose(fp);
    printf("\n%sfile created",filename);
}
void falsePosition(double ca, double cb, double cc,double a, double b)
{
    if (func(ca,cb,cc,a) * func(ca,cb,cc,b) >= 0)
    {
        printf("You have not assumed right a and b\n");
        return;
    }

    double present = a;
    double prev, error;

    for (int i=0; i < mx; i++)
    {
        prev = present;
        present = (a*func(ca,cb,cc,b) - b*func(ca,cb,cc,a))/ (func(ca,cb,cc,b) - func(ca,cb,cc,a));

        if(i>0)
        {
            error = ((present-prev)/present);
        }
        printf("iteration %d --- > present = %f error = %f\n",i,present,error);

        table[i][0] = i;
        table[i][1] = a;
        table[i][2] = b;
        table[i][3] = present;
        table[i][4] = error;
        table[i][5] = func(ca,cb,cc,present);

        if (func(ca,cb,cc,present)==0.0)
            break;

        else if (func(ca,cb,cc,present)*func(ca,cb,cc,a) < 0)
            b = present;
        else
            a = present;
    }
    printf("The value of root is : %f",present);
    csv();

}

int main()
{

    double ca=42,cb=28,cc=4,a=1,b=20, eps=0.0001;
    printf("%f %f", func(ca,cb,cc,1), func(ca,cb,cc,20));
    scanf("%f %f %f",&a, &b, &eps);
    falsePosition(ca,cb,cc,a, b);
    return 0;
}

