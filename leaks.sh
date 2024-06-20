#!/bin/bash

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

make re
rm valout.txt

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | /___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____\ | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

function run_test()
{
    printf "$CYAN \"$@\" $RESET"
    echo >> valout.txt 2>&1
    echo $@>> valout.txt 2>&1
    printf $BOLDRED"Your output : \n" "-----------------------------------------"
	valgrind --suppressions=valgrind_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --malloc-fill=0x41 --free-fill=0x42 --track-fds=yes --malloc-fill=0x41 --free-fill=0x42 ./minishell -c "$@" >> valout.txt 2>&1
    printf $BOLDRED"Your output : \n" "-----------------------------------------"
    echo >> valout.txt 2>&1
	sleep 0.1
}

# SYNTAX
run_test "|"
run_test "| echo oi"
run_test "| |"
run_test "| $"
run_test "| >"
run_test ">"
run_test ">>"
run_test ">>>"
run_test "<"
run_test "<<"
run_test "echo hi <"
run_test "cat <| ls"
run_test "echo hi | >"
run_test "echo hi | > >>"
run_test "echo hi | < |"
run_test "echo hi | |"
run_test "echo hi | "|""

# ECHO TESTS
run_test 'echo test tout'
run_test 'echo test      tout'
run_test 'echo -n test tout'
run_test 'echo -n -n -n test tout'


# CD TESTS
run_test 'cd .. | pwd'
run_test 'cd /Users | pwd'
run_test 'cd | pwd'
run_test 'mkdir test_dir | cd test_dir | rm -rf ../test_dir | cd . | pwd | cd . | pwd | cd .. | pwd'


# PIPE TESTS
run_test 'cat tests/lorem.txt | grep arcu | cat -e'
run_test 'echo test | cat -e|cat -e'
run_test 'cat /dev/random | head -c 100 | wc -c'
run_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
run_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# # ENV EXPANSIONS + ESCAPE
run_test 'echo test     \    test'
run_test 'echo \"test'
run_test 'echo $TEST'
run_test 'echo "$TEST"'
run_test "echo '$TEST'"
run_test 'echo "$TEST$TEST$TEST"'
run_test 'echo "$TEST$TEST=lol$TEST"'
run_test 'echo "   $TEST lol $TEST"'
run_test 'echo $TEST$TEST$TEST'
run_test 'echo $TEST$TEST=lol$TEST""lol'
run_test 'echo    $TEST lol $TEST'
run_test 'echo test "" test "" test'
run_test 'echo "\$TEST"'
run_test 'echo "$=TEST"'
run_test 'echo "$"'
run_test 'echo "$?TEST"'
run_test 'echo $TEST $TEST'
run_test 'echo "$1TEST"'
run_test 'echo "$T1TEST"'

# ENV EXPANSIONS
# ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
# EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
# run_test 'export ='
# run_test 'export 1TEST= |' $ENV_SHOW
# run_test 'export TEST |' $EXPORT_SHOW
# run_test 'export ""="" | ' $ENV_SHOW
# run_test 'export TES=T="" |' $ENV_SHOW
# run_test 'export TE+S=T="" |' $ENV_SHOW
# run_test 'export TEST=LOL | echo $TEST |' $ENV_SHOW
# run_test 'export TEST=LOL | echo $TEST$TEST$TEST=lol$TEST'
# run_test 'export TEST=LOL| export TEST+=LOL | echo $TEST |' $ENV_SHOW
run_test "env | sort | grep -v SHLVL | grep -v _="
run_test "export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
# run_test 'export TEST="ls       -l     - a" | echo $TEST | $LS | ' $ENV_SHOW

# REDIRECTIONS
run_test 'echo test > ls | cat ls'
run_test 'echo test > ls >> ls >> ls | echo test >> ls| cat ls'
run_test '> lol echo test lol| cat lol'
run_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test| cat test'
run_test 'cat < ls'
run_test 'cat < ls > ls'

# MULTI TESTS
run_test 'echo testing multi | echo "test 1 | | and 2" | cat tests/lorem.txt | grep Lorem'

# SYNTAX ERROR
run_test '|| test'
run_test '| test'
run_test 'echo > <'
run_test 'echo | |'
run_test '<'

# EXIT
run_test "exit 42"
run_test "exit 42 53 68"
run_test "exit 259"
run_test "exit 9223372036854775807"
run_test "exit -9223372036854775808"
run_test "exit 9223372036854775808"
run_test "exit -9223372036854775810"
run_test "exit -4"
run_test "exit wrong"
run_test "exit wrong_command"
run_test "gdagadgag"
run_test "ls -Z"
run_test "cd gdhahahad"
run_test "ls -la | wtf"

run_test "echo hello world"
run_test "echo 'hello world'"
run_test "echo hello'world'"
run_test "echo hello""world"
run_test "echo ''"
run_test "echo "$PWD""
run_test "echo '$PWD'"
# run_test "echo "aspas ->'""
# run_test "echo "aspas -> ' ""
# run_test "echo 'aspas ->"'"
# run_test "echo 'aspas -> " '"
# run_test "echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<""
run_test "echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'"
run_test "echo "exit_code ->$? user ->$USER home -> $HOME""
run_test "echo 'exit_code ->$? user ->$USER home -> $HOME'"
run_test "echo "$""
run_test "echo '$'"
run_test "echo $"
run_test "echo $?"
run_test "echo $?HELLO"

run_test "echo $ '1234var'"

run_test "echo hello$1world"
run_test "echo $"$var""
run_test "echo $'1234var'"
run_test "echo $eli hello$eli"
run_test "echo $1"
run_test "echo $2"
run_test "echo $3"
run_test "echo $4"
run_test "echo $5"
run_test "echo $6"
run_test "echo $7"
run_test "echo $8"
run_test "echo $9"
run_test "echo "hello '$USER' world""
run_test "echo "a$H b""
run_test "echo $USER 'hello "$USER" world' $USER"


run_test "PWD"
run_test "pwd"
run_test "pwd oi"

run_test "var=hello"
run_test ""var"="123""
run_test "var=hello"world$test""
run_test "var=hello"world $test""
run_test "var='helloworld'"
run_test "var=wefdsaf'hello'"
run_test "var="12345"678"
run_test "var="hello""
run_test "var=$"$var""
run_test "var=$"var""
run_test "var="$VAR""
run_test "var=$HOME"
run_test "var="hello world""
run_test "var='hello world'"
run_test "var='hello world' A"

run_test "var=hello world=hello"
run_test "var= 12345"

run_test "export"
run_test "export var1 var2 var3"
run_test "export hello"
run_test "export HELLO=123"
run_test "export HELLO=123 A"
run_test "export HELLO-=123"
run_test "export HELLO="123 A-""
run_test "export HELLO="214321""$HOME"'1231234214' var="2asdfwefasf""$PWD""
run_test "export A-"
run_test "export hello world"
run_test "export ="
run_test "export 123"

run_test "cd $PWD"
run_test "cd $PWD hi "
# run_test "cd ./"test folder""
run_test "cd 123123"

run_test "unset"
# run_test ""unset HELLO""
run_test "unset HELLO1 HELLO2"
run_test "unset HOME"
run_test "unset PATH"
run_test "unset SHELL"

run_test "exit 123"
run_test "exit 298"
run_test "exit +100"
run_test "exit "+100""
run_test "exit +"100""
run_test "exit -100"
run_test "exit "-100""
run_test "exit -"100""
run_test "exit hello"
run_test "exit 42 world"

run_test "grep hi <./test_files/infile"
run_test "grep hi "<infile" < ./test_files/infile"
run_test "echo hi < ./test_files/infile bye bye"
run_test "grep hi <./test_files/infile_big <./test_files/infile"
run_test "echo <"./test_files/infile" "bonjour 42""
run_test "cat <"./test_files/file name with spaces""
run_test "cat <./test_files/infile_big ./test_files/infile"
run_test "cat <"1""2""3""4""5""
run_test "echo <"./test_files/infile" <missing <"./test_files/infile""
run_test "echo <missing <"./test_files/infile" <missing"
run_test "cat <"./test_files/infile""
run_test "echo <"./test_files/infile_big" | cat <"./test_files/infile""
run_test "echo <"./test_files/infile_big" | cat "./test_files/infile""
run_test "echo <"./test_files/infile_big" | echo <"./test_files/infile""
run_test "echo hi | cat <"./test_files/infile""
run_test "echo hi | cat "./test_files/infile""
run_test "cat <"./test_files/infile" | echo hi"
run_test "cat <"./test_files/infile" | grep hello"
run_test "cat <"./test_files/infile_big" | echo hi"
run_test "cat <missing"
run_test "cat <missing | cat"
run_test "cat <missing | echo oi"
run_test "cat <missing | cat <"./test_files/infile""
run_test "echo <123 <456 hi | echo 42"
run_test "ls >./outfiles/outfile01"
run_test "ls > ./outfiles/outfile01"
run_test "echo hi > ./outfiles/outfile01 bye"
run_test "ls >./outfiles/outfile01 >./outfiles/outfile02"
run_test "ls >./outfiles/outfile01 >./test_files/invalid_permission"
run_test "ls >"./outfiles/outfile with spaces""
run_test "ls >"./outfiles/outfile""1""2""3""4""5""
run_test "ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02""
run_test "ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission"
run_test "cat <"./test_files/infile" >"./outfiles/outfile01""
run_test "echo hi >./outfiles/outfile01 | echo bye"
run_test "echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye"
run_test "echo hi | echo >./outfiles/outfile01 bye"
run_test "echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02"
run_test "echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02"
run_test "echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye"
run_test "echo hi >./test_files/invalid_permission | echo bye"
run_test "echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
run_test "echo hi | echo bye >./test_files/invalid_permission"
run_test "echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission"
run_test "echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01"
run_test "cat <"./test_files/infile" >./test_files/invalid_permission"
run_test "cat >./test_files/invalid_permission <"./test_files/infile""
run_test "cat <missing >./outfiles/outfile01"
run_test "cat >./outfiles/outfile01 <missing"
run_test "cat <missing >./test_files/invalid_permission"
run_test "cat >./test_files/invalid_permission <missing"
run_test "cat >./outfiles/outfile01 <missing >./test_files/invalid_permission"
run_test "ls >>./outfiles/outfile01"
run_test "ls >> ./outfiles/outfile01"
run_test "ls >>./outfiles/outfile01 >./outfiles/outfile01"
run_test "ls >./outfiles/outfile01 >>./outfiles/outfile01"
run_test "ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02"
run_test "ls >>./outfiles/outfile01 >>./outfiles/outfile02"
run_test "ls >>./test_files/invalid_permission"
run_test "ls >>./test_files/invalid_permission >>./outfiles/outfile01"
run_test "ls >>./outfiles/outfile01 >>./test_files/invalid_permission"
run_test "ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02"
run_test "ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02"
run_test "ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing"
run_test "echo hi >>./outfiles/outfile01 | echo bye"
run_test "echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye"
run_test "echo hi | echo >>./outfiles/outfile01 bye"
run_test "echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02"
run_test "echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02"
run_test "echo hi >>./test_files/invalid_permission | echo bye"
run_test "echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye"
run_test "echo hi | echo bye >>./test_files/invalid_permission"
run_test "echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission"
run_test "cat <minishell.h>./outfiles/outfile"
run_test "cat <minishell.h|ls"



rm lol ls test
