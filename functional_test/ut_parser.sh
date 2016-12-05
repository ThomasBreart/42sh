# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"
source "$ft_directory/ut_tools.sh"

pr_blue "<=============>\n"
pr_blue "    Parser    \n"
pr_blue "<=============>\n"
pr_blue "ref: $ref_exe\n\n"


ut_ref "ls \"./\"" $mode;

ut_ref "echo $HOME" $mode;

ut_ref "echo ~~~~~~~~~~~" $mode;

ut_ref "echo \"$HOME\"" $mode;

ut_ref "echo \"\'$HOME\'\"" $mode;

ut_ref "echo \"~\"" $mode;

ut_ref "echo \"~/Desktop\"" $mode;

ut_ref "ls \"~/Desktop\"" $mode;

ut_ref "echo ~/Desktop && ls ~ && echo toto || echo ca chie" $mode;

ut_ref "echo \"$HOME\" tata ~~~ ~/../~ | cat -e" $mode;

echo "\n"
