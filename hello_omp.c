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
    int nthreads = 10;

    if (argc > 1) {
        if (isNumber(argv[1])) {
            nthreads = atoi(argv[1]);
        } else {
            printf("Error: El parámetro ingresado no es un número válido. Utilizando valor por defecto.\n");
            nthreads = 10;
        }
    }

    omp_set_num_threads(nthreads);

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d!\n", thread_num, total_threads);
    }

    return 0;
}
