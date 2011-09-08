#!/bin/sh

cd Sources
qmake
make && cp tabula_rasa ../

ROUGE="\\033[1;31m"
VERT="\\033[1;32m"

echo -e "\n\n${ROUGE}Vous pouvez lancer l'application en tapant la commande ${VERT}./tabula_Rasa
${ROUGE}Pour installer l'application, tapez la commande ${VERT}sudo make install"


