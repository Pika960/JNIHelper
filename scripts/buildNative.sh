#!/bin/sh
# Buildsystem for JNIHelper - Windows
# (c) 2020 Gabriel Daenner

if [ -z "$JAVA_HOME" ]
then
    echo Error: JAVA_HOME is not set on this system.
    echo You can add this to by running the one of the following commands:
    echo "export JAVA_HOME=\"/usr/lib/jvm/java-11-openjdk-amd64/\""
    echo "export JAVA_HOME=\"/usr/lib/jvm/java-11-openjdk-amd64/\" >> ~/.bashrc"
    echo First one is only for this session, second one permanently
    echo The path above is only an example and may differ
    exit
fi

echo Compiling sources ...
cd ../src
rm -f *.class *.h
javac JNIHelper.java
javac JNIHelper.java -h .
clang++ -fPIC -shared -o ../bin/libCLib.so JNIHelper.cpp -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -lncurses

echo Cleaning up ...
rm -f *.class *.h
cd ../scripts
