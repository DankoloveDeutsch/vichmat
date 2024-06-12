#include <iostream>
#include <cmath>
#include <cassert>

const double epsilon = 0.0005;

double f(double x)
{
    return (pow(x,3)+2.7*x-9.4);
}
double f1(double x)
{
    return (2*pow(x, 2) + 2.7);
}
double f2(double x)
{
    return (4*x);
}
void Dihotomia(double a, double b) {
    double c,dx;
    do {
        c = (a + b) / 2;
        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;
    } while (abs(b - a) > epsilon);
    c = (a + b) / 2;
    dx = (b - a) / 2;
    std::cout << "output -> c f(c) dx\n";
    std::cout << c << " " << f(c) << " " << dx << std::endl;
}
void hord(double a, double b) {
    
    double c=0, dx, horda;
    double fa = f(a), fb = f(b), fc;
    
    if (fa * fb > 0){
        return;
    }
    do {
        
        c = a - ((b - a) / (fb - fa)) * f(a);
        fc = f(c);

        if (fa * fc > 0) {
            b = c;
            fb = fc;
        }
        else {
            a = c;
            fa = fc;
        }
    } while (abs(b - a) > epsilon);
    horda = c;

    dx = (b - a) / 2;
    std::cout << "output -> c f(c) dx\n";
    std::cout << c << " " << f(c) <<" " << dx << std::endl;
}
void Njuton(double x0){
    double fx, fx1, fx2,x1,dx;
    fx = f(x0);
    fx1 = f1(x0);
    fx2 = f2(x0);
    
    if (abs((fx * fx2) / (fx1 * fx1)) >= 1) {
        std::cout << "Rashoditsa" << std::endl;
        return;
    }
    while(true){

        x1 = x0 - fx / f1(x0);
        if (abs(x1 - x0) > epsilon) {
            break;
        }
        else {
            x0 = x1;
            fx = f(x0);
        }
    }
    dx = (x1 - x0) / 2;
    std::cout << "output -> x1 f(x1) dx\n";
    std::cout << x1 << " " << f(x1) << " " << dx << std::endl;
}
int main()
{
    double a, b;
    a = -3;
    b = 3;
    std::cout << "Method Dihotomii\n";
    Dihotomia(a, b);
    std::cout << "Method Hord\n";
    hord(a,b);
    std::cout << "Method Njutona\n";
    Njuton(b);
    return 0;
}