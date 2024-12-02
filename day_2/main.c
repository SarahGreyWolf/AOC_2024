#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readFile(char *file_path);
char **splitBy(char **buffer, size_t size, char *deliminator, size_t *out_size);
int safety(char **numbers, size_t number_count);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: aoc2 <path_to_input.txt>\n");
        return 1;
    }

    char *buffer = readFile(argv[1]);

    if (!buffer) {
        return 1;
    }

    size_t size = strlen(buffer);

    size_t line_count = 0;
    char **lines = splitBy(&buffer, size, "\n", &line_count);

    if (!lines) {
        return 1;
    }

    int safe_reports = 0;

    for (int i = 0; i < line_count; i++) {
        // printf("%d\n", i);
        size_t number_count = 0;
        char **numbers = splitBy(&lines[i], size, " ", &number_count);
        int value = safety(numbers, number_count);
        free(numbers);
        if (value) {
            safe_reports++;
        }
        printf("Safety: %d\n", value);
    }

    printf("The number of safe reports are: %d\n", safe_reports);

    free(lines);
    free(buffer);
}

int safety(char **numbers, size_t number_count) {
    int last_number = 0;
    // 0 for Downward, 1 for Upward
    int trending;
    int last_trending;
    for (int i = 0; i < number_count; i++) {
        int num = strtol(numbers[i], NULL, 10);
        if (i == 0) {
            last_number = num;
            continue;
        }
        if (num > last_number) {
            trending = 1;
            if (i == 1) {
                last_trending = trending;
            }
        } else {
            trending = 0;
            if (i == 1) {
                last_trending = trending;
            }
        }
        int diff = abs(last_number - num);
        if (diff < 1 || diff > 3) {
            // UNSAFE
            return 0;
        }
        if (trending != last_trending) {
            // UNSAFE
            return 0;
        }
        last_number = num;
        last_trending = trending;
    }

    // SAFE
    return 1;
}

char **splitBy(char **buffer, size_t size, char *deliminator,
               size_t *out_size) {
    char **split = malloc(sizeof(char) * size);
    if (!split) {
        printf("Failed to malloc size %zu for lines\n", size);
        free(buffer);
        return NULL;
    }

    char *next_token;
    char *token = strtok_s(*buffer, deliminator, &next_token);

    size_t line_number = 0;
    while (token != NULL) {
        size_t line_size = strlen(token);
        split[line_number] = malloc(sizeof(char) * line_size);
        split[line_number] = token;
        token = strtok_s(NULL, deliminator, &next_token);
        line_number++;
    }
    *out_size = line_number;

    return split;
}

char *readFile(char *file_path) {
    FILE *file;
    errno_t err = fopen_s(&file, file_path, "r");

    if (!file) {
        printf("Failed to open %s with %d\n", file_path, err);
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(sizeof(char) * size);

    if (!buffer) {
        printf("Failed to malloc size %zu for buffer\n", size);
        fclose(file);
        return NULL;
    }

    size_t read = fread_s(buffer, size, sizeof(char), size, file);

    if (read != size) {
        printf("Failed to read entirely into buffer\n");
        return NULL;
    }

    fclose(file);

    return buffer;
}