#include <iostream>
#include <math.h>

double f(double x) {
    return pow(1 + pow(tan(x), 2), 0.5);
}


double Left_Rect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    int i;
    for (i = 0; i <= n - 1; i++) {
        sum += h * f(a + i * h);
    }
    return sum;
}

double Right_Rect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        sum += h * f(a + i * h);
    }
    return sum;
}
double Middle_Rect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    int i;
    for (i = 1; i <= n-1; i++) {
        sum += h * f(a + (i+1/2) * h);
    }
    return sum;
}

double trapeze(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a)+f(b);
    int i;
    for (i = 1; i <= n-1; i++) {
        sum += 2 * f(a + i * h);
    }
    sum *= h / 2;
    return sum;
}


double Simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    int i,k;
    for (i = 1; i <= n - 1; i++) {
        k = 2 + 2 * (i % 2);
        sum += k * f(a + i * h);
    }
    sum *= h / 3;
    return sum;
}

int main() {
    int n;
    double a, b;
    // По заданию шаг = 0.1 => n = (2.6-1)/0.1 = 16
    n = 16;
    a = 1;
    b = 2.6;
    std::cout <<"Method left rectangle: "<< Left_Rect(a, b, n) << std::endl;
    std::cout << "Method right rectangle: " << Right_Rect(a, b, n)<< std::endl;
    std::cout << "Method middle rectangle: " << Middle_Rect(a, b, n)<< std::endl;
    std::cout << "Method trapeze: " << trapeze(a, b, n)<< std::endl;
    std::cout << "Method Simpson: " << Simpson(a, b, n)<< std::endl;

    // Для левых и правых прямоугольников
    std::cout <<"Teta(Method left rectangle) = " << abs(Left_Rect(a, b, 2 * n) - Left_Rect(a, b, n)) << std::endl;
    std::cout << "Teta(Method right rectangle) = " << abs(Right_Rect(a, b, 2 * n) - Right_Rect(a, b, n)) << std::endl;
    // Для средних прямоуголников и трапеций

    std::cout << "Teta(Method middle rectangle) = " << (1 / 3.) * abs(Middle_Rect(a, b, 2 * n) - Middle_Rect(a, b, n)) << std::endl;
    std::cout << "Teta(Method trapeze) = " << (1 / 3.) * abs(trapeze(a, b, 2 * n) - trapeze(a, b, n)) << std::endl;
    // Для метода симпсона
    std::cout << "Teta(Method Simpson) = " << (1 / 15.) * abs(Simpson(a, b, 2 * n) - Simpson(a, b, n)) << std::endl;
}