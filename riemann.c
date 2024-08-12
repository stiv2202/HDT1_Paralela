#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

bool isNumber(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

double function(double x){
    // Función 1: x²
    //return pow(x, 2);

    // Función 2: 2x³
    //return pow(x, 3) * 2;

    // Función 3: sin(x)
    return sin(x);
}

double trapezoides(int a, int b, int n){
    double result = 0.0;
    double h = (b - a) / (double)n;

    double x = a;

    while(x < b) {
        result += (function(x) + function(x + h)) * h / 2;
        x += h;
    }

    return result;
}

int main(int argc, char *argv[]) {
    int n = 10e6;
    int a, b;

    if (argc > 1) {
        if (isNumber(argv[1])) {
            a = atoi(argv[1]);
        } else {
            printf("Error: El parámetro ingresado para 'a' no es un número válido.\n");
            return 1;
        }
        if (argc > 2 && isNumber(argv[2])) {
            b = atoi(argv[2]);
        } else {
            printf("Error: El parámetro ingresado para 'b' no es un número válido.\n");
            return 1;
        }
    }

    double riemann = trapezoides(a, b, n);

    printf("Con n = %d trapezoides, nuestra aproximación\nde la integral de %d a %d es = %f\n", n, a, b, riemann);

    return 0;
}
