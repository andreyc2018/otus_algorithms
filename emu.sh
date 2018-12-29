#!/bin/sh

if [ -n "$1" ]
then
    input=`readlink -f $1`
    cmd="--input $input"
fi

cd $HOME/apps/emuStudio
echo "Running java -jar emuStudio.jar --config RAM $cmd"
java -jar emuStudio.jar --config RAM $cmd &> emu.log &

