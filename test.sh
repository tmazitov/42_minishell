#!/bin/bash

MINISHELL=./minishell

TEST_CASES=./testcases.sh

MINISHELL_OUTPUT=./minishell_output.tmp
BASH_OUTPUT=./bash_output.tmp
VALGRIND_OUTPUT_DIR=./valgrind_outputs

mkdir -p $VALGRIND_OUTPUT_DIR

rm -rf $MINISHELL_OUTPUT
rm -rf $BASH_OUTPUT

run_test()
{
    echo "run command"
    local test_command=$1
    local test_case_name=$2
    local valgrind_output_file=$VALGRIND_OUTPUT_DIR/valgrind_$test_case_name.out

    $MINISHELL -c "$test_command" > $MINISHELL_OUTPUT 2>&1

    bash -c "$test_command" > $BASH_OUTPUT 2>&1

    valgrind --suppressions=valgrind_leaks_ignore.txt --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes --malloc-fill=0x41 --free-fill=0x42 --track-fds=yes --malloc-fill=0x41 --free-fill=0x42 $MINISHELL -c "$test_command" > /dev/null 2> $valgrind_output_file

    if diff -q $MINISHELL_OUTPUT $BASH_OUTPUT && [ ! -s $valgrind_output_file ]; then
        echo "[PASS] $test_command"

        rm -rf $valgrind_output_file
    else
        echo "[FAIL] $test_command"
        echo "Expected (bash output):"
        cat $BASH_OUTPUT
        echo "Got (minishell output):"
        cat $MINISHELL_OUTPUT

        if [ -s $valgrind_output_file ]; then
            echo "valgrind error (see $valgrind_output_file):"
            cat $valgrind_output_file
        fi
    fi
}

test_case_count=1

while read -r test_command; do
    (printf %s $test_command)
    if [[ -n "$test_command" && "$test_command" != \#* ]]; then
        # Generate a unique name for each test case
        test_case_name=$(printf "%03d" $test_case_counter)
        run_test "$test_command" "$test_case_name"
        # Increment the test case counter
        test_case_counter=$((test_case_counter + 1))
    fi
done < "$TEST_CASES"

rm -f $MINISHELL_OUTPUT $BASH_OUTPUT