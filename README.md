# COMP304 Project 1 - Shell-ish

## Student

-   **Name:** Ahmet Buğra Ertürk
-   **ID:** 0086877
-   **Email** aerturk23@ku.edu.tr

## Introduction

Shell-ish is an interactive Unix-style command-line
interpreter developed in C. The project
focuses on core operating system concepts including process creation via
forking, manual path resolution using environment variables to replace
`execvp` with `execv`, I/O redirection, and inter-process communication
through piping.

## Repository and Usage

**GitHub Repository:** <https://github.com/ahmetbugraerturk/COMP304_Project1_Shell-ish>

## How to Build

To compile the shell and new commands using `gcc`. A Makefile is also provided. Run the following
command in your terminal:

    make

## How to Run

Launch the shell directly or with line editing
support:

1.  `./shell-ish`

2.  `rlwrap ./shell-ish`

# Features Usage

-   **Standard Commands:** Run programs available in the system path
    like `ls`, `mkdir`, and `cp`.

-   **Background Processes:** Append `&` to any command to execute it
    without blocking the shell.

    <div style="display: flex; gap: 10px;">
      <img src="./imgs/part1-background-1.png" alt="Background 1" width="400">
      <img src="./imgs/part1-background-2.png" alt="Background 2" width="400">
    </div>

-   **Redirection:** Redirect the output of a command to a file.

    <img src="./imgs/part2-redirections.png" alt="Redirections" width="500">

-   **Piping:** Pipe the output of one command to the input of another command.

    <img src="./imgs/part2-piping.png" alt="piping" width="500">

-   **cut command:** A custom command that implements the functionality of the cut command.
    * Usage: `cut -d <delimiter> -f<field_number>`
    * Example: `cut -d ":" -f1,6`
 
    <div style="display: flex; gap: 10px;">
      <img src="./imgs/part3-cut-1.png" alt="Cut 1" width="400">
      <img src="./imgs/part3-cut-2.png" alt="Cut 2" width="400">
    </div>

-   **chatroom command:** A custom command that allows users to chat with each other  using named pipes.
    * Usage: `chatroom <room_name> <user_name>`
    * Example: `chatroom comp304 bugra`
 
    <div style="display: flex; gap: 10px;">
      <img src="./imgs/part3-chatroom-1.png" alt="Chatroom 1" width="300">
      <img src="./imgs/part3-chatroom-2.png" alt="Chatroom 2" width="300">
      <img src="./imgs/part3-chatroom-3.png" alt="Chatroom 3" width="300">
    </div>

-   ***hangman command (my custom command):*** A custom command that allows two users to play hangman with each other using named pipes.
    * Usage: `hangman -m` (moderator) or `hangman -p` (player)

    * Named pipe is created in /tmp/hangman/fifo for communication between moderator and player.

    * How to play:
        1. Open two terminals.
        2. In the first terminal, run `hangman -m`.
           
           <img src="./imgs/part3-hangman(custom)-1.png" alt="Hangman 1" width="400">
        3. In the second terminal, run `hangman -p`.
     
           <img src="./imgs/part3-hangman(custom)-2.png" alt="Hangman 2" width="400">
        4. The moderator will enter a word, and this process will terminated. The game starts at the players screen.
     
           <img src="./imgs/part3-hangman(custom)-3.png" alt="Hangman 3" width="400">
        5. The player will guess letters one by one.
     
           <img src="./imgs/part3-hangman(custom)-4.png" alt="Hangman 4" width="400">
        6. The game ends when the player guesses the word or runs out of lives.

           <div style="display: flex; gap: 10px;">
              <img src="./imgs/part3-hangman(custom)-5.png" alt="Hangman 5" width="400">
              <img src="./imgs/part3-hangman(custom)-6.png" alt="Hangman 6" width="400">
           </div>

# References

* Gemini helps me about the usage of aboves:
  * Template and proofreadings of this README.md file.  
  * `getenv("PATH")`: to find the paths of commands.
  * `access(char *path, F_OK)`: it returns 0 if the path exists.  
  * `dup2()` and `dup()` functions
  * `fcntl.h` package
  * `atoi()` function
  * `fgets()` function
  * `waitpid()` function
  * `WNOHANG` as a suggestion from TA
  * `mkfifo()` and `mkdir()` permissions
  * `dirent.h` package
  * `fflush()` function
  * hangman stages
  * hangman lost and won messages
* unix-pipe.c example
  * pipe codes.
* named-pipes-writes-first.c example
  * named pipe codes.

