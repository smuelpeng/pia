#!/bin/sh
#
# refresh pia.* from git master

NAME=pia
URL="https://raw.githubusercontent.com/jjgreen/$NAME/master"

for ext in c h
do
    FILE="$NAME.$ext"
    echo -n "$FILE .."
    wget -q $URL/$FILE -O $FILE
    echo ". done"
done
