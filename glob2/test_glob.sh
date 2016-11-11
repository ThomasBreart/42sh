#!/bin/bash
#Bin_name
bin=binairy
n=1
libft=libft
make -C $libft
#Linux compil gcc -g -I. deps.c glob_listing.c glob.c glob_match.c main_glob.c ../command/libft/libft.a -Wall -Wextra -o binairy
gcc -g -I. deps.c glob_listing.c glob.c glob_braces.c glob_brace2.c glob_match.c main_glob.c $libft/libft.a -Wall -Wextra -o $bin

## Creer un nouveau test
#
#	launch_test(arg1, arg2, ret)
#
# arg1 : chaine a matcher
# arg2 : chaine glob
# ret : 1 - dois matcher
#       0 - ne dois pas matcher
##

function test_it()
{
	if [ $# == 2 ]
	then
		echo "==========> test $n" >> o1
		echo $2 >> o1

		echo "==========> test $n" >> o2
		./$bin $1 >> o2

		if [ $? -eq 1 ]
		then
			diff o1 o2 >> out
			if [ $? -eq 0 ]
			then
				echo -e '\033[0;32m'"TEST $n OK" '\033[0m'
			else
				echo -e '\033[0;31m'"TEST $n FAIL: ret = $?, args = $1, $2" '\033[0m'
			fi
		else
			echo -e '\033[0;31m'"TEST binairy $n FAIL: ret = $?, args = $1, $2" '\033[0m'
		fi

	else
		echo "Bad args"
	fi
	n=$((n+1))
}

test_it "*" "*"
