#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>

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

double trapezoides(double a, double b, double n, double h){
    double result = 0.0;

    double x = a;

    while(x < b) {
        result += (function(x) + function(x + h)) * h / 2;
        x += h;
    }

    return result;
}

int main(int argc, char *argv[]) {
    int n = 10e6;
    int nthreads = 10;
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
        if (argc > 3 && isNumber(argv[3])) {
            nthreads = atoi(argv[3]);
        } else {
            printf("Error: número de threads no es válido. Utilizando valor predeterminado.\n");
            nthreads = 10;
        }
    }

    double h = (b - a) / (double)n;
    double riemann = 0.0;

    omp_set_num_threads(nthreads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        double n_local = n / (double)nthreads;
        double a_local = a + (thread_id * n_local * h);
        double b_local = a_local + (n_local*h);

        #pragma omp critical
        {
            riemann += trapezoides(a_local, b_local, n_local, h);
        }
    }

    printf("Con n = %d trapezoides, nuestra aproximación\nde la integral de %d a %d es = %f\n", n, a, b, riemann);

    return 0;
}
