#!/bin/sh

cd Sources
qmake
make && cp -v tabula_rasa ../

echo "Vous pouvez lancer l'application en tapant la commande \"./tabula_Rasa\" "


