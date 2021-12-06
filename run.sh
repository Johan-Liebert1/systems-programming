#!/bin/bash

name=""
run="0"

if [[ $2 == "run" ]]; then
name="exec"
run="1"
else
name="$2"
fi

if [[ $3 == "run" ]]; then
run="1"
fi

gcc $1 -o "bin/$name"

if [[ $run == "1" ]]; then
    "./bin/$name"
fi