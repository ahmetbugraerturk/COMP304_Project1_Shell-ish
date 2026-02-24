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

-   **Redirection:** Redirect the output of a command to a file.

-   **Piping:** Pipe the output of one command to the input of another command.

# TODO and Questions

## Remaining Tasks

-   I hope part 1, 2 and first 2 commands of part 3 are done, I am still working on the custom command of part 3.

## Questions

-   How to handle zombie processes for background processos?
-   Why can't I write capital C in shell-ish? (._.)
-   What should I do if ">" and ">>" both exist? I could handle it but idk if I should have. In my code, both of the operators work, but in the unix the last one should work, if I'm not mistaken. However, I can't handle the order of them. "|" can be considered for this question.
-   I did the piping between parent and child instead of siblings. Is it a problem.

# References

* from Gemini:
  * Template and proofreadings of this README.md file.  
  * `getenv("PATH")`: to find the paths of commands.
  * `access(char *path, F_OK)`: it returns 0 if the path exists.  
  * `dup2()` and `dup()` functions
  * `fcntl.h` package
  * `atoi()` function
  * `fgets()` function
  * `waitpid()` function
  * `WNOHANG` also from TA
  * `mkfifo()` and `mkdir()` permissions
  * `dirent.h` package
  * `fflush()` function
  * hangman stages
  * hangman lost and won messages
* from unix-pipe.c example
  * pipe codes.
* from named-pipes-writes-first.c example
  * named pipe codes.

