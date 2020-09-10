# JNIHelper

JNIHelper is a helper library which gives you more interaction possibilities 
between your app and your terminal application. Supported is CMD on Windows 
and Bash on Linux.

## What is the Java Native Interface?
see [Wikipedia](https://en.wikipedia.org/wiki/Java_Native_Interface)

> The Java Native Interface (JNI) is a foreign function interface programming 
framework that enables Java code running in a Java virtual machine (JVM) to 
call and be called by native applications (programs specific to a hardware 
and operating system platform) and libraries written in other languages such 
as C, C++ and assembly.

## Getting Started

These instructions will get you a copy of the project up and running on your 
local machine for development and testing purposes.

### Prerequisites (Windows)

* Git
* JDK (Java SDK)
* MinGW (per example [this distro](https://nuwen.net/mingw.html))

### Prerequisites (Linux)
* Git
* JDK (Java SDK)
* gcc, g++ and clang
* ncurses development package (per example libncurses-dev or ncurses-devel)

### Setting up your system
* check if the JAVA_HOME environment variable points to the root dir of the 
JDK installation
* check if the javac command can be executed in your terminal app
* check if you can run the installed compiler in your terminal app 
(g++ on Windows, clang++ on Linux)
    - if not add the bin folder to your path environment variable

### How to start the project
* clone this repo
* navigate your terminal to the scripts folder
* open the build script for your operating system
