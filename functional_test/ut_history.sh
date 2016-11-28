# ft_directory="/tmp/42sh_FunTe"
ft_directory="/Users/mfamilar/work/GROUP/42sh/functional_test"

source "$ft_directory/ut_tools.sh"

# 42sh historic
hist_42_file="/tmp/.42_history"
p_42_hist="cat $hist_42_file"
# bash historic
hist_bash_file="/Users/$(whoami)/.bash_history"
p_bash_hist="cat $hist_bash_file"
#test result location
test_repository="/tmp/42sh_functionnal_test"
test_file="$test_repository/test_history.txt"

pr_blue "<=============>\n"
pr_blue "    HISTORY    \n"
pr_blue "<=============>\n"

#../docs/switch_gnl.sh 1 ../docs
rm -r /tmp/old.txt $test_repository $test_file

mkdir -p $test_repository
cat $hist_42_file > /tmp/old.txt

echo "\nhistory"
printf "" > $hist_42_file
ut_no_ref "ls > /dev/null\necho toto > /dev/null\nhistory" "    1  ls > /dev/null
    2  echo toto > /dev/null
    3  history" $mode;

# (-)n
echo "\nhistory (-)n"
printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "history 2" "    3  pwd
    4  history 2" $mode;

printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "history 20" "    1  ls
    2  echo toto
    3  pwd
    4  history 20" $mode;

printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "history -1" "42sh: history: -1: invalid option" $mode;

printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "history -100" "42sh: history: -100: invalid option" $mode;

printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "history 0" "" $mode;

# -d
echo "\nhistory -d"
printf "ls\n" > $hist_42_file
printf "ls\n" > $hist_bash_file
ut_ref "history -d 1" $mode;

printf "ls\n" > $hist_42_file
printf "ls\n" > $hist_bash_file
ut_no_ref "history -d -12" "42sh: history: -12: history position out of range" $mode;

printf "ls\n" > $hist_42_file
printf "ls\n" > $hist_bash_file
ut_no_ref "history -d 100" "42sh: history: 100: history position out of range" $mode;

# -c
echo "\nhistory -c"
printf "ls\necho toto\npwd\n" > $hist_42_file
printf "ls\necho toto\npwd\n" > $hist_bash_file
ut_no_ref "ls > /dev/null\nhistory -c;history" "" $mode;

# -p
echo "\nhistory -p"
printf "" > $hist_42_file
ut_ref "history -p echo ~ /tmp toto" $mode;

printf "" > $hist_42_file
ut_ref "history -p" $mode;

printf "" > $hist_42_file
ut_ref "history -p asdasdasd" $mode;

# -s
echo "\nhistory -s"
printf "" > $hist_42_file
printf "" > $hist_bash_file
ut_ref "history -s echo ~ /tmp toto; history" $mode;

# -a
echo "\nhistory -a"
printf "" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -a\n$p_42_hist" "ls > /dev/null
history -a" $mode;

printf "" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -a $test_file\ncat $test_file" "ls > /dev/null
history -a $test_file" $mode;

printf "" > $hist_42_file
printf "pwd\nls\n" > $test_file
ut_no_ref "ls > /dev/null\nhistory -a $test_file\ncat $test_file" "pwd
ls
ls > /dev/null
history -a $test_file" $mode;
rm $test_file

# -w
echo "\nhistory -w"
printf "pwd\necho coucou\n" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -w\n$p_42_hist" "pwd
echo coucou
ls > /dev/null
history -w" $mode;

printf "pwd\necho coucou\n" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -w\n$p_42_hist\npwd > /dev/null\necho eHOh > /dev/null\nhistory -w\n$p_42_hist" "pwd
echo coucou
ls > /dev/null
history -w
pwd
echo coucou
ls > /dev/null
history -w
$p_42_hist
pwd > /dev/null
echo eHOh > /dev/null
history -w" $mode;

printf "" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -w $test_file\ncat $test_file" "ls > /dev/null
history -w $test_file" $mode;

printf "" > $hist_42_file
printf "pwd\nls\n" > $test_file
ut_no_ref "echo truc > /dev/null\necho \"ls /tmp\npwd\n\" >> $hist_42_file\nhistory -w $test_file\ncat $test_file" "echo truc > /dev/null
echo \"ls /tmp
pwd
\" >> $hist_42_file
history -w $test_file" $mode;

rm -r $test_repository
mkdir -p $test_repository
#make re -C $PATH_TO_EXE > /dev/null
# -r
echo "\nhistory -r"
printf "pwd\necho coucou\n" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory\nhistory -r\nls > /dev/null\nhistory" "    1  pwd
    2  echo coucou
    3  ls > /dev/null
    4  history
    1  pwd
    2  echo coucou
    3  ls > /dev/null
    4  history
    5  history -r
    6  ls > /dev/null
    7  history" $mode;

printf "pwd\necho coucou\n" > $hist_42_file
ut_no_ref "ls > /dev/null\nhistory -r\nhistory\npwd > /dev/null\necho eHOh > /dev/null\necho \"echo toto\nls\" >> $hist_42_file\nhistory -r\nhistory" "    1  pwd
    2  echo coucou
    3  ls > /dev/null
    4  history -r
    5  history
     1  pwd
     2  echo coucou
     3  ls > /dev/null
     4  history -r
     5  history
     6  pwd > /dev/null
     7  echo eHOh > /dev/null
     8  echo \"echo toto
ls\" >> /tmp/.42_history
     9  history -r
    10  echo toto
    11  ls
    12  history" $mode;

printf "" > $hist_42_file
printf "ls\n" > $test_file
ut_no_ref "history -r $test_file\nhistory" "    1  history -r $test_file
    2  ls
    3  history" $mode;

printf "ls\npwd\n" > $hist_42_file
printf "pwd\nls\n" > $test_file
ut_no_ref "history -r $test_file\nhistory\npwd >/dev/null\nwhoami >/dev/null\necho \"echo toto\nls\" >> $test_file\nhistory -r $test_file\nhistory" "    1  ls
    2  pwd
    3  history -r $test_file
    4  history
     1  ls
     2  pwd
     3  history -r $test_file
     4  history
     5  pwd >/dev/null
     6  whoami >/dev/null
     7  echo \"echo toto
ls\" >> $test_file
     8  history -r $test_file
     9  echo toto
    10  ls
    11  history" $mode;


echo "\n"

cat /tmp/old.txt > $hist_42_file
rm -r /tmp/old.txt $test_repository
#../docs/switch_gnl.sh 0 ../docs
#make re -C $PATH_TO_EXE > /dev/null
