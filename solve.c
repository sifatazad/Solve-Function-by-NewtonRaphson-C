#include<stdio.h>
#include<math.h>
#define h 1e-6
#define Abs(x) ((x)>=0?(x):-(x))

static double f(const double x) {
    // write your function here!!
    return (x*x+3*x+pow(M_E,(2*x)));
}

static double df(const double x) {
    return ((f(x-2*h)-8*f(x-h)+8*f(x+h)-f(x+2*h))/(12*h));
}

static double ddf(const double x) {
    return ((-f(x-2*h)+16*f(x-h)-30*f(x)+16*f(x+h)-f(x+2*h))/(12*h*h));
}

static double solve(const double x0) {
    if (Abs(df(x0))>1e-9 && Abs(ddf(x0)/(2*df(x0)))<1) {
        double err=100;
        double xi=x0,xi_1=0;
        int it=0;
        while (err>1e-8) {
            if (it==100000 && err>1e-8) {
                printf("Didn't converge! Try another guess.\n");
                return NAN;
            }
            if (Abs(df(xi))<1e-9) {
                printf("Cannot solve!\nf'(x)~0! Try another guess.\n");
                return NAN;
            }
            xi_1=xi-f(xi)/df(xi);
            err=Abs(xi-xi_1);
            xi=xi_1;
            it++;
        }
        return xi_1;
    }
    printf("Cannot solve! Try another guess.\n");
    return NAN;
}

int main() {
    printf("%.10lf\n",solve(70));
}