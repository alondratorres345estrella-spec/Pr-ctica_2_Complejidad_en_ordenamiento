#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>

void bubble_sort(double *arr, long long n) {
    for (long long i = 0; i < n - 1; i++) {
        for (long long j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double* generar_arreglo(long long n) {
    double *arr = (double*)malloc(n * sizeof(double));
    if (!arr) return NULL;
    for (long long i = 0; i < n; i++) {
        arr[i] = ((double)rand() / RAND_MAX) * 10000.0;
    }
    return arr;
}

int main() {
    long long tamanos[] = {100000LL, 1000000LL, 10000000LL, 100000000LL, 1000000000LL};

    printf("Pruebas Bubble Sort C\n\n");

    for (int i = 0; i < 5; i++) {
        long long n = tamanos[i];
        printf("N = %lld\n", n);

        double *arr = generar_arreglo(n);
        if (!arr) {
            printf("Error de memoria\n\n");
            continue;
        }

        LARGE_INTEGER freq, t1, t2;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);

        bubble_sort(arr, n);

        QueryPerformanceCounter(&t2);
        double tiempo = (double)(t2.QuadPart - t1.QuadPart) / freq.QuadPart;

        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        double memoria = (double)pmc.PeakWorkingSetSize / (1024.0 * 1024.0);

        printf("Tiempo: %.4f s\n", tiempo);
        printf("Memoria: %.2f MB\n\n", memoria);

        free(arr);
    }

    return 0;
}