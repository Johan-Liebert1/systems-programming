#!/bin/bash

name=$1

mkdir -p bin

gcc $1 -pthread -o "bin/out"
./bin/out ${@:2}
