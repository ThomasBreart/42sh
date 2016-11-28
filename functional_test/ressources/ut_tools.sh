exe=$1/42sh
PATH_TO_EXE="$1"
ref_exe="/bin/bash --posix"

if [ "$1" == "--help" ]; then
    echo "ut_21sh_correction.sh [path to exe] [1 or 2 or leaks or nothing]  [1 or 2 or leaks or nothing]"
    echo "    1 => reduced format"
    echo "    2 => reduced format except error"
    echo "    eoe => exit on error"
    echo "    leaks => use valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all"
    echo "    leak => use valgrind --leak-check=yes --leak-check=full"
    echo "    no_color => print colorless result"
    exit
fi

leaks=""
if [ "$2" == "leaks" ] || [ "$3" == "leaks" ]; then
    leaks="valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all "
elif [ "$2" == "leak" ] || [ "$3" == "leak" ]; then
    leaks="valgrind --leak-check=yes --leak-check=full "
fi

grep_loses=""
if [ "$2" == "grep" ] || [ "$3" == "grep" ]; then
    grep_loses=" | grep lost "
fi

exit_on_error=""
if [ "$2" == "eoe" ] || [ "$3" == "eoe" ] || [ "$4" == "eoe" ]; then
    exit_on_error="exit 1"
fi

color="on"
if [ "$2" == "--nocolor" ] || [ "$3" == "--nocolor" ] || [ "$4" == "--nocolor" ]; then
    color="off"
fi

margin="\t"
DFLT="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
BLUE="$(tput setaf 4)"

function pr_blue() {
    if [ "$color" == "off" ];then
        printf "$1"
    else
        printf "$BLUE""$1""$DFLT"
    fi
}

function pr_green() {
    if [ "$color" == "off" ];then
        printf "$1"
    else
        printf "$GREEN""$1""$DFLT"
    fi
}

function pr_red() {
    if [ "$color" == "off" ];then
        printf "$1"
    else
        printf "$RED""$1""$DFLT"
    fi
}


if [ "$2" == "1" ] || [ "$3" == "1" ]; then
    mode="tiny"
elif [ "$2" == "2" ] || [ "$3" == "2" ]; then
    mode="false"
fi

function ut_result() {
    if [ "$ret" == "$ref" ]; then
        if [ "$mode" == "tiny" ] || [ "$mode" == "false" ]; then
            pr_green "+"
        else
            pr_green "OK";pr_blue " : ";printf "$CMD" ;pr_blue " : ";printf "$ret\n"
        fi
    else
        if [ "$mode" == "tiny" ]; then
            pr_red "-"
        else
            if [ "$mode" == "false" ]; then
                echo "\n"
            fi
            pr_red "NK"; pr_blue " : "
            printf "$CMD \n"
            printf "$margin"; pr_blue "expected: \n"; printf "$ref\n"
            printf "$margin"; pr_blue "returned: \n"; printf "$ret\n"
        fi
        if [ "$exit_on_error" == "exit 1" ]; then
            ../docs/switch_gnl.sh 0 ../docs
            exit 1
        fi
    fi
}

function ut_no_ref() {
    ret="$(echo $1 | $leaks $exe 2>&1 )"
    ref="$2"
    CMD="$1"
    ut_result
}

function ut_ref() {
    ret="$(echo $1 | $leaks $exe 2>&1 )"
    ref="$(echo $1 | $ref_exe 2>&1)"
    CMD="$1"
    ut_result
}

function ut_ref_spe() {
    ret="$(echo $1 | $leaks $exe 2>&1 )"
    ref="$(echo $2 | $ref_exe 2>&1)"
    CMD="$1"
    ut_result
}

function ut_eye() {
    ret="$(echo $1 | $leaks $exe 2>&1 )"
    ref="Human check"
    CMD="$1"
    ut_result
}

echo "tools loaded"