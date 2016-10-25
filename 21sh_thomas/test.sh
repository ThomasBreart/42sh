#!/bin/sh

#=== Modification à faire dans le main ===#
# 	//	if (termcaps->istty == 1)
#	// 			ret = get_command(termcaps, &entry);
#				get_next_line(0, &entry);

SHBASH=/bin/bash
SHCSH=/bin/csh
SH=./21sh
OUT=tmp
OUTB=tmp2
V=0
COMMAND=""
BEHAVIOR=""

check_diff() {
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
	fi
	if [ $V = 1 ]
	then
		printf "  $COMMAND\n"
	fi
}

check_good_behavior() {
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
printf "Basic tests: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="ls"
check_diff ${SHCSH}

COMMAND="mkdir \"Salut ca va ?\""
COMMAND="mkdir \"YOO\""

COMMAND="ls"
check_diff ${SHCSH}

COMMAND="rm -rf  \"Salut ca va ?\""
COMMAND="rm -rf  \"YOO\""


COMMAND="pwd"
check_diff ${SHCSH}

COMMAND="ls -ar"
check_diff ${SHCSH}

COMMAND="ls -la -z"
check_diff ${SHCSH}

COMMAND="/bin/ls"
check_diff ${SHCSH}

COMMAND="/bin/ls -ar"
check_diff ${SHCSH}

COMMAND="ls ~"
check_diff ${SHCSH}

COMMAND="invalid_command"
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
#exit
COMMAND="echo -n -n -n -n -n -nnnn -n -n -- tata"
check_diff ${SHBASH}

COMMAND="echo \"$?\""
check_diff ${SHCSH}

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

printf "\n"

#===TESTS BUILTIN CD===#
printf "builtin_cd: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="cd a b c"
check_diff ${SHCSH}

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
check_diff ${SHCSH}

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

COMMAND="unsetenv PWD ; cd .. ;echo \$OLDPWD"
BEHAVIOR=""
check_good_behavior

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

COMMAND="cd /../../../../../../ ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd ../../../../../../../../../ ; echo \$PWD; echo \$OLDPWD"
check_diff ${SHBASH}

COMMAND="cd -p"
check_diff ${SHBASH}

#printf "\033[1;31;33m?\033[0m"
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

COMMAND="setenv coucou=truc USER=truc truc=bidule"
check_diff ${SHCSH}

COMMAND="setenv coucou=\"test\""
check_diff ${SHCSH}

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

COMMAND="env -i pwd"
BEHAVIOR="pwd: Command not found."
check_good_behavior

COMMAND="env -i PWD=plop pwd"
BEHAVIOR="pwd: Command not found."
check_good_behavior

COMMAND="env -i a=apwd ls"
BEHAVIOR="ls: Command not found."
check_good_behavior

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
BEHAVIOR="pwd: Command not found."
check_good_behavior

COMMAND="env -i -u PWD PWD=plop pwd"
BEHAVIOR="pwd: Command not found."
check_good_behavior

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
BEHAVIOR="qwerty: Command not found."
check_good_behavior

COMMAND="env -i PATH=/bin pwd"
check_diff ${SHCSH}
# ENV
# env a=a b=b
# env PWD=plop
# env -u -i
# env -u -i PWD=a pwd
# env -u -z
printf "\n"
#===TESTS BUILTIN EXIT===#
printf "builtin_exit: "
if [ $V == 1 ]
then
	printf "\n"
fi

#COMMAND="exit"
#diff_exit ${SHCSH}


#exit
#EXIT
#exit 42
# exit -1
# exit plop
# exit 123abc456
#exit 123a
#exit EXIT
# exit a b c
printf "\n"

#===TESTS HISTORY===#
printf "builtin_history: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="history"
check_diff ${SHBASH}

COMMAND="history 10"
check_diff ${SHBASH}

COMMAND="history 1"
check_diff ${SHBASH}

COMMAND="history -d 1"
check_diff ${SHBASH}

COMMAND="history"
check_diff ${SHBASH}

COMMAND="history -s YOYOY \"salut ca va $USER\""
check_diff ${SHBASH}

COMMAND="history"
check_diff ${SHBASH}

COMMAND="history -s YOYOY SAlut ca va"
check_diff ${SHBASH}

COMMAND="history"
check_diff ${SHBASH}

COMMAND="history -p YOYOY \"salut ca va $USER\""
check_diff ${SHBASH}

COMMAND="history -p YOYOY SALUT CA VA"
check_diff ${SHBASH}

COMMAND="history -d 10f"
BEHAVIOR="42sh: history: 10f: history position out of range"
check_good_behavior

COMMAND="history -c"
check_diff ${SHBASH}

COMMAND="history"
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

printf "\n"
#===TESTS BONUS METACHARACTERS===#
printf "bonus_metacharacters_\$VAR: "
if [ $V == 1 ]
then
	printf "\n"
fi

COMMAND="echo $"
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

COMMAND="echo \$PWDaa"
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
#===CLEAN===#
chmod 777 test_noperm_dir
rm -rf test_noperm_dir
rm -rf test_dir
rm test_reg_file
rm tmp tmp2 tmp3
