# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"

source "$ft_directory/ut_tools.sh"

pr_blue "<=====================>\n"
pr_blue "env | setenv | unsetenv\n"
pr_blue "<=====================>\n"
pr_blue "ref: $ref_exe\n\n"

ut_no_ref "setenv PATH \"\"; env | /usr/bin/grep -E '^PATH='" "PATH=" $mode;

ut_no_ref "unsetenv PATH; env | /usr/bin/grep -E '^PATH='" "" $mode;

ut_no_ref "setenv TOTO PROUT; env | /usr/bin/grep -E '^TOTO='" "TOTO=PROUT" $mode;

ut_no_ref "setenv TOTO PROUT; unsetenv TOTO; env | /usr/bin/grep -E '^TOTO='" "" $mode;

ut_no_ref "unsetenv DONT_EXIST" "" $mode;

ut_ref "env -i PATH=$PATH env" $mode;

ut_ref "env -i PATH=$PATH ls" $mode;

ut_no_ref "env -i -u PATH ls" "42sh: not a command :ls" $mode;

echo "\n"
