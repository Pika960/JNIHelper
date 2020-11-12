#!/bin/bash
# Buildsystem for JNIHelper - Linux
# (c) 2020 Gabriel Daenner

# variables
CLEAR="\e[0m"
JAVA_ARGS="noMenu"
RED="\e[1;31m"
SKIP_CHECKS="false"

# functions
function buildExample()
{
    cd ../bin
    echo "Cleaning up build directory ..."
    rm -f *.class

    cd ..
    echo "Compiling sources ..."
    javac -d ./bin $(find . -name '*.java')

    cd ./bin
    echo "Running example-app ..."
    java TestApp "$JAVA_ARGS"

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

    if ! [ -x "$(command -v java)" ]
    then
        printError "java seems to be missing. Ensure it is installed." >&2
        exit
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
    echo "  -h, --help         Display this information."
    echo "  -i, --interactive  Start example application in interactive mode"
    echo "  -q, --quick        Start example application in quick mode"
    echo "  -s, --skip-checks  Skip all environment checks."
    echo "Example: $0 --interactive --skip-checks"
    exit
}

# parse arguments
while [[ "$#" > 0 ]]
    do case $1 in
        -h|--help)        printHelp; shift;;
        -i|--interactive) JAVA_ARGS=""; shift;;
        -q|--quick)       JAVA_ARGS="noMenu"; shift;;
        -s|--skip-checks) SKIP_CHECKS="true"; shift;;
        *) printError "Unknown parameter passed: $1" "hint"; exit; shift;;
    esac
done

# start build
if [ "$SKIP_CHECKS" == "true" ]
then
    buildExample
else
    checkEnvironment
    buildExample
fi
