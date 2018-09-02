#include<stdio.h>
#include<math.h>
int mx;
double eps;

double table2[10000][10];
double table[10005][15];
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
    printf("\nCreating %s file\n",filename);
    FILE *fp;
    fp=fopen(filename,"w+");
    fprintf(fp,"Iterations, Xl, Xh, Xm, Error(\%), f(Xm)");
    char l1[11]="Iter";
    char l2[11]="Xl";
    char l3[11]="Xh";
    char l4[11]="Xm";
    char l5[11]="Error(\%)";
    char l6[11]="f(Xm)";
    printf("|%12s |%12s |%12s |%12s |%12s |%12s|\n",l1,l2,l3,l4,l5,l6);
    printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");

    for(i=0; i<mx; i++)
    {
        fprintf(fp,"\n%d",i+1);
        printf("\n%d",i+1);
        for(j=1; j<6; j++)
        {
            fprintf(fp,",%f ",table[i][j]);

            //printf("    %f ",table[i][j]);
        }
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12f|\n",i,table[i][1],table[i][2],table[i][3],table[i][4],table[i][5]);
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
    double prev, error=100.0;
    int i=0;
    for (i=0; error>eps ; i++)
    {
        prev = present;
        present = (a*func(ca,cb,cc,b) - b*func(ca,cb,cc,a))/ (func(ca,cb,cc,b) - func(ca,cb,cc,a));

        if(i>0)
        {
            error = (fabs(present-prev)/present);
        }

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
    mx = i;
    csv();

}

void printTable(int itr, double upperValue, double lowerValue, double Xm, double f, double error)
{
    int i = 0;
    table2[itr][0] = itr;
    table2[itr][1] = upperValue;
    table2[itr][2] = lowerValue;
    table2[itr][3] = Xm;
    table2[itr][4] = f;
    table2[itr][5] = error;
    csvBisectionGraph(itr, error);
}

void csvBisectionGraph(int itr, double error)
{
    int i,j;
    char filename[20]="falsevsbs.csv";
    FILE *fp;
    fp=fopen(filename,"a+");

    fprintf(fp,"\n%d, %.5lf",itr,error);

    fclose(fp);
}

void bisection(double ca, double cb, double cc,double a, double b)
{
    if (func(ca,cb,cc,a) * func(ca,cb,cc,b) >= 0)
    {
        printf("No root is possible.\n");

        return;
    }

    double c = a;
    double prev=0.0, error=100.0;
    int ff = 0;

    while ((b-a) >= eps)
    {
        prev = c;
        c = (a+b)/2.0;
        if(ff!=0)
        error = (fabs(c-prev)/c);

        printTable(ff,a,b,c,func(ca,cb,cc,c),error);
        ff++;

        if(error<=eps) break;

        if (func(ca,cb,cc,c) == 0.0)
            break;

        else if (func(ca,cb,cc,c)*func(ca,cb,cc,a) < 0)
            b = c;
        else
            a = c;


    }
    printf("The value of root is : %f\n",c);

}

int main()
{

    double ca=42,cb=28,cc=4,a=1,b=20;

    for(int i=0; i<=20; i++)
    {
        printf("%d    %f\n",i,func(ca,cb,cc,i));
    }
    scanf("%lf %lf %lf",&a, &b, &eps);
    falsePosition(ca,cb,cc,a, b);
    bisection(ca,cb,cc,a,b);
    return 0;
}
