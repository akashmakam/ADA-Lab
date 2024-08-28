// Merge Sort Algorithm.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

int* read(int *n) {
    printf("\nEnter the size of the array: ");
    scanf("%d", n);
    int *array = (int *)malloc((*n) * sizeof(int));
    printf("\nEnter the elements of the array:\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

void display(int *array, int n) {
    printf("\nThe sorted array is:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void merge(int *leftArray, int leftSize, int *rightArray, int rightSize, int *array) {
    int i = 0, l = 0, r = 0;
    while (l < leftSize && r < rightSize) {
        count++;
        if (leftArray[l] < rightArray[r]) {
            array[i++] = leftArray[l++];
        } else {
            array[i++] = rightArray[r++];
        }
    }
    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }
    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
}

void worstCaseArrayGenerator(int *array, int n) {
    if (n <= 1) {
        return;
    } else {
        int middle = n / 2;
        int *leftArray = (int *)malloc(middle * sizeof(int));
        int *rightArray = (int *)malloc((n - middle) * sizeof(int));

        for (int i = 0; i < middle; i++) {
            leftArray[i] = array[2 * i];
        }
        for (int j = 0; j < (n - middle); j++) {
            rightArray[j] = array[(2 * j) + 1];
        }
        worstCaseArrayGenerator(leftArray, middle);
        worstCaseArrayGenerator(rightArray, n - middle);
        for (int i = 0; i < middle; i++) {
            count++;
            array[i] = leftArray[i];
        }
        for (int j = 0; j < (n - middle); j++) {
            count++;
            array[j + middle] = rightArray[j];
        }
        free(leftArray);
        free(rightArray);
    }
}

void mergeSort(int *array, int n) {
    if (n <= 1) {
        return;
    } else {
        int middle = n / 2;
        int *leftArray = (int *)malloc(middle * sizeof(int));
        int *rightArray = (int *)malloc((n - middle) * sizeof(int));
        for (int i = 0; i < n; i++) {
            if (i < middle) {
                leftArray[i] = array[i];
            } else {
                rightArray[i - middle] = array[i];
            }
        }
        mergeSort(leftArray, middle);
        mergeSort(rightArray, n - middle);
        merge(leftArray, middle, rightArray, n - middle, array);
        free(leftArray);
        free(rightArray);
    }
}

void plotter() {
    srand(time(NULL));
    FILE *bestCase, *worstCase;
    bestCase = fopen("mergeBest.txt", "w");
    worstCase = fopen("mergeWorst.txt", "w");
    for (int n = 2; n <= 1024; n = n * 2) {
        int *array = (int *)malloc(n * sizeof(int));
        // Best case
        count = 0;
        for (int i = 0; i < n; i++) {
            array[i] = i + 1;
        }
        mergeSort(array, n);
        fprintf(bestCase, "%d\t%d\n", n, count);
        // Worst case
        count = 0;
        worstCaseArrayGenerator(array, n);
        fprintf(worstCase, "%d\t%d\n", n, count);
        free(array);
    }
    fclose(bestCase);
    fclose(worstCase);
}

void tester() {
    int n;
    int *array = read(&n);
    mergeSort(array, n);
    display(array, n);
    printf("\nThis took %d comparisons.\n", count);
    free(array);
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