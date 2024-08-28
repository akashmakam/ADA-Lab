// Clears the exisiting file contents of plotter generated text files.
#include <stdio.h>

int main() {
    const char* filenames[] = {"e_b.txt", "e_w.txt", "c_b.txt", "c_w.txt", "m_b.txt", "m_w.txt"};
    for (int i = 0; i < (int)(sizeof(filenames) / sizeof(filenames[0])); i++) {
        FILE* file = fopen(filenames[i], "w");
        if (file == NULL) {
            printf("Failed to open %s\n", filenames[i]);
        } else {
            printf("Cleared contents of %s\n", filenames[i]);
            fclose(file);
        }
    }
    return 0;
}