#!/bin/bash

name=$1

mkdir -p bin

gcc $1 -o "bin/out"
./bin/out
