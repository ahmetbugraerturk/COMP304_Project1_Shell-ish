#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 100
#define MAX_BUFFER 4096

// Process a single line of input
void process_line(char *line, char delimiter, int fields[], int fc){
    char *token = strtok(line, &delimiter);
    int i = 1;
    while (token != NULL){
        for (int j = 0; j<fc; j++){
            if (fields[j] == i){
                printf(j==fc-1 ? "%s" : "%s:", token);
            }
        }
        token = strtok(NULL, &delimiter);
        i++;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    char delimiter = '\t';
    int fields[MAX_FIELDS];
    int fc = 0;

    // Parse command line arguments
    for (int i = 1; i<argc; i++){
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delimiter") == 0) && i+1 < argc){
            delimiter = argv[i+1][0];
        } else if (strncmp(argv[i], "-f", 2) == 0 || strncmp(argv[i], "--fields", 8) == 0){
            char *f_str = strncmp(argv[i], "-f", 2) == 0 ? strdup(argv[i]+2) : strdup(argv[i]+8);
            char *token = strtok(f_str, ",");
            while (token != NULL){
                fields[fc++] = atoi(token); // from Gemini
                token = strtok(NULL, ",");
            }
            free(f_str);
        }
    }

    // Read from stdin and process each line
    char buffer[MAX_BUFFER];
    while (fgets(buffer, sizeof(buffer), stdin)) { // from Gemini
        buffer[strcspn(buffer, "\n")] = '\0';
        process_line(buffer, delimiter, fields, fc);
    }
    
    return 0;
}