valgrind --suppressions=valgrind_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --malloc-fil=0x41 --free-fill=0x42 --track-fds=yes --malloc-fill=0x41 --free-fill=0x42 ./minishell\