# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"

source "$ft_directory/ut_tools.sh"

pr_blue "<=============>\n"
pr_blue "       CD      \n"
pr_blue "<=============>\n"
pr_blue "ref: $ref_exe\n\n"


ut_ref "cd /tmp ; pwd" $mode;

ut_ref "cd -P /tmp ; pwd" $mode;

ut_ref "cd -L /tmp ; pwd" $mode;

ut_ref "cd /tmp ; mkdir test 2>&- && cd test && rm -rf ../test && cd -" $mode;

ut_ref "cd -P /tmp ; mkdir test && cd test && pwd && rm -rf ../test" $mode;

ut_ref "cd -P /tmp ; mkdir test && cd -L test && pwd && rm -rf ../test" $mode;

ut_ref "cd -P /tmp ; mkdir test && cd -L test && pwd && rm -rf ../test" $mode;

ut_no_ref "cd /tmp ; unsetenv OLDPWD; cd -" "OLDPWD not set" $mode;

ut_no_ref "cd -P /tmp ; unsetenv OLDPWD PWD; cd -" "OLDPWD not set" $mode;

ut_no_ref "cd -P akajshdgkajhgka" "akajshdgkajhgka: No such file or directory." $mode;

ut_no_ref "cd -L akajshdgkajhgka" "akajshdgkajhgka: No such file or directory." $mode;

ut_no_ref "cd /tmp; mkdir -p test; cd test; pwd; cd ..; rm -r test" "/tmp/test" $mode;


echo "\n"
