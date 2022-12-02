#!/bin/bash

#* project relative path
PROJECT_PATH=..
BUILD_DIR=build/bin

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

pushd $PROJECT_PATH
trap popd EXIT #*

#$BUILD_DIR/day1.exe
$BUILD_DIR/day2.exe

echo "$0 done."
