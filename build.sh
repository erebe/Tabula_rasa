#!/bin/sh

cd Sources
qmake
make && cp tabula_rasa ../

NORMAL="\\033[39;49;00m"
ROUGE="\\033[1;31m"
VERT="\\033[1;32m"

echo -e "\n\n${ROUGE}Vous pouvez lancer l'application en tapant la commande ${VERT}./tabula_rasa"
echo -e "${ROUGE}Installer l'application dans ${VERT}/usr/bin ${ROUGE}? [o/n] ${NORMAL}" 
read reponse

if [ $reponse == "o" ]
then
    echo ''
    sudo make install
    echo -e "${ROUGE}Terminé ! Tapez directement ${VERT}tabula_rasa ${ROUGE}dans votre terminal pour lancer l'application${NORMAL}"
fi


