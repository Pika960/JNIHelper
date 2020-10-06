# JNIHelper

JNIHelper is a helper library which gives you more interaction possibilities
between your java application and the system the application is running on.

## What is the Java Native Interface?
see [Wikipedia](https://en.wikipedia.org/wiki/Java_Native_Interface)

> The Java Native Interface (JNI) is a foreign function interface programming
framework that enables Java code running in a Java virtual machine (JVM) to
call and be called by native applications (programs specific to a hardware
and operating system platform) and libraries written in other languages such
as C, C++ and assembly.

## What targets are supported by this library?
* the library itself is compatible with Windows and Linux
* the main target of this project are console applications
    - some functions should work without problems in graphical applications
* this library only supports platform specific native environments
    - this means, for example, that applications like Mintty are not supported

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites (Windows)

* Git
* JDK (Java SDK)
* MinGW (per example [this distro](https://nuwen.net/mingw.html))
* Microsoft Visual Studio 2017 or newer with the C++ workload
    - you only need MinGW or Visual Studio to build this project

### Prerequisites (Linux)
* Git
* JDK (Java SDK)
* gcc, g++ and clang
* ncurses development package (per example libncurses-dev or ncurses-devel)
* PortAudio development package (per example portaudio-devel)

### A note about installing PortAudio on Ubuntu and Debian
Installing `portaudio19-dev` downgrades the JACK Audio Connection Kit package
from jackd2 to jackd1. To prevent this behavior, you must install the
`libjack-jackd2-dev` package before installing portaudio19-dev. This fulfills
the dependencies of the PortAudio development package without having to
downgrade jackd2.

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
