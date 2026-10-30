#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>

void merge(double *arr, long long l, long long m, long long r) {
    long long n1 = m - l + 1;
    long long n2 = r - m;

    double *L = (double*)malloc(n1 * sizeof(double));
    double *R = (double*)malloc(n2 * sizeof(double));

    for (long long i = 0; i < n1; i++) L[i] = arr[l + i];
    for (long long j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    long long i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(double *arr, long long l, long long r) {
    if (l < r) {
        long long m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
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

    printf("Pruebas Merge Sort C\n\n");

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

        merge_sort(arr, 0, n - 1);

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