#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return 1;
    }
    
    const char *filename = argv[1];
    
    FILE *fp = fopen(filename, "r");
    
    if (!fp) {
        fprintf(stderr, "Could not open %s\n", filename);
        return 1;
    }
    
    char c;
    for (unsigned int i = 0; (c = fgetc(fp)) != EOF; i++) {
        printf("%c", c);
    }
    printf("\n");
    
    fclose(fp);
    return 0;
}

