ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"
source "$ft_directory/ut_tools.sh"

pr_blue "<=============>\n"
pr_blue "      ECHO     \n"
pr_blue "<=============>\n"
pr_blue "ref: $ref_exe\n\n"


ut_ref "echo \"\" | cat -e" $mode;

ut_ref "echo \"toto\" | cat -e" $mode;

ut_ref "echo \"toto\" tata | cat -e" $mode;

ut_ref "echo \"toto\" tata \"asd asd asd as da sd asd asd q \" | cat -e" $mode;

ut_ref "echo \"toto\" tata | cat -e" $mode;

ut_ref "echo \"toto\" tata | cat -e" $mode;

echo "\n"
