#include <stdio.h>
#include <stdbool.h>

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
    
    char section[50];
    section[0] = '\0';
    char c;
    for (int i = 0; (c = fgetc(fp)) != EOF; i++) {
        if (c == '\r') continue; // Ignore \r
        if (c == '\n') {
            i = -1;
            continue;
        }
        if (i == 0 && c == '[') {
            unsigned int j = 0;
            while (j < 49) {
                c = fgetc(fp);
                if (c == '\\')
                    c = fgetc(fp);
                else if (c == ']')
                    break;
                section[j] = c;
                j++;
            }
            section[j] = '\0';
        } else {
            char key[50];
            char value[1000];
            unsigned int j;
            for (j = 0;; j++) {
                key[j] = c;
                c = fgetc(fp);
                if (c == '\\') {
                    c = fgetc(fp);
                    continue;
                }
                if (c == '\r')
                    c = fgetc(fp);
                if (c == '\n' || c == '=')
                    break;
            }
            key[++j] = '\0';
            c = fgetc(fp);
            for (j = 0;; j++) {
                value[j] = c;
                c = fgetc(fp);
                if (c == '\\') {
                    c = fgetc(fp);
                    continue;
                }
                if (c == '\r')
                    c = fgetc(fp);
                if (c == '\n')
                    break;
            }
            value[++j] = '\0';
            printf("%s :: %s -> %s\n", section, key, value);
        }
    }
    
    fclose(fp);
    return 0;
}

