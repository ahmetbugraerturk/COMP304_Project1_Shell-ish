#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_WORD_LEN 128

char *stages[] = { // drawn by Gemini
    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |  /|\\ \n"
    "  |  / \\ \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |  /|\\ \n"
    "  |  /   \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |  /|\\ \n"
    "  |      \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |  /|  \n"
    "  |      \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |   |  \n"
    "  |      \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |   O  \n"
    "  |      \n"
    "  |      \n"
    "  |      \n"
    "=========",

    "  +---+  \n"
    "  | / |  \n"
    "  |      \n"
    "  |      \n"
    "  |      \n"
    "  |      \n"
    "========="
};

void print_lost() {
    printf(" __     ______  _    _   _      ____   _____ _______ \n");
    printf(" \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|__   __|\n");
    printf("  \\ \\_/ / |  | | |  | | | |   | |  | | (___    | |   \n");
    printf("   \\   /| |  | | |  | | | |   | |  | |\\___ \\   | |   \n");
    printf("    | | | |__| | |__| | | |___| |__| |____) |  | |   \n");
    printf("    |_|  \\____/ \\____/  |______\\____/|_____/   |_|   \n\n");
}

void print_won() {
    printf(" __     ______  _    _  __          ______  _   _ \n");
    printf(" \\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | |\n");
    printf("  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| |\n");
    printf("   \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` |\n");
    printf("    | | | |__| | |__| |    \\  /\\  / | |__| | |\\  |\n");
    printf("    |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_|\n\n");
}

void draw_hangman(int lives, char *display, char *tried) {
    system("clear");
    
    char stage_copy[256];
    strcpy(stage_copy, stages[lives]);
    
    char *line = strtok(stage_copy, "\n");
    int line_num = 0;

    printf("Past Guesses: %s\n", tried);

    while (line != NULL) {
        printf("%s", line);

        switch(line_num) {
            case 2:
                printf("\t Word: ");
                for(int i = 0; i < strlen(display); i++) {
                    if (display[i] == ' '){
                        printf("  ");
                    } else {
                        printf("%c ", display[i]);
                    }
                }
                break;
            case 4:
                printf("\t > ");
        }
        
        printf("\n");
        line = strtok(NULL, "\n");
        line_num++;
    }
    printf("\033[3A\033[19C"); // from Gemini
    fflush(stdout);
}

void game(char *word){
    int lives = 6;
    char tried[26];
    int t = 0;
    char display[MAX_WORD_LEN];

    for (int i = 0; i<strlen(word); i++){
        if (word[i] == ' '){
            display[i] = ' ';
        } else {
            display[i] = '_';
        }
    }
    display[strlen(word)] = '\0';

    while (strcmp(display, word) != 0){
        draw_hangman(lives, display, tried);

        char input[MAX_WORD_LEN];
        fgets(input, MAX_WORD_LEN, stdin);
        input[1] = '\0';

        int found = 0;
        for (int i = 0; i<strlen(word); i++){
            if (input[0] == word[i]){
                display[i] = input[0];
                found = 1;
            }
        }
        if (found == 0){
            tried[t] = input[0];
            t++;
            lives--;
        }

        if (lives == 0){
            break;
        }
        
    }

    if (lives == 0){
        draw_hangman(lives, display, tried);
        printf("\033[3B\033[19D"); // from Gemini
        print_lost();
    } else {
        draw_hangman(lives, display, tried);
        printf("\033[3B\033[19D"); // from Gemini
        print_won();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2){
        fprintf(stderr, "Usage: hangman -m or -p \n"); // -m: moderator, -p: player
        return 1;
    }

    printf("Welcome to Hangman!\n");

    if (strcmp(argv[1], "-m") == 0){
        char *dir_path = "/tmp/hangman";
        if(access(dir_path, F_OK) == -1){
            mkdir(dir_path, 0777);
        }

        char *fifo_path = "/tmp/hangman/fifo";
        if(access(fifo_path, F_OK) == -1){
            mkfifo(fifo_path, 0666); // from named-pipes-writes-first.c example
        }

        char word[MAX_WORD_LEN];
        printf("Enter a word > ");
        fflush(stdout); // from Gemini
        fgets(word, MAX_WORD_LEN, stdin);

        int fd = open(fifo_path, O_WRONLY);
        write(fd, word, strlen(word));
        close(fd);

    } else if (strcmp(argv[1], "-p") == 0){
        char *fifo_path = "/tmp/hangman/fifo";
        int fd = open(fifo_path, O_RDONLY);
        char word[MAX_WORD_LEN];
        int r_byte;
        if ((r_byte = read(fd, word, MAX_WORD_LEN-1)) > 0) {
            word[r_byte-1] = '\0';
            printf("Word: %s\n", word);
            fflush(stdout); // from Gemini
        }

        game(word);

        close(fd);
    } else {
        fprintf(stderr, "Usage: hangman -m or -p \n");
        return 1;
    }
    
    return 0;
}