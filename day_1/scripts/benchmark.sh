#!/bin/bash

#* project relative path
PROJECT_PATH=..
COMMON_COMMAND="main.exe $PROJECT_PATH/input.txt"

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

$PROJECT_PATH/$COMMON_COMMAND 1
$PROJECT_PATH/$COMMON_COMMAND 3
$PROJECT_PATH/$COMMON_COMMAND 16
$PROJECT_PATH/$COMMON_COMMAND 32
$PROJECT_PATH/$COMMON_COMMAND 64
$PROJECT_PATH/$COMMON_COMMAND 256
