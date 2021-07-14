#!/bin/bash

echo Setting up INTELLIpad!

#set up dictionaries in ~/.INTELLIpad
origin=$(pwd)
mkdir ~/.INTELLIpad
cd ~/.INTELLIpad
touch activeDic
echo .INTELLIpad/usa2.txt > ~/.INTELLIpad/activeDic
cd origin
mv *.txt ~/.INTELLIpad

sudo chmod +x INTELLIpad
sudo mv INTELLIpad /usr/bin
