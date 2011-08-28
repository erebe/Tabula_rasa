#!/bin/bash

if [ $# != 1 ]; then
	echo Il faut donner le chemin où formatter les fichier
fi

liste=`find $1 \( -name *.cpp -o -name *.hpp \)`

for path in $liste
do
    astyle $path
    cat $path | sed -e 's/^{$/{\/*{{{*\//' | sed -e 's/^}$/}\/*}}}*\//' > tmp
    grep -v -E '^\s+/\*{{{' tmp > $path


done

find $1 -name *.orig -exec rm '{}' \;
rm tmp
