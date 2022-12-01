#!/bin/bash

#* project relative path
PROJECT_PATH=../..
CLEAR_DIR=$PROJECT_PATH/build
CLEAR_EXE=$PROJECT_PATH/*.exe

#*  change the cwd to the script dir temporarily, and hide pushd popd output
pushd () { 
	command pushd "$@" > /dev/null 
}
popd () { 
	command popd "$@" > /dev/null 
}
pushd "$(dirname ${BASH_SOURCE:0})"
trap popd EXIT #*

rm -f $CLEAR_EXE
if [[ $? -eq 0 ]]; then
   echo "Removed $CLEAR_EXE"
fi

#* remove
if [[ -f "$CLEAR_FILE" ]]; then
rm -f $CLEAR_FILE

if [[ $? -eq 0 ]]; then
   echo "Removed $CLEAR_FILE"
fi
fi

echo "$0 done."
