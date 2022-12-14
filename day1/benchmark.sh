#!/bin/bash

#* project relative path
PROJECT_PATH=..
EXECUTABLE=build/bin/day1.exe

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

#* run the executable with different top n list sizes
$PROJECT_PATH/$EXECUTABLE 1
$PROJECT_PATH/$EXECUTABLE 3
$PROJECT_PATH/$EXECUTABLE 16
$PROJECT_PATH/$EXECUTABLE 32
$PROJECT_PATH/$EXECUTABLE 64
$PROJECT_PATH/$EXECUTABLE 128
