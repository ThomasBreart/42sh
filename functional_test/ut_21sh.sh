
# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"
source "$ft_directory/ut_tools.sh"

pr_blue "<=============>\n\n"
pr_blue "correction 21sh\n\n"
pr_blue "<=============>\n\n"

pr_blue "ELIMINATOIRE\n"

ut_no_ref "foo" "foo: Command not found.";

ut_ref "/bin/ls";

ut_ref "/bin/ls -laF";

ut_ref "/bin/ls -l -a -F";

pr_blue "\n\nCD\n"

ut_ref "echo \"It works!\"";

#adapted to 21sh cd
ut_ref_spe "cd /tmp; pwd" "cd /tmp; pwd";

#adapted to 21sh cd
ut_ref_spe "cd /tmp; /bin/pwd" "cd /tmp; /bin/pwd";

#adapted to 21sh cd
ut_ref_spe "cd ; /bin/pwd" "echo $HOME";

#adapted to 21sh cd
ut_ref_spe "cd /tmp; cd -; /bin/pwd" "cd /tmp; cd -; /bin/pwd";

pr_blue "\n\nEnvironnement\n"

ut_eye "env";

ut_ref_spe "setenv FOO bar; env | grep FOO" "echo \"FOO=bar\"";

ut_ref_spe "setenv FOO bar;unsetenv FOO; env | grep FOO" "echo \"\"";

ut_ref_spe "setenv FOO bar;unsetenv FOO;unsetenv FOO; env | grep FOO" "echo \"\"";

pr_blue "\n\nGestion du Path\n"

ut_no_ref "unsetenv GOPATH ; unsetenv PATH; env | /usr/bin/grep -E 'PATH='" "";

ut_ref_spe " unsetenv GOPATH ;unsetenv PATH; setenv PATH \"/bin:/usr/bin\" ; ls" "ls";

ut_no_ref "unsetenv PATH; ls" "ls: Command not found.";

ut_ref_spe "unsetenv PATH; /bin/ls" "ls";

pr_blue "\n\nLigne de command\n"

ut_no_ref "" "";

ut_no_ref " " "";

ut_no_ref "        " "";

ut_ref_spe "        ls       " "ls";

pr_blue "\n\nSignal: Human required\n"

pr_blue "\n\nPipe\n"

ut_ref "ls | cat -e";

ut_ref "ls | sort | cat -e";

ut_no_ref "base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g'" "       No"

pr_blue "\n\nRedirection\n"

rm -r /tmp/test

ut_no_ref "cd /tmp; mkdir -p test; cd test; echo \"Testing redirections,\" > test.txt; cat test.txt" "Testing redirections,"

ut_ref_spe "cd /tmp; mkdir -p test; cd test; echo \"with multiple lines\" >> test.txt; cat test.txt" "echo \"Testing redirections,\nwith multiple lines\""

ut_no_ref "wc -c < /tmp/test/test.txt" "      42"

ut_no_ref "cat -e << EOF
Roses are red\nViolets are blue\nAll my base are belong to you\nAnd so are you\nEOF" "Roses are red$
Violets are blue$
All my base are belong to you$
And so are you$"

ut_no_ref "cat -e << EOF >> /tmp/test/test.txt\nRoses are red\nViolets are blue\nAll my base are belong to you\nAnd so are you\nEOF\ncat /tmp/test/test.txt" "Testing redirections,
with multiple lines
Roses are red$
Violets are blue$
All my base are belong to you$
And so are you$"

pr_blue "\n\nPlusieurs commandes de suite\n"

ut_ref "ls -1; touch filethatcannotexistbecauseisay; ls -1 ; rm filethatcannotexistbecauseisay"

pr_blue "\n\nUn peu de tout\n"

ut_ref "cd /tmp; mkdir -p test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat -e fifi ; rm -f fifi"
rm -r /tmp/test

ut_ref_spe "cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd - > /dev/null ; echo \"I prefer turnips anyway\" >> /tmp/better_poem; cat /tmp/better_poem\nRoses are red\nViolets are blue\nAll my base are belong to you\nI love you\nEOF" "echo \"All my bases are belong to you$\nI love you$\nTurnips are red$\nViolets are blue$\nI prefer turnips anyway\""

pr_blue "\n\nAggrégation des descripteurs de fichiers\n"

ut_no_ref "rm nosuchfileicantellyoubecauseimadesureof 2>&-" ""

ut_no_ref "rm nosuchfileicantellyoubecauseimadesureof 2>&1 | cat -e" "rm: nosuchfileicantellyoubecauseimadesureof: No such file or directory$"

ut_no_ref "echo \"No dollar character\" 1>&2 | cat -e" "No dollar character"

pr_blue "\n\nLe Reste Se Fait A La Main\n"

echo ""
