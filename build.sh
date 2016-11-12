#!/bin/bash

NORMAL="\\033[39;49;00m"
ROUGE="\\033[1;31m"
VERT="\\033[1;32m"

QMAKE=$(which qmake-qt5 2> /dev/null)

if [ -z "${QMAKE}" ]
then
    QMAKE=$(which qmake)
fi

cd Sources
${QMAKE} || exit 0
make -j3 || exit 0
cp tabula_rasa ../


echo -e "\n\n${ROUGE}Vous pouvez lancer l'application en tapant la commande ${VERT}./tabula_rasa"

echo -e "${ROUGE}Vous pouvez installer l'application dans ${VERT}/usr/bin${ROUGE} en tapant "
echo -e "${VERT}cd Sources; sudo make install${NORMAL}" 


