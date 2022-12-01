#!/bin/bash

#* project relative path
PROJECT_PATH=../..
BUILD_DIR=$PROJECT_PATH

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

if ! [[ -d "$BUILD_DIR" ]]; then
	mkdir $BUILD_DIR
fi

pushd $BUILD_DIR

g++ -g -o main.exe main.cpp

trap popd EXIT 

./main.exe 

echo "$0 done."
