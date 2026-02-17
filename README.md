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

To compile the shell using `gcc`, run the following
command in your terminal:

    gcc -o shell-ish shellish-skeleton.c

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

# TODO and Questions

## Remaining Tasks

-   I hope part 1 is done, I am still working on the other parts.

## Questions

-   How to handle zombie processes for background processos?
-   Why can't I write capital C in shell-ish? (._.)

# References

* from Gemini:
  * Template and proofreadings of this README.md file.  
  * `getenv("PATH")`: to find the paths of commands.
  * `access(char *path, F_OK)`: it returns 0 if the path exists.  
