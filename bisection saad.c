#include<stdio.h>
#include<string.h>
#include <math.h>

double table[100][6];
int tot;
void csv()
{
    char filename[11]="prob1b.csv";
    printf("\nCreating %s file",filename);
    FILE *fp;
    int i,j;
    fp=fopen(filename,"w+");
    fprintf(fp,"Iterations, Xl, Xh, Xm, Error(\%), f(Xm)");
    for(i=0; i<tot; i++)
    {
        fprintf(fp,"\n%d",i+1);

        for(j=1; j<6; j++)fprintf(fp,",%f ",table[i][j]);
    }
    fclose(fp);
    printf("\n%sfile created",filename);
}
double funct(double x)
{
    double e=2.71;
    double ex=pow(e,x);
    double sq=x*x;
    double ans=ex-5*sq;
    return ans;
}
void print()
{
    char l1[11]="Iter";
    char l2[11]="Xl";
    char l3[11]="Xh";
    char l4[11]="Xm";
    char l5[11]="Error(\%)";
    char l6[11]="f(Xm)";
    printf("|%12s |%12s |%12s |%12s |%12s |%12s
           |\n",l1,l2,l3,l4,l5,l6);
    printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
    int i=0;

    for(; i<tot; i++)
    {
        printf("|%-12d |%-12f |%-12f |%-12f |%-12f |%-12f|\n",i,table[i][1],table[i][2],table[i][3],table[i][4],table[i][5]);
    }
    printf("Approximate Root = %lf\n",table[tot-1][3]);
    return ;
}
double myabs(double x)
{
    if(x<0.000000)return x*-1;
    else return x;
}
void solve(double pos,double neg, double tol)
{
    double hi=pos;
    double lo=neg;
    double mid=0,err,fx,px=0;
    tot=0;
    while(1)
    {
        mid=(hi+lo)/2;
        fx=funct(mid);
        err=fabs((mid-px)/mid);
        err=err*100;
        table[tot][0]=tot;
        if(hi>=lo)
        {
            table[tot][1]=lo;

            table[tot][2]=hi;
        }
        else
        {
            table[tot][1]=hi;
            table[tot][2]=lo;
        }
        table[tot][3]=mid;
        if(tot)table[tot][4]=err;
        table[tot][5]=fx;
        if(fx<=0)
        {
            lo=mid;
        }
        else hi=mid;
        px=mid;
        tot++;
        if(err<=tol)break;
    }
    print();
    csv();
}
double table2[100][3];
void csv2()
{
    char filename[11]="prob1a.csv";
    printf("\nCreating %s file",filename);
    FILE *fp;
    int i,j;

    fp=fopen(filename,"w+");
    fprintf(fp,"Iterations, X, f(X)");
    for(i=0; i<21; i++)
    {
        fprintf(fp,"\n%d",i+1);
        for(j=0; j<2; j++)fprintf(fp,",%f ",table2[i][j]);
    }
    fclose(fp);
    printf("\n%sfile created",filename);
}
void print2()
{
    char l1[11]="Iter";
    char l2[11]="X";
    char l3[11]="f(X)";
    printf("|%12s |%12s |%12s |\n",l1,l2,l3);
    printf("|-------------|-------------|-------------|\n");
    int i=0;
    for(; i<21; i++)
    {
        printf("|%-12d |%-12f |%-12f
               |\n",i,table2[i][0],table2[i][1]);
    }
    return ;
}

void solve2()
{
    double x=-1;
    int i;
    for(i=0; i<21; i++)
    {
        table2[i][0]=x;
        table2[i][1]=funct(x);
        x=x+0.1;
    }
    print2();
    csv2();
}
int main()
{
    solve2();
    printf("\nEnter EndPoints & Tolerance\n");
    double b1,b2,tol,pos,neg,t1,t2;
    scanf("%lf %lf %lf",&b1,&b2,&tol);
    fclose(stdin);
    t1=funct(b1);
    t2=funct(b2);
    if(t1*t2>=0)
    {
        printf("End points have same sign!");
        return 0;
    }
    if(t1>=t2)
    {
        pos=b1;
        neg=b2;

    }
    else
    {
        pos=b2;
        neg=b1;
    }
    solve(pos,neg,tol);
    return 0;
}
