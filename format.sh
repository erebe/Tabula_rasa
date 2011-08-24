#!/bin/bash

if [ $# != 1 ]; then
	echo Il faut donner le chemin où formatter les fichier
fi

find $1 -name *.hpp -exec astyle '{}' \;
find $1 -name *.cpp -exec astyle '{}' \;
find $1 -name *.orig -exec rm '{}' \;
