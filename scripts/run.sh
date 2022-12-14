#!/bin/bash

#* project's relative path with respect to this script
PROJECT_PATH=..
BUILD_DIR=build/bin
#EXECUTABLES="template day1 day2 day3 day4 day5 day6 day7"
EXECUTABLES="day7"

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

#* cd into build directory
pushd $PROJECT_PATH
trap popd EXIT #*

UNAME=$(uname)

for exe in $EXECUTABLES
do
	if [[ $UNAME == "Linux" ]] ; then
		printf "\n---> Running $exe...\n"
		$BUILD_DIR/$exe
	elif [[ $UNAME == "MSYS"* ]] ; then
		printf "\n---> Running $exe.exe...\n"
		$BUILD_DIR/$exe.exe
	fi
done

echo "$0 done."
