#include<stdio.h>
#include<math.h>
#define mx 10

double table[50][50];
double func(double x)
{
    return ((x-4)*(x-4)) * (x+2);
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
void falsePosition(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("You have not assumed right a and b\n");
        return;
    }

    double present = a;
    double prev, error;

    for (int i=0; i < mx; i++)
    {
        prev = present;
        present = (a*func(b) - b*func(a))/ (func(b) - func(a));

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
        table[i][5] = func(present);

        if (func(present)==0)
            break;

        else if (func(present)*func(a) < 0)
            b = present;
        else
            a = present;
    }
    printf("The value of root is : %f",present);
    csv();

}

int main()
{

    double a =-1.0, b = -2.5;
    falsePosition(a, b);
    return 0;
}
