#!/bin/sh

DATE=$(date +%Y%m%d)
TIME=$(date +%H%M)
FILENAME=${DATE}_ 
FILENAME=${FILENAME}$TIME
touch TODO_$FILENAME