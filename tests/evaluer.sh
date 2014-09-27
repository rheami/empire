#!/bin/bash
# Script pour INF3105/2014A/TP1
# http://ericbeaudry.ca/INF3105/tp1/

# Détection du répertoire contenant le présent script
repertoire_tests=`dirname $0`
# Lister les fichier carte*.txt disponibles
cartes=`cd $repertoire_tests && ls carte*.txt`

# Exécutable du programme à évaluer
programme="tp1"
# Exécutable du programme de validation
OS=`uname`
valideur="${repertoire_tests}/valideur"

if [ -x ${valideur}-${OS} ]
then
    valideur=${valideur}-${OS}
fi

echo "Évaluation des temps d'exécution de ${programme} sur les jeux de tests."

# Détection si l'utilitaire time sous Linux est disponible (peut afficher 0.00)
/usr/bin/time -f %U echo 2>&1 > /dev/null
souslinux=$?

# Mettre une limite de temps.
#ulimit -t 1200 -v 122880 -f 20

echo "Limites :"
ulimit -t -v -f

# Vérification de l'existance du programme.
if [ ! -e ${programme} ]
	then
	echo "  ERREUR : le programme ${programme} est inexistant!"
	exit -1
fi
if [ ! -x ${programme} ]
	then
	echo "  ERREUR : l'executable ${programme} n'est pas exécutable!"
	exit -1
fi

date=`date +%Y%m%d_%H%M%S`
logfile="log-${date}.txt"

echo "Les résultats sont déposés dans $logfile."


echo "Machine : " `hostname` "."
echo "#Machine : " `hostname` "."  > $logfile
echo "Date début : $date."
echo "#Date début : $date."  >> $logfile
echo "Limite de `ulimit -t` secondes par test."
echo "#Limite de `ulimit -t` secondes par test."  >> $logfile
echo 
echo "#" >> $logfile

echo -e "Carte\tTaille\tRequete\tSuperficie\tOpt?\tCPU\tMém.(k)"
echo -e "Carte\tTaille\tRequete\tSuperficie\tOpt?\tCPU\tMém.(k)" >> $logfile

requetes="1 2 2-100 2-50 2-10 2-1 3 4"

for carte in $cartes;
do
    fichiercarte=$repertoire_tests/$carte

    for requete in $requetes;
    do

        args=`echo $requete | sed s/'-'/' '/g`
        taillecarte=`cat $fichiercarte | wc -l`
        
        fichierresultat="${carte%.txt}_${requete}.resultat"
        fichiersolution="$repertoire_tests/${carte%.txt}_${requete}.resultat"
        
        if [ $souslinux -eq 0 ]; then
            #echo "./$programme $fichiercarte $args"
            #./$programme $fichiercarte $args
            tcpu="`(/usr/bin/time -f "%U\t%Mk" ./$programme $fichiercarte $args > $fichierresultat) 2>&1 | tail -n 1`"
        else
            tcpu=`(time -p ./$programme $fichiercarte $args > $fichierresultat) 2>&1 | egrep user | cut -f 2 -d " "`
        fi
        
        compteresultat="?"
        optimal="?"
        if ( [ -x ${valideur} ] && [ -e $fichierresultat ] )
        then
            compteresultat=`$valideur $fichiercarte $fichierresultat $args`
            if( [ -e $fichiersolution ] )
            then
                comptesolution=`$valideur $fichiercarte $fichiersolution $args`
                [ "$compteresultat" != "$comptesolution" ];
                optimal=$?
            fi
        else
            compteresultat=`head -n 1 $fichierresultat`
            if( [ -e $fichiersolution ] )
            then
                diff -tibw $fichierresultat $fichiersolution 2>&1 > /dev/null
            	if [ $? -eq 0 ];
            	then
            	    optimal="OK"
             	else
             	    optimal="Echec"
            	fi
            fi
        fi

        echo -e "$carte\t$taillecarte\t$requete\t$compteresultat\t$optimal\t$tcpu"
        echo -e "$carte\t$taillecarte\t$requete\t$compteresultat\t$optimal\t$tcpu" >> $logfile
  
    done
 
done


