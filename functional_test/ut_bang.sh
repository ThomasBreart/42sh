# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"
source "$ft_directory/ut_tools.sh"

pr_blue "<=============>\n"
pr_blue "    Pareser    \n"
pr_blue "<=============>\n"
pr_blue "ref: $ref_exe\n\n"


ut_ref "ls toto 2>&- 1>&-\n!" $mode;

ut_ref "ls toto 2>&- 1>&-\n!!" $mode;

ut_ref "ls toto 2>&- 1>&-\n!$:p" $mode;

ut_ref "ls toto 2>&- 1>&-\n!!:p" $mode;

ut_ref "history -c\n echo toto >&-\nls >&-\n pwd >&-\n !13:p" $mode;

ut_ref_spe "history --save /tmp/old_histo; history -c\nls >&-\ntmp >&-\n!!history --load /tmp/old_histo" "history -c\nls >&-\ntmp >&-\n!!" $mode;
rm /tmp/old_histo



echo "\n"
