#!/bin/bash

: > .gitignore

for filename in *.c; do
    echo ${filename%.c} >> .gitignore
done