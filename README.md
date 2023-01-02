# Library Management Application

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## What is this application?

This application allows for the management of libraries and books and provides functionality for managing the libraries including updating the addresses of libraries, sorting books within the libraries, adding and removing books, and moving books between libraries.

## Choice of programming language
This application was written in C++ for several reasons:

- C++ is a high-performance language, which means it can handle large amounts of data efficiently. This is important for an application that is managing a large number of books and libraries.
- C++ has a large standard library and a large community of users, which means there are lots of premade functions with high reliability that can be used immediately such as the sort function and vector class.
- C++ is a statically-typed language, which means that the type of a variable must be specified at compile time. This can help catch errors and bugs early on in the development process, which is helpful for the development of collection classes that have a high amount of operator overloading.
- C++ is a widely-used language, which means it is well-documented and has a large number of resources available online.

## Demo of the application running!
![](https://user-images.githubusercontent.com/81977350/210184873-fd8819c4-8648-45e7-8cf6-166384801094.gif)

## Instructions to compile and run the application:

## Linux
1. Download the application or clone the repository
2. Make sure you have a C++ compiler like **gcc** installed on your OS
3. Compile the files in the program by running the Makefile in the root directory with the `make` command in a terminal.
4. Afterwards, move the terminal to the bin directory and run the executable with the `./LibraryManagementApplication` command
5. Once the program launches, follow the onscreen prompts.
6. Once the program finishes, you can clean up the executables and object files with the `make clean` command in a terminal in the root directory.

## Potential Improvements and Advancements:
- Finish the functionality to save libraries into text files so they can be saved.
- Add the ability to save other commodities that libraries carry like audiobooks.
