#!/bin/sh
# Buildsystem for JNIHelper - Windows
# (c) 2020 Gabriel Daenner

if [ -z "$JAVA_HOME" ]
then
    echo Error: JAVA_HOME is not set on this system.
    echo You can set the environment variable by running one of the following commands:
    echo "  export JAVA_HOME=\"/usr/lib/jvm/java-14-openjdk-amd64/\""
    echo "  echo 'export JAVA_HOME=\"/usr/lib/jvm/java-14-openjdk-amd64/\"' >> ~/.bashrc"
    echo The first command is only for the current shell session.
    echo The second command is persistent but requires a restart of the shell.
    echo The path above is only an example and may differ.
    exit
fi

echo Cleaning up build directory ...
cd ../bin
rm -f *.class

echo Compiling sources ...
cd ..
javac -d ./bin $(find . -name '*.java')

echo Running example-app ...
cd ./bin
java TestApp noMenu
