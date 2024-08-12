#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isNumber(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

int main(int argc, char *argv[]) {
    int age = 10;

    if (argc > 1) {
        if (isNumber(argv[1])) {
            age = atoi(argv[1]);
        } else {
            printf("Error: El parámetro ingresado no es un número válido. Utilizando valor por defecto.\n");
            age = 10;
        }
    }

    omp_set_num_threads(age);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        if (thread_num % 2 == 0)
            printf("Saludos del hilo %d.\n", thread_num);
        else
            printf("Feliz cumpleaños número %d!\n", total_threads);
    }

    return 0;
}
