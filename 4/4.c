// Brute Force String Matching algorithm.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int stringMatching(char *text, char *pattern, int mode) {
    int m = strlen(text);
    int n = strlen(pattern);
    int count = 0, flag = 0;
    for (int i = 0; i <= (m - n); i++) {
        int j = 0;
        count++;
        while ((j < n) && (text[i + j] == pattern[j])) {
            j++;
            count++;
        }
        if (j == n) {
            flag = 1;
            if (mode == 0) {
                printf("\nThe pattern '%s' is present in the text '%s'.\nThis took %d comparisions.\n", pattern, text, count);
            }
            break;
        }
    }
    if (mode == 0 && flag == 0) {
        printf("\nThe pattern '%s' is not present in the text '%s'.\nThis took %d comparisions.\n", pattern, text, count);
    }
    return count;
}

void tester() {
    char text[100], pattern[100];
    printf("Enter the text:\n");
    scanf("%s", text);
    printf("\nEnter the pattern:\n");
    scanf("%s", pattern);
    stringMatching(text, pattern, 0);
}

void plotter() {
    srand(time(NULL));
    int count = 0, n = 10, m = 1000;
    char *text = (char *) malloc(sizeof(char) * (m + 1));
    FILE *f1 = fopen("stringBest.txt", "w");
    FILE *f2 = fopen("stringWorst.txt", "w");
    FILE *f3 = fopen("stringAverage.txt", "w");
    for (int i = 0; i < m; i++) {
        text[i] = 'a';
    }
    text[m] = '\0';
    while (n <= m) {
        char *pattern = (char *) malloc(sizeof(char) * (n + 1));
        // Best case: pattern of 'a' characters
        for (int i = 0; i < n; i++) {
            pattern[i] = 'a';
        }
        pattern[n] = '\0';
        count = stringMatching(text, pattern, 1);
        fprintf(f1, "%d %d\n", n, count);
        // Worst case: pattern ending with 'b'
        pattern[n - 1] = 'b';
        pattern[n] = '\0';
        count = stringMatching(text, pattern, 1);
        fprintf(f2, "%d %d\n", n, count);
        // Average case: random characters
        for (int i = 0; i < n; i++) {
            pattern[i] = (char)(97 + (rand() % 3));
        }
        pattern[n] = '\0';
        count = stringMatching(text, pattern, 1);
        fprintf(f3, "%d %d\n", n, count);
        if (n < 100) {
            n += 10;
        } else {
            n += 100;
        }
        free(pattern);
    }
    free(text);
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