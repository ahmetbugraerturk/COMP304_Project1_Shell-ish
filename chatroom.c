#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h> // from Gemini

#define MAX_MSG_LEN 1024

void send_msg(char *msg, char *dir_path, char *my_name){
    struct dirent *entry;
    DIR *dp = opendir(dir_path);
    while((entry = readdir(dp)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, my_name) == 0) {
            continue;
        }

        pid_t pid = fork();
        if(pid == 0){
            char fifo_path[100];
            strcpy(fifo_path, dir_path);
            strcat(fifo_path, "/");
            strcat(fifo_path, entry->d_name);
            int fd = open(fifo_path, O_WRONLY);
            char final_msg[MAX_MSG_LEN + 100];
            strcpy(final_msg, my_name);
            strcat(final_msg, ": ");
            strcat(final_msg, msg);
            write(fd, final_msg, strlen(final_msg));
            close(fd);
            exit(0);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        fprintf(stderr, "Usage: chatroom <username> <chatroom_name>\n");
        return 1;
    }

    char dir_path[100];
    strcpy(dir_path, "./tmp/chatrooms-"); // replace it with /tmp/chatrooms- before submission
    strcat(dir_path, argv[1]);
    if(access(dir_path, F_OK) == -1){
        mkdir(dir_path, 0777);
    }

    printf("Welcome to %s!\n", argv[1]);

    pid_t rx_pid = fork();
    if(rx_pid == 0){
        char fifo_path[100];
        strcpy(fifo_path, dir_path);
        strcat(fifo_path, "/");
        strcat(fifo_path, argv[2]);
        if(access(fifo_path, F_OK) == -1){
            mkfifo(fifo_path, 0666); // from named-pipes-writes-first.c example
        }
        
        while(1){
            int fd = open(fifo_path, O_RDONLY);
            char msg[MAX_MSG_LEN];
            int r_byte;
            if ((r_byte = read(fd, msg, MAX_MSG_LEN-2)) > 0) {
                msg[r_byte-1] = '\0';
                printf("\r[%s] %s\n", argv[1], msg);
                printf("[%s] %s > ", argv[1], argv[2]);
                fflush(stdout); // from Gemini
            }
            close(fd);
        }   
        exit(0);
    }

    pid_t tx_pid = fork();
    if(tx_pid == 0){
        char msg[MAX_MSG_LEN];
        while(1){
            printf("[%s] %s > ", argv[1], argv[2]);
            fflush(stdout); // from Gemini
            fgets(msg, MAX_MSG_LEN, stdin);
            
            send_msg(msg, dir_path, argv[2]);
        }
        exit(0);
    }
    
    waitpid(rx_pid, NULL, 0);
    waitpid(tx_pid, NULL, 0);
    return 0;
}