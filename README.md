# 🐚 Simple Shell

## 📖 Description
This project is a simple UNIX command language interpreter written in C. It reads commands from the standard input or from a file and executes them. This project is part of the low-level programming and algorithm track at Holberton School.

The shell mimics the behavior of the `sh` (Bourne Shell) by presenting a prompt, accepting user input, parsing the input into commands and arguments, and executing those commands using the `execve` system call.

## 🛠️ Requirements
* All files will be compiled on **Ubuntu 20.04 LTS** using `gcc`.
* Compiler options: `-Wall -Werror -Wextra -pedantic -std=gnu89`.
* Code follows the **Betty** style guidelines.
* No memory leaks are allowed.

## ⚙️ Compilation
To compile the shell, run the following command in the terminal:

    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## 🚀 Usage
The shell can work in two modes: **Interactive** and **Non-interactive**.

### Interactive Mode
In this mode, the shell displays a prompt `($)` and waits for the user to type a command.

    $ ./hsh
    ($) /bin/ls
    hsh main.c shell.c
    ($) exit
    $

### Non-interactive Mode
In this mode, the shell reads commands piped into it without displaying a prompt.

    $ echo "/bin/ls" | ./hsh
    hsh main.c shell.c test_ls_2
    $

## 📋 Features
* Executes external commands (e.g., `/bin/ls`, `/bin/pwd`).
* Handles the `PATH` environment variable to find commands (e.g., `ls` instead of `/bin/ls`).
* Built-in commands:
  * `exit`: Exits the shell.
  * `env`: Prints the current environment variables.
* Handles the End-Of-File condition (`Ctrl+D`).

## 👥 Authors
* **Ahmed Alshahrani**
* **Afnan Aljuhani**
