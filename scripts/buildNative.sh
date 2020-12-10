#!/bin/bash
# Buildsystem for JNIHelper - Linux
# (c) 2020 Gabriel Daenner

# variables
CLEAR="\e[0m"
RED="\e[1;31m"
PREFERRED_COMPILER="clang++"
SKIP_CHECKS="false"

# functions
function buildNative()
{
    cd ../src

    echo "Compiling JNIHelper.java ..."
    javac ./java/JNIHelper.java
    echo "Generating resources ..."
    javac ./java/JNIHelper.java -h ./native
    echo "Creating shared library ..."
    $PREFERRED_COMPILER -fPIC -shared -Wall -O2 -o ../bin/libCLib.so \
        ./native/JNIHelper.cpp ./native/posix.cpp                    \
        -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux"          \
        -lm -lncurses -lportaudio
    echo "Cleaning up ..."
    find . -name "*.class"     -type f -delete
    find . -name "JNIHelper.h" -type f -delete
    find . -name "*.obj"       -type f -delete

    cd ../scripts
    exit
}

function checkEnvironment()
{
    if [ -z "$JAVA_HOME" ]
    then
        printError "JAVA_HOME is not set on this system."
        echo "You can set the environment variable by running one of the following commands:"
        echo "  export JAVA_HOME=\"/usr/lib/jvm/java-14-openjdk-amd64/\""
        echo "  echo 'export JAVA_HOME=\"/usr/lib/jvm/java-14-openjdk-amd64/\"' >> ~/.bashrc"
        echo "The first command is only for the current shell session."
        echo "The second command is persistent but requires a restart of the shell."
        echo "The path above is only an example and may differ."
        exit
    fi

    if ! [ -x "$(command -v javac)" ]
    then
        printError "javac seems to be missing. Ensure it is installed." >&2
        exit
    fi

    if [ "$PREFERRED_COMPILER" == "clang++" ]
    then
        if ! [ -x "$(command -v clang++)" ]
        then
            printError "clang++ seems to be missing. Ensure it is installed." >&2
            exit
        fi
    elif [ "$PREFERRED_COMPILER" == "g++" ]
    then
        if ! [ -x "$(command -v g++)" ]
        then
            printError "g++ seems to be missing. Ensure it is installed." >&2
            exit
        fi
    fi
}

function printError()
{
    if [ -n "$1" ]
    then
        echo -e "${RED}error: ${CLEAR}$1"
        if [ -n "$2" ]
        then
            echo -e "Type '$0 --help' for usage"
        fi
    fi
}

function printHelp()
{
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -c, --use-clang    Prefer clang++ as default compiler."
    echo "  -g, --use-gcc      Prefer g++ as default compiler."
    echo "  -h, --help         Display this information."
    echo "  -s, --skip-checks  Skip all environment checks."
    echo "Example: $0 --use-gcc --skip-checks"
    exit
}

# parse arguments
while [[ "$#" > 0 ]]
    do case $1 in
        -c|--use-clang)   PREFERRED_COMPILER="clang++"; shift;;
        -g|--use-gcc)     PREFERRED_COMPILER="g++"; shift;;
        -h|--help)        printHelp; shift;;
        -s|--skip-checks) SKIP_CHECKS="true"; shift;;
        *) printError "Unknown parameter passed: $1" "hint"; exit; shift;;
    esac
done

# start build
if [ "$SKIP_CHECKS" == "true" ]
then
    buildNative
else
    checkEnvironment
    buildNative
fi
