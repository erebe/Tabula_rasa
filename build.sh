#!/bin/bash

NORMAL="\\033[39;49;00m"
ROUGE="\\033[1;31m"
VERT="\\033[1;32m"

QMAKE=$(which qmake-qt4 2> /dev/null)

if [ -z "${QMAKE}" ]
then
    QMAKE=$(which qmake)
fi

cd Sources
${QMAKE} || exit 0
make || exit 0
cp tabula_rasa ../


echo -e "\n\n${ROUGE}Vous pouvez lancer l'application en tapant la commande ${VERT}./tabula_rasa"

echo -e "${ROUGE}Voulez-vous installer l'application dans ${VERT}/usr/bin ${ROUGE}? [o/n] ${NORMAL}" 

read reponse

if [ "${reponse}" == "o" ]
then
    sudo make install
    echo -e "${ROUGE}Terminé ! Tapez directement ${VERT}tabula_rasa ${ROUGE}dans votre terminal pour lancer l'application${NORMAL}"
    echo ''
fi


