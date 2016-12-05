# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"
source "$ft_directory/ut_tools.sh"

pr_blue "<=====================>\n"
pr_blue "    quotes \"\'\` and \   \n"
pr_blue "<=====================>\n"
pr_blue "ref: $ref_exe\n\n"

ut_ref "echo \" toto \" " $mode;

ut_ref "echo \" \' toto \' \" " $mode;

ut_no_ref "echo \" \' \` toto \` \' \" " " \' \` toto \` \' " $mode;

ut_ref "echo \' toto \' " $mode;

ut_ref "echo \\\` toto \\\` " $mode;

ut_ref "echo \\\" toto \\\" " $mode;

ut_ref "echo \\\' toto \\\' " $mode;

ut_ref "echo \\\\\\ toto " $mode;

ut_ref "echo \"\\ \"toto\\ \"\" tata  " $mode;

ut_ref "echo \\\a " $mode;

ut_ref "echo \\\z " $mode;

ut_ref "echo \\\n " $mode;

ut_ref "echo \\\r " $mode;

ut_ref "echo \\\t " $mode;

ut_ref "echo \"\\t\" " $mode;

echo "\n"
