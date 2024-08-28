// Heap Sort Algorithm.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisions = 0;
int swaps = 0;

int max(int a, int b) {
    return ((a > b)? a : b);
}

void heapify(int array[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if ((left < n) && (array[largest] < array[left])) {
        comparisions++;
        largest = left;
    }
    if ((right < n) && (array[largest] < array[right])) {
        comparisions++;
        largest = right;
    }
    if (largest != i) {
        swaps++;
        int temp = array[largest];
        array[largest] = array[i];
        array[i] = temp;
        heapify(array, n, largest);
    }
}

void buildHeap(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }
}

void heapSort(int array[], int n) {
    buildHeap(array, n);
    for (int i = n - 1; i >= 0; i--) {
        swaps++;
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        heapify(array, i, 0);
    }
}

void tester() {
    int n;
    printf("\nEnter the size of the array: ");
    scanf("%d", &n);
    int array[n];
    printf("\nEnter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    printf("\nThe entered array elements are:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
    heapSort(array, n);
    printf("\nThe array elements after sorting are:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
}

void plotter() {
    int *array, n = 100, count;
    srand(time(NULL));
    FILE *f1, *f2, *f3;
    f1 = fopen("heapBest.txt", "w");
    f2 = fopen("heapWorst.txt", "w");
    f3 = fopen("heapAverage.txt", "w");
    while (n <= 1000) {
        array = (int *) malloc(n * sizeof(int));
        // Best case
        for (int i = 0; i < n; i++) {
            array[i] = n - i + 1;
        }
        swaps = comparisions = 0;
        heapSort(array, n);
        count = max(swaps, comparisions);
        fprintf(f1, "%d\t%d\n", n, count);
        // Worst case
        for (int i = 0; i < n; i++) {
            array[i] = i + 1;
        }
        swaps = comparisions = 0;
        heapSort(array, n);
        count = max(swaps, comparisions);
        fprintf(f2, "%d\t%d\n", n, count);
        // Average case
        for (int i = 0; i < n; i++) {
            array[i] = rand() % n;
        }
        swaps = comparisions = 0;
        heapSort(array, n);
        count = max(swaps, comparisions);
        fprintf(f3, "%d\t%d\n", n, count);
        free(array);
        n += 100;
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

int main() {
    int option;
    printf("\nChoose any one of the following:\n"
    "1. Tester\n"
    "2. Plotter\n"
    "3. Exit\n");
    scanf("%d", &option);
    switch(option) {
        case 1: tester(); break;
        case 2: plotter(); break;
        case 3: exit(0);
        default: printf("\nInvalid option!\n");
    }
    return 0;
}