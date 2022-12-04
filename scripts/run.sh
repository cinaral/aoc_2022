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

printf "\nRun template.exe...\n"
$BUILD_DIR/template.exe

printf "\nRun day1.exe...\n"
$BUILD_DIR/day1.exe

printf "\nRun day2.exe...\n"
$BUILD_DIR/day2.exe

printf "\nRun day3.exe...\n"
$BUILD_DIR/day3.exe

printf "\nRun day4.exe...\n"
$BUILD_DIR/day4.exe

echo "$0 done."
