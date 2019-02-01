#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <memory.h>
#include "util.h"

static const char *SLASH = "/";
static const char *JAVA_EXTENSION = ".java";

void process_dir(char *dir_name);
void process_file(FILE *file);

int main(int len, char **argv) {
    if (len != 2) {
        puts("You did not provide a directory to scan");
        return 1;
    }

    char *dir_name = *(argv + 1);

    process_dir(dir_name);

    return 0;
}

int fill_line(int *line_len, char **line_ptr, FILE *file) {
    char *line = *line_ptr;
    int char_idx = 0;
    char c;

    while (TRUE) {
        c = (char) fgetc(file);

        if (c == EOF) {
            return -1;
        }

        if (char_idx >= *line_len - 2) {
            *line_len = char_idx + 2;
            char *alloc = realloc(line, *line_len);
            if (alloc == NULL) {
                puts("Error while allocating new char memory");
                return -1;
            } else {
                line = alloc;
                *line_ptr = line;
            }
        }

        *(line + char_idx) = c;
        char_idx++;

        if (c == '\n') {
            break;
        }
    }

    *(line + char_idx) = '\0';
    return char_idx;
}

void process_dir(char *dir_name) {
    int ends_with_slash = ends_with(dir_name, SLASH);
    if (!ends_with_slash) {
        dir_name = concat(dir_name, SLASH);
    }

    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        printf("Provided directory \"%s\" could not be located...\n", dir_name);
        return;
    }

    printf("Parsing directory \"%s\"...\n", dir_name);

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_REG && ends_with(ent->d_name, JAVA_EXTENSION)) {
            char *file_path = concat(dir_name, ent->d_name);
            FILE *file = fopen(file_path, "r");
            printf("Processing file: \"%s\"...\n", file_path);
            process_file(file);

            fclose(file);
        }

        if (ent->d_type == DT_DIR) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            char *subdir_name = concat(dir_name, ent->d_name);
            process_dir(subdir_name);
        }
    }

    closedir(dir);
    free(dir_name);
}

void process_file(FILE *file) {
    int line_number = 0;
    int line_len = 0;
    char *line = malloc(line_len);

    while (TRUE) {
        line_number++;
        int chars_read = fill_line(&line_len, &line, file);
        if (chars_read == -1) {
            break;
        }

        if (begins_with(line, "if")) {
            printf("%d %s", line_number, line);
        }
    }
}
