#include<stdio.h>
#include<math.h>
#define mx 10
#define eps 0.01

double func(double x)
{
    return ((x-4)*(x-4)) * (x+2);
}

// Prints root of func(x) with error of EPSILON
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

    double a =-2.5, b = -1.0;
    bisection(a, b);
    return 0;
}

