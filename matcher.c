#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Match structure
struct Match {
    int lineNum;
};

// Function to open a file and handle errors
FILE *openFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }
    return file;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <pattern> [file]\n", argv[0]);
        return 1;
    }

    // Extract the pattern and input source
    char *pattern = argv[1];
    FILE *input = (argc == 3) ? openFile(argv[2]) : stdin;

    // Array to store matching line numbers
    struct Match matches[100];
    int matchCount = 0;

    // Read lines and check for matches
    char *line = NULL;
    size_t size = 0;
    ssize_t len;
    int lineNum = 0;

    while ((len = getline(&line, &size, input)) != -1) {
        lineNum++;
        // Remove the newline character at the end of the line
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Check if the line matches the pattern
        if (strcmp(line, pattern) == 0) {
            matches[matchCount].lineNum = lineNum;
            matchCount++;
        }
    }

    // Print the results
    if (matchCount > 0) {
        printf("Here are all matches:\n");
        for (int i = 0; i < matchCount; i++) {
            printf("%d\n", matches[i].lineNum);
        }
    } else {
        printf("No matches found\n");
    }

    // Clean up
    free(line);
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}