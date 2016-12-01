#!/bin/sh

SHBASH=/bin/bash
SHCSH=/bin/csh
SH=./42sh
OUT=tmp
OUTB=tmp2
V=0
COUNTER=0
FAIL=0
COMMAND=""
BEHAVIOR=""

check_diff() {
	COUNTER=$((COUNTER+1))
	echo ${COMMAND} | ${SH} > ${OUT} 2>&1
	if [ -n "$2" ]
	then
		COMMAND="$2"
	fi
	echo ${COMMAND} | $1 > ${OUTB} 2>&1
	diff ${OUT} ${OUTB} > tmp3

	a=$(stat -f%z tmp3)
	if [ $a = 0 ]
	then
		printf "\033[1;32;40m.\033[0m"
	else
		printf "\033[1;31;40mX\033[0m"
		FAIL=$((FAIL+1))
	fi
	if [ $V = 1 ]
	then
		printf "  $COMMAND\n"
	fi
}

check_good_behavior() {
	COUNTER=$((COUNTER+1))
	echo ${COMMAND} | ${SH} > ${OUT} 2>&1
	if [ "$1" == "-n" ]
	then
	printf "${BEHAVIOR}" > ${OUTB} 2>&1
	else
	echo ${BEHAVIOR} > ${OUTB} 2>&1
	fi
	diff ${OUT} ${OUTB} > tmp3
	a=$(stat -f%z tmp3)
	if [ $a = 0 ]
	then
		printf "\033[1;32;40m.\033[0m"
	else
		printf "\033[1;31;40mX\033[0m"
	fi
	if [ $V == 1 ]
	then
		printf "  $COMMAND\n"
	fi
}

diff_exit() {
	echo ${COMMAND} | ${SH}
	echo "$?" > ${OUT}
	if [ -n "$2" ]
	then
		COMMAND="$2"
	fi
	echo ${COMMAND} | $1
	echo "$?" > ${OUTB}
	diff ${OUT} ${OUTB} > tmp3

	a=$(stat -f%z tmp3)
	if [ $a = 0 ]
	then
		printf "\033[1;32;40m.\033[0m"
	else
		printf "\033[1;31;40mX\033[0m"
	fi
	if [ $V = 1 ]
	then
		printf "  $COMMAND\n"
	fi
}

#===INIT===#
mkdir test_noperm_dir
chmod 000 test_noperm_dir
mkdir test_dir
touch test_reg_file
#==========#

echo "SCRIPT DE TEST DU 42SH :"
echo "Utiliser le -v pour mettre le mode verbose"


if [ "$1" == "-v" ]
then
	printf "\033[1;32;40mVerbose mod ON\n\033[0m"
	V=1
else
	V=0
fi

touch tmp tmp2 tmp3
#===TESTS Basiques===#
printf "basic tests: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="cat -e auteur"
BEHAVIOR="tbreart$\njmaccion$\nfjacquem$\nmfamilar$"
check_good_behavior

COMMAND="ls"
check_diff ${SHCSH}

COMMAND="mkdir \"Salut ca va ?\""
COMMAND="mkdir \"YOO\""
COMMAND="mkdir OLA"

COMMAND="ls"
check_diff ${SHCSH}

COMMAND="rm -rf  \"Salut ca va ?\""
COMMAND="rm -rf  \"YOO\""
COMMAND="rm -rf  OLA"

COMMAND="pwd"
check_diff ${SHCSH}

COMMAND="ls -ar"
check_diff ${SHCSH}

COMMAND="ls -a -r"
check_diff ${SHCSH}

COMMAND="ls -la -z"
check_diff ${SHCSH}

COMMAND="/bin/ls"
check_diff ${SHCSH}

COMMAND="/bin/ls -ar"
check_diff ${SHCSH}

COMMAND="ls ~"
check_diff ${SHCSH}

COMMAND="ls $HOME"
check_diff ${SHCSH}

COMMAND="invalid_command"
check_diff ${SHCSH}

COMMAND="              ls               -a      -r        "
check_diff ${SHCSH}

COMMAND="          			    ls               -a      			-r  		"
check_diff ${SHCSH}

COMMAND="			ls 			~			"
check_diff ${SHCSH}

COMMAND="\n"
check_diff ${SHCSH}

COMMAND=""
check_diff ${SHCSH}

COMMAND="        "
check_diff ${SHCSH}

COMMAND="       		 	 		 	 			     						"
check_diff ${SHCSH}

printf "\n"

#===TESTS SÉPARATEURS===#
printf "séparateurs: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="ls ; ls"
check_diff ${SHCSH}

COMMAND=";"
check_diff ${SHCSH}

COMMAND=";;;;;;;;;;;;;;;"
check_diff ${SHCSH}

COMMAND="ls;;;;;ls -a;;;;;pwd;			   ;;;;"
check_diff ${SHCSH}

COMMAND="ls;ls; ls; ls;"
check_diff ${SHCSH}

COMMAND="ls;truc;ls;"
check_diff ${SHCSH}

printf "\n"

#===TESTS BUILTIN ECHO===#
printf "builtin_echo: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="echo"
check_diff ${SHCSH}

COMMAND="echo \"It works\""
check_diff ${SHCSH}

COMMAND="echo -n"
check_diff ${SHCSH}

COMMAND="echo -n -n -nnnnnn -n -nn"
check_diff ${SHBASH}

COMMAND="echo -n -n -nnnnnn -n -nn --"
check_diff ${SHBASH}

COMMAND="echo toto tata"
check_diff ${SHCSH}

COMMAND="echo -n toto"
check_diff ${SHCSH}

COMMAND="echo -n -n -n -n -n -nnnn toto"
check_diff ${SHBASH}

COMMAND="echo -- tata"
check_diff ${SHCSH}

COMMAND="echo -n -n -n -n -nnnn -n-n -- toto"
check_diff ${SHBASH}

COMMAND="echo -n -n -n -n -n -nnnn -n -n -- tata"
check_diff ${SHBASH}

COMMAND="echo ~"
check_diff ${SHCSH}

COMMAND="echo \"~\""
check_diff ${SHCSH}

COMMAND="echo \"coucou mec\""
check_diff ${SHCSH}

COMMAND="setenv POLO=pola ;echo $POLO"
check_diff ${SHCSH}

COMMAND="unsetenv POLO;echo POLO"
check_diff ${SHCSH}

COMMAND="echo $HOME/Desktop"
check_diff ${SHCSH}

COMMAND="echo $HOME > file ; cat file"
check_diff ${SHCSH}

printf "\n"

#===TESTS VALEURS DE RETOUR===#
printf "valeurs de retour: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="		ls  ;echo \$?"
check_diff ${SHBASH}

COMMAND="ls -z; echo \$?"
check_diff ${SHBASH}

COMMAND="ls -z | cat ;  echo \$?"
check_diff ${SHBASH}

COMMAND="ls -z || cat ;  echo \$?"
check_diff ${SHBASH}

COMMAND="ls -z && cat ;  echo \$?"
check_diff ${SHBASH}

printf "\n"

#===TESTS BUILTIN CD===#
printf "builtin_cd: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="cd a b c"
check_diff ${SHCSH}

COMMAND="cd ~/Desktop ; /bin/pwd"
check_diff ${SHCSH}

COMMAND="cd .. ; /bin/pwd"
check_diff ${SHCSH}

COMMAND="cd ; /bin/pwd"
check_diff ${SHCSH}

COMMAND="cd / ; /bin/pwd"
check_diff ${SHCSH}

COMMAND="cd ; cd / ; cd - ; /bin/pwd"
check_diff ${SHBASH}

COMMAND="cd;pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd ..;pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd /;pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd . ;pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd ~ ;pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd /;cd ..; cd ../..; pwd ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd wertytui"
check_diff ${SHCSH}

COMMAND="cd test_file"
check_diff ${SHCSH}

COMMAND="cd test_noperm_dir"
check_diff ${SHCSH}

COMMAND="unsetenv HOME;cd"
check_diff ${SHCSH} "unset home;unsetenv HOME;cd"

COMMAND="cd test_dir;pwd;cd -;pwd;cd -;pwd"
check_diff ${SHBASH}

COMMAND="unsetenv OLDPWD;cd -"
BEHAVIOR="OLDPWD not set"
check_good_behavior

COMMAND="setenv HOME=caca ;cd ~"
check_diff ${SHCSH}

COMMAND="setenv HOME=caca ;cd"
check_diff ${SHCSH}

COMMAND="cd .;pwd"
check_diff ${SHCSH}

COMMAND="cd ..;pwd"
check_diff ${SHCSH}

COMMAND="cd ../../;pwd"
check_diff ${SHCSH}

COMMAND="cd ../../;echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}
# exit
COMMAND="unsetenv PWD;echo \$PWD;cd ..;echo \$PWD"
check_diff ${SHBASH} "unset PWD;echo \$PWD;cd ..;echo \$PWD"

COMMAND="cd test_dir;mkdir test_dir_del;cd test_dir_del; rm -Rf ../test_dir_del;pwd;ls;echo \$PWD;cd ..;cd /;pwd"
check_diff ${SHCSH}

COMMAND="cd ; cd ./Desktop ; echo \$PWD;echo \$OLDPWD ; cd ../Downloads ; echo \$PWD;echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd ~/Desktop ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd ////; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd /tmp/;pwd"
check_diff ${SHBASH}

COMMAND="cd -L /tmp/;pwd"
check_diff ${SHBASH}

COMMAND="cd -P /tmp/;pwd"
check_diff ${SHBASH}

COMMAND="cd ; cd goinfre ; pwd ; cd ..; pwd"
check_diff ${SHBASH}

COMMAND="cd ; cd -L goinfre ; pwd ; cd ..; pwd"
check_diff ${SHBASH}

COMMAND="cd ; cd -P goinfre ; pwd ; cd ..; pwd"
check_diff ${SHBASH}

COMMAND="cd ../../../../../../../../../ ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

printf "\n"

#===TESTS BUILTIN SETENV===#
printf "builtin_setenv: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="setenv a b c"
check_diff ${SHCSH}

COMMAND="setenv a b; echo \$a"
check_diff ${SHCSH}

COMMAND="setenv \$"
check_diff ${SHCSH}

COMMAND="setenv \$\$"
check_diff ${SHCSH}

COMMAND="setenv @abc"
check_diff ${SHCSH}

COMMAND="setenv abc@"
check_diff ${SHCSH}

COMMAND="setenv \$PWD plop;echo \$PWD"
check_diff ${SHCSH}

COMMAND="setenv \$PWD;echo \$PWD"
check_diff ${SHCSH}

COMMAND="setenv a;echo \$a;setenv a plop;echo \$a"
check_diff ${SHCSH}

COMMAND="setenv USER=machin"
check_diff ${SHCSH}

COMMAND="setenv coucou=1"
check_diff ${SHCSH}

COMMAND="setenv 1 2 3 4"
check_diff ${SHCSH}

COMMAND="setenv 1plop coco"
check_diff ${SHCSH}

COMMAND="setenv coucou=truc USER=truc truc=bidule"
check_diff ${SHCSH}

COMMAND="setenv coucou=\"test\""
check_diff ${SHCSH}

COMMAND="setenv 0=\"test\""
check_diff ${SHCSH}

# BEHAVIOR="setenv: Variable name must contain alphanumeric characters."
# check_good_behavior

printf "\n"

#===TESTS BUILTIN UNSETENV===#
printf "builtin_unsetenv: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="unsetenv"
check_diff ${SHCSH}

COMMAND="setenv a plop;echo \$a;unsetenv a;echo \$a"
check_diff ${SHBASH} "export a=plop; echo \$a; unset a; echo \$a"

COMMAND="setenv a 1;setenv b 2;setenv c 3;echo \$a \$b \$c;unsetenv b c;echo \$a \$b \$c"
check_diff ${SHBASH} "export a=1 b=2 c=3; echo \$a \$b \$c; unset b c; echo \$a \$b \$c"

COMMAND="unsetenv a b c"
check_diff ${SHCSH}

printf "\n"

#===TESTS BUILTIN ENV===#
printf "builtin_env: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="env ls"
check_diff ${SHCSH}

COMMAND="env /bin/ls"
check_diff ${SHCSH}

COMMAND="env ls -ar"
check_diff ${SHCSH}

COMMAND="env -i"
check_diff ${SHCSH}

COMMAND="env -i ls"
check_diff ${SHCSH}

COMMAND="env -i a=a"
check_diff ${SHCSH}

COMMAND="env -i coco=\"test\""
check_diff ${SHCSH}

COMMAND="env -i a=a env"
check_diff ${SHCSH}

COMMAND="env -i a=a b=b c=a a=z"
check_diff ${SHCSH}

COMMAND="env -u"
BEHAVIOR="env: option requires an argument -- u"
check_good_behavior

COMMAND="env pwd"
check_diff ${SHCSH}

COMMAND="env PATH=fake ls"
check_diff ${SHBASH}

COMMAND="env -i pwd"
check_diff ${SHBASH}

COMMAND="env -i PWD=plop pwd"
check_diff ${SHBASH}

COMMAND="env -i a=apwd ls"
check_diff ${SHBASH}

COMMAND="env pwd ls"
check_diff ${SHCSH}

COMMAND="env -iu"
BEHAVIOR="env: option requires an argument -- u"
check_good_behavior

COMMAND="env -ui"
BEHAVIOR="env: option requires an argument -- u"
check_good_behavior

COMMAND="env -ui LESS"
BEHAVIOR=""
check_good_behavior "-n"

COMMAND="env -ui PWD"
BEHAVIOR=""
check_good_behavior "-n"

COMMAND="env -ui xsacdvfbgnhj"
BEHAVIOR=""
check_good_behavior "-n"

COMMAND="env -i -u"
BEHAVIOR="env: option requires an argument -- u"
check_good_behavior

COMMAND="env -i -u -i"
BEHAVIOR=""
check_good_behavior "-n"

COMMAND="env -i -i -i"
BEHAVIOR=""
check_good_behavior "-n"

COMMAND="env -i -u PWD a=a PWD=plop pwd ls"
check_diff ${SHBASH}

COMMAND="env -i -u PWD PWD=plop pwd"
check_diff ${SHBASH}

COMMAND="env -z"
BEHAVIOR="env: illegal option -- z"
check_good_behavior

COMMAND="env -i -u -z"
check_diff ${SHCSH}

COMMAND="env -"
check_diff ${SHCSH}

COMMAND="env - a=a"
check_diff ${SHCSH}

COMMAND="env - - - - -      "
check_diff ${SHCSH}

COMMAND="env qwerty"
check_diff ${SHBASH}


COMMAND="env -i PATH=/bin pwd"
check_diff ${SHCSH}

printf "\n"

#===TESTS HISTORY et !===#
printf "builtin_history et !: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="history -p YOYOY \"salut ca va $USER\""
check_diff ${SHBASH}

COMMAND="history -p YOYOY SALUT CA VA"
check_diff ${SHBASH}

COMMAND="history -an"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -ar"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -anrw"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -nr"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -c ; history ; history -s YOYO ; history -d 1"
check_diff ${SHBASH}

COMMAND="history -s -s -s -s -s -- --\"dsfdsf sdf sdf sdf dsfdsf\"      sdfdsf       sdf ; history > file ; cat file"
check_diff ${SHBASH}

COMMAND="history -an"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -an"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="history -an"
BEHAVIOR="42sh: history: cannot use more than one of -anrw"
check_good_behavior

COMMAND="ls > /dev/null\necho toto > /dev/null\nhistory"
check_diff ${SHBASH}

printf "\n"

#===TESTS GESTION PATH===#
printf "gestion_path: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="unsetenv PATH ; ls"
BEHAVIOR="ls: Command not found."
check_good_behavior

COMMAND="unsetenv PATH ; /bin/ls"
check_diff ${SHCSH}

COMMAND="unsetenv PATH ; setenv PATH \"/bin:/usr/bin\" ; ls"
check_diff ${SHCSH}

COMMAND="ls | cat -e"
check_diff ${SHCSH}

printf "\n"

#===TESTS REDIRECTIONS===#
printf "redirections: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="ls | cat -e | cat -e | cat -e | cat -e"
check_diff ${SHCSH}

COMMAND="ls -r | cat -e | cat -e | cat -e | cat -e | sort"
check_diff ${SHCSH}

COMMAND="base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'"
check_diff ${SHBASH}

COMMAND=" echo \"Testing redirections\" > /tmp/test.txt ; cat /tmp/test.txt"
check_diff ${SHBASH}

COMMAND=" echo \"with multiple lines\" >> /tmp/test.txt  ; cat /tmp/test.txt"
BEHAVIOR="Testing redirections\nwith multiple lines"
check_good_behavior

COMMAND=" echo \"Testing redirections\" > /tmp/test.txt ;echo \"with multiple lines\" >> /tmp/test.txt ; wc -c < /tmp/test.txt ;"
check_diff ${SHBASH}

COMMAND=" read < auteur auteur"
BEHAVIOR="file bad formatted"
check_good_behavior

COMMAND="  ls > file -l ; cat file"
BEHAVIOR="file bad formatted"
check_good_behavior

COMMAND=" echo \"Hello!\" | tr \"[:lower:]\" \"[:upper:]\""
check_diff ${SHBASH}

printf "\n"

#===TESTS BONUS METACHARACTERS===#
printf "bonus_metacharacters: "
if [ $V == 1 ]
then
		printf "\n"
fi

COMMAND="echo $a$PWD$b"
check_diff ${SHBASH}

COMMAND="echo $PWD$PWD"
check_diff ${SHBASH}

COMMAND="echo $"
check_diff ${SHBASH}

COMMAND="echo \"\SALUT\""
check_diff ${SHBASH}

COMMAND="echo \"SAL\UT\""
check_diff ${SHBASH}

COMMAND="echo '\SALUT'"
check_diff ${SHBASH}

COMMAND="echo 'SAL\UT'"
check_diff ${SHBASH}

COMMAND="echo \$P"
check_diff ${SHBASH}

COMMAND="echo \$pwd"
check_diff ${SHBASH}

COMMAND="echo \$P aa"
check_diff ${SHBASH}

COMMAND="echo \$PWD aa"
check_diff ${SHBASH}

COMMAND="echo \$PWD$"
check_diff ${SHBASH}

COMMAND="echo \$PWD\$PWD"
check_diff ${SHBASH}

COMMAND="echo \$PWD\$PW"
check_diff ${SHBASH}

COMMAND="echo \$ \$"
check_diff ${SHBASH}

COMMAND="echo \$__\$"
check_diff ${SHBASH}

COMMAND="echo \$PWDaaa"
check_diff ${SHBASH}

COMMAND="echo \$PWD\"aaa\""
check_diff ${SHBASH}

COMMAND="echo \$PWD'aaa'"
check_diff ${SHBASH}

COMMAND="echo \$PWD\"$PWD\""
check_diff ${SHBASH}

COMMAND="echo \$PWD'$PWD'"
check_diff ${SHBASH}

COMMAND="echo \$PWD/aaa"
check_diff ${SHBASH}

COMMAND="echo \$PWD\aaa"
check_diff ${SHBASH}

COMMAND="\$A"
check_diff ${SHBASH}

COMMAND="echo \$\$"
BEHAVIOR="\$\$"
check_good_behavior

COMMAND="echo \$\$\$\$\$\$\$"
BEHAVIOR="\$\$\$\$\$\$\$"
check_good_behavior

COMMAND="setenv A pwd;\$A"
check_diff ${SHBASH} "export A=pwd;\$A"

COMMAND="setenv A ; \$A"
check_diff ${SHBASH} "export A=\"\";\$A"


printf "\n"

#===TESTS metacharacters===#
printf "bonus_metacharacters_~: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="echo ~"
check_diff ${SHBASH}

COMMAND="echo ~P"
check_diff ${SHBASH}

COMMAND="echo ~\$PWD"
check_diff ${SHBASH}

COMMAND="echo ~~"
check_diff ${SHBASH}

COMMAND="echo P~"
check_diff ${SHBASH}

COMMAND="echo ~ ~ ~"
check_diff ${SHBASH}

COMMAND="unsetenv HOME; echo ~"
BEHAVIOR="~"
check_good_behavior

COMMAND="setenv HOME; echo ~"
BEHAVIOR=""
check_good_behavior

printf "\n"

#===TESTS OPÉRATEURS LOGIQUES===#
printf "opérateurs logiques: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND=" ls || pwd"
check_diff ${SHBASH}

COMMAND=" ls -z || pwd"
check_diff ${SHBASH}

COMMAND=" history -p COCO || pwd"
check_diff ${SHBASH}

COMMAND=" setenv -z COCO || pwd"
check_diff ${SHCSH}

COMMAND=" ls && pwd"
check_diff ${SHBASH}

COMMAND=" ls -z && pwd"
check_diff ${SHBASH}

COMMAND=" history -p COCO && pwd"
check_diff ${SHBASH}

COMMAND=" setenv -z COCO && pwd"
check_diff ${SHCSH}

printf "\n"

#===TESTS INHIBITEURS===#
printf "inhibiteurs: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="\"\""
BEHAVIOR=": Command not found."
check_good_behavior

COMMAND="''"
BEHAVIOR=": Command not found."
check_good_behavior

COMMAND="``"
check_diff ${SBASH}

COMMAND="()"
check_diff ${SBASH}

COMMAND="{}"
BEHAVIOR="{}: Command not found."
check_good_behavior

COMMAND="[]"
BEHAVIOR="[]: Command not found."
check_good_behavior

COMMAND="echo \"\SALUT\""
check_diff ${SHBASH}

printf "\n"

#===TESTS GLOBING===#
printf "globing: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="echo {/*,./*}"
check_diff ${SHBASH}

COMMAND="echo \* \[ \\"
check_diff ${SHBASH}

COMMAND="{} []"
BEHAVIOR="{}: Command not found."
check_good_behavior

COMMAND='setenv E ./\*; echo $E'
check_diff ${SHCSH}

COMMAND='setenv E "./*"; echo $E'
check_diff ${SHCSH}

COMMAND='/bin/*ls'
check_diff ${SHBASH}

COMMAND='/bin/*ash'
check_diff ${SHBASH}

COMMAND='/bin/ech* this is an echo and * test'
check_diff ${SHBASH}

printf "\n"

#===TESTS BACK QUOTES===#
printf "back quotes: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="ls `ls`"
check_diff ${SHBASH}

COMMAND="ls `cd $HOME ; pwd`"
check_diff ${SHBASH}

COMMAND="setenv PWD `pwd` ; echo $PWD"
check_diff ${SHBASH}

printf "\n"

#===TESTS SOUS SHELL===#
printf "sous shell: "
if [ $V == 1 ]
then
	printf "\n"
fi

printf "\n"

#===TESTS sur l'entrée du shell===#
printf "sur entrée du shell: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="ls << salut | ./42sh "
check_diff ${SHBASH}

COMMAND="cat -e << salut | ./42sh"
check_diff ${SHBASH}

COMMAND="cat -e << salut\nplop \n\n | ./42sh"
check_diff ${SHBASH}

COMMAND="cat -e << salut\nplop\n salut\nsalut\nls | ./42sh"
check_diff ${SHBASH}

printf "\n"

#===TESTS en vrac===#
printf "en vrac: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND=" rm nosuchfile 2>&-"
check_diff ${SHBASH}

COMMAND=" rm nosuchfile 2>&1 | cat -e "
check_diff ${SHBASH}

COMMAND=" echo \"No dollar character\" 1>&2 | cat -e"
check_diff ${SHBASH}

COMMAND="  ls > file | cat -e ; cat file"
check_diff ${SHBASH}

COMMAND="   ls > out | echo HELLO"
check_diff ${SHBASH}

COMMAND="   ls > out | echo HELLO ; cat out"
check_diff ${SHBASH}

#race condition
COMMAND="ls > file | cat < file"
check_diff ${SHBASH}

COMMAND="ls > file | cat < file ; cat file"
check_diff ${SHBASH}

COMMAND=" echo \ABCDEFGHIJKLMNOPQRSTUVWXYZ"
check_diff ${SHBASH}

COMMAND="echo $PWD > pop ; cat pop"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 fake > lolo 2>&1"
check_diff ${SHBASH}

echo "Fabrice,18 / 20,Excellent travail
Mathieu,3 / 20,Nul comme d'hab
Sophie,14 / 20,En nette progression
Mélanie,9 / 20,Allez presque la moyenne !
Corentin,11 / 20,Pas mal mais peut mieux faire
Albert,20 / 20,Toujours parfait
Benoît,5 / 20,En grave chute" > notes.csv

COMMAND="cat < notes.csv"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 notes.csv"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 notes.csv > eleves.txt;cat eleves.txt"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 fichier_inexistant.csv > eleves.txt"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 fichier_inexistant.csv > eleves.txt 2> erreurs.log ; cat  erreurs.log"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 fichier_inexistant.csv > eleves.txt 2>&1 ; cat eleves.txt"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 notes.csv | sort"
check_diff ${SHBASH}

COMMAND="cut -d , -f 1 notes.csv | sort > noms_tries.txt;cat noms_tries.txt "
check_diff ${SHBASH}

COMMAND="< t t"
BEHAVIOR="Invalid command."
check_good_behavior

COMMAND=">"
BEHAVIOR="Invalid command."
check_good_behavior

COMMAND="<< t t"
BEHAVIOR="Invalid command."
check_good_behavior

COMMAND="<"
BEHAVIOR="Invalid command."
check_good_behavior

COMMAND="ls \?"
check_diff ${SHBASH}

printf "\n\n"

echo "Nombre total de tests = " $COUNTER
echo "Nombre de tests qui fail = " $FAIL
SUCCESS=$((COUNTER - FAIL))
echo "Nombre de tests OK = " $SUCCESS

#===CLEAN===#
chmod 777 test_noperm_dir
rm -rf test_noperm_dir
rm -rf test_dir
rm test_reg_file
rm tmp tmp2 tmp3
rm notes.csv eleves.txt file erreurs.log lolo out pop noms_tries.txt
rm -rf YO mkdir test
