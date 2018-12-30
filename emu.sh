#!/bin/sh

if [ -n "$1" ]
then
    input=`readlink -e $1`
    if [ -z "$input" ]
    then
        echo "File not found: $1"
        exit 1
    fi
    cmd="--input $input"
fi

cd $HOME/apps/emuStudio
echo "Running java -jar emuStudio.jar --config RAM $cmd"
java -jar emuStudio.jar --config RAM $cmd &> emu.log &

