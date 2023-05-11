#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
struct Interval
{
    double left;
    double right;
} rada[5];

double f(double x)
{
    return x*x*x + 5*x*x - 6*x -42;

}
double fpr(double x)
{
    return 3*x*x + 10*x - 8;
}
double eps = 1e-9;
int Separation(double A, double B, double h);
double Bisection(double a, double b, int &k);
double Newton(double a, double b, int &k);
double ModificataTangentelor(double a, double b, int &k);
double Secantelor(double a, double b, int &k);
double Coardelor(double a, double b, int &k);
double MIxta(double a, double b, int &k);
double SimpleIteratiilor(double a, double b, int &k);
void Print(double A, double B, int k);

int main()
{
    int i, n, k;
    double A = -6;
    double B = 4;
    double h = 0.05;

    cout << "Proiect nr1 elaborat de Costiuc Igor" << endl;
    cout << "Tema: Rezolvarea ecuatiilor nelineare" << endl;
    cout << ""<< endl;
    n = Separation(A, B, h);
    for(i=0; i<n; i++)
    {
        cout << "\n \nO solutie separata se afla pe ["<< rada[i].left << ":" << rada[i].right << "]" << endl;
        Print(rada[i].left, rada[i].right, k);


    }

    return 0;
}
void Linia(int st, int lin, int mij, int dr)
{
    int i;
    printf("\n%c", st);
    for (i = 1; i <= 20; i++) printf("%c", lin); printf("%c", mij); // Metoda
    for (i = 1; i <= 8; i++) printf("%c", lin); printf("%c", mij); // Iteratia
    for (i = 1; i <= 17; i++) printf("%c", lin); printf("%c", mij); // Aproximatia
    for (i = 1; i <= 12; i++) printf("%c", lin); printf("%c", dr); // Verificare
}
void Print(double A, double B, int k){
        double x;
        Linia(201, 205, 209, 187);
        printf("\n%cMetoda %14cIteratia%cAproximatia %6cVerificare  %c",
           186, 179, 179, 179, 186);
           Linia(199, 196, 197, 186);
        x = Bisection(A, B, k);
        printf("\n%cBisectia %12c %d %5c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = Newton(A, B, k);
        printf("\n%cNewton %14c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = ModificataTangentelor(A, B, k);
        printf("\n%cModifTangentelor %4c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = Secantelor(A, B, k);
        printf("\n%cSecantelor %10c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = Coardelor(A, B, k);
        printf("\n%cCoardelor %11c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = MIxta(A, B, k);
        printf("\n%cMIxta %15c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(199, 196, 197, 186);
        x = SimpleIteratiilor(A, B, k);
        printf("\n%cSimpleIteratiilor %3c %d %6c%15.12lf %2c%12.3le%c", 186, 179, k, 179, x, 179, f(x), 186);
        Linia(200, 205, 207, 188);

}

int Separation(double A, double B, double h)
{
    int n = 0;
    double x0, x;
    x0 = A;
    do{
        x = x0 + h;
        //if(f(x)==0)...
        if(f(x0)*f(x) < 0){
            rada[n].left = x0;
            rada[n].right = x;
            n++;
        }
        x0 = x;

    } while(x<B);
    return n;
}
double Bisection(double a, double b, int &k)
{
    double x;
   k = 0;
    do{
            k++;
        x = (a+b)/2;

        if(fabs(f(x)) < eps){
            return x;
        }
        if(f(a)*f(x) < 0){
            b = x;
        }else
        {
            a = x;
        }

    } while(fabs(b-a) > eps);
    return (a +b)/2;
}
double Newton(double a, double b, int &k)
{
     double x0, x, delta;
   k = 0;
   x0 = (a+b)/2;
    do{
            k++;
        x = x0 - f(x0)/fpr(x0);

        if(fabs(f(x)) < eps){
            return x;
        }
        delta = fabs(x0-x);
        x0 = x;

} while(delta > eps);
    return x;
}
double ModificataTangentelor(double a, double b, int &k)
{
     double x0, x, fpr0, delta;
   k = 0;
   x0 = (a+b)/2;
    fpr0 = fpr(x0);
    do{
            k++;
        x = x0 - f(x0)/fpr0;

        if(fabs(f(x)) < eps){
            return x;
        }
        delta = fabs(x0-x);
        x0 = x;

    } while(delta > eps);
    return x;
}
double Secantelor(double a, double b, int &k)
{
   double x0, x1, x, delta;
   k = 1;
   x0 = a;
   x1 = b;

    do{
            k++;
        x = x1 - f(x1)*(x1-x0)/(f(x1)- f(x0));

        if(fabs(f(x)) < eps){
            return x;
        }
        delta = fabs(x-x1);
        x0 = x1;
        x1 = x;

    } while(delta > eps);
    return x;
}
double Coardelor(double a, double b, int &k)
{
    double x0, x1, x, fx0, delta;
   k = 1;
   x0 = a;
   x1 = b;
   fx0 = f(x0);

    do{
            k++;
        x = x1 - f(x1)*(x1-x0)/(f(x1)- fx0);

        if(fabs(f(x)) < eps){
            return x;
        }
        delta = fabs(x-x1);
        x1 = x;

    } while(delta > eps);
    return x;
}


double chord(double x0, double x1) {
    return x0 - f(x0) * (x1 - x0) / (f(x1) - f(x0));
}

double tangent(double x0) {
    return x0 - f(x0) / fpr(x0);
}


double MIxta(double a, double b, int &k)
{
    double x0 = a, x1 = b;
    double x2 = chord(x0, x1), x3 = tangent(x1);
    double delta;

    do {
        x0 = x1;
        x1 = x2;
        x2 = chord(x0, x1);
        x3 = tangent(x1);

        delta = fabs(x2 - x3);
    } while (delta > eps);

    return x2;
}
double fi(double x) {
     return x - f(x) / (3*x*x + 10*x - 8);
}
double SimpleIteratiilor(double a, double b, int &k)
{
   double x0 = (a+b)/2;
   // double x1 = fi(x0);
    k = 1;
    while (fabs(f(x0)) >= eps) {
        x0 = fi(x0);
        //x0 = x1;
        k++;
    }
    /*cout << "x = " << x1 << endl;
    cout << "f(x) = " << f(x1) << endl;*/
    return x0;

}
