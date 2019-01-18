#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
#include "util.h"

static const char *SLASH = "\\";
static const char *JAVA_EXTENSION = ".java";

void process_file(FILE *file);

int main(int len, char **argv) {
    if (len != 2) {
        puts("You did not provide a directory to scan");
        return 1;
    }

    char *dir_name = *(argv + 1);
    int ends_with_slash = ends_with(dir_name, SLASH);
    if (!ends_with_slash) {
        dir_name = concat(dir_name, SLASH);
    }

    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        puts("Provided directory is not valid");
        return 1;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        int is_java_file = ends_with(ent->d_name, JAVA_EXTENSION);
        if (is_java_file) {
            char *file_path = concat(dir_name, ent->d_name);
            FILE *file = fopen(file_path, "r");
            printf("Processing file: %s...\n", file_path);
            process_file(file);

            fclose(file);
        }
    }

    closedir(dir);
    free(dir_name);

    return 0;
}

int fill_line(int *line_len, char *line, FILE *file) {
    int chars_read = 0;
    char c;

    while (TRUE) {
        c = (char) fgetc(file);

        if (c == EOF) {
            return -1;
        }

        chars_read++;
        if (chars_read >= *line_len - 1) {
            *line_len = chars_read + 1;
            line = realloc(line, (size_t) *line_len * sizeof(*line));
            printf("Size: %d\n", *line);
        }

        *(line + chars_read - 1) = c;

        if (c == '\n') {
            break;
        }
    }

    *(line + chars_read) = '\0';
    return chars_read;
}

void process_file(FILE *file) {
    int line_len = 1;
    char *line = malloc((size_t) line_len * sizeof(char));

    puts("Dumping...");
    while (TRUE) {
        int chars_read = fill_line(&line_len, line, file);
        if (chars_read == -1) {
            break;
        }

        printf("%s", line);
    }
}
