#!/bin/sh

ress=( "ressources/ut_tools.sh"\
	"ut_21sh.sh" "ut_cd.sh"\
	"ut_env.sh" "ut_all.sh"\
	"ut_echo.sh"\
	"ut_history.sh"\
	"ut_parser.sh")

ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"

mkdir -p $ft_directory
for res in "${ress[@]}"; do
	cp $res $ft_directory/
	chmod 777 $res
done
