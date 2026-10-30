import random
import time
import tracemalloc

def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def ejecutar():
    tamanos = [100_000, 1_000_000, 10_000_000, 100_000_000, 1_000_000_000]
    print("Pruebas Bubble Sort Python\n")

    for n in tamanos:
        print(f"N = {n}")
        try:
            tracemalloc.start()
            arr = [random.uniform(0.0, 10000.0) for _ in range(n)]

            t1 = time.perf_counter()
            bubble_sort(arr)
            t2 = time.perf_counter()

            _, peak = tracemalloc.get_traced_memory()
            tracemalloc.stop()

            print(f"Tiempo: {t2 - t1:.4f} s")
            print(f"Memoria: {peak / (1024 * 1024):.2f} MB\n")
            del arr

        except MemoryError:
            tracemalloc.stop()
            print("Error de memoria\n")
        except Exception as e:
            tracemalloc.stop()
            print(f"Error: {e}\n")

if __name__ == "__main__":
    ejecutar()