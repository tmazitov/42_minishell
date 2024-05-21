cc -Wall -Wextra -Werror output_filter_command.c ../../../../libft/libft.a -fsanitize=address
./a.out "ls -a"
./a.out "ls -a > outfile"
./a.out "> outfile ls -a"
./a.out "> outfile ls -a << heredoc"
./a.out "<< heredoc ls -a > outfile"
./a.out "ls -a > outfile << heredoc"
./a.out "> outfile << heredoc ls -a > outfile"
./a.out "> outfile ls -a < infile > outfile"
./a.out " > outfile < infile ls -a < infile > outfile > outfile"
rm -rf ./a.out