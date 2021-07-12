#!/bin/bash

echo Setting up INTELLIpad for you!

#set up dictionaries in ~/.INTELLIpad
origin=$(pwd)
mkdir ~/.INTELLIpad
cd ~/.INTELLIpad
touch activeDic
echo .INTELLIpad/usa2.txt
cd origin
mv *.txt ~/.INTELLIpad

sudo mv INTELLIpad /usr/bin