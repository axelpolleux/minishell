# Comments
-[ ] Remove all your comments
  - //
  - /* */

# Norminette
-[ ] Except 'minichevre', check that all the names used in this project are really english
  - Variables
  - Functions


# Errors

```
minichevre$ cat < out | cat -e
==864047== Memcheck, a memory error detector
==864047== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==864047== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==864047== Command: /usr/bin/cat
==864047== 
==864048== Memcheck, a memory error detector
==864048== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==864048== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==864048== Command: /usr/bin/cat -e
==864048== 
echo coucou$
echo coucou$$
==864047== 
==864047== FILE DESCRIPTORS: 0 open (0 std) at exit.
==864047== 
==864047== HEAP SUMMARY:
==864047==     in use at exit: 0 bytes in 0 blocks
==864047==   total heap usage: 31 allocs, 31 frees, 139,232 bytes allocated
==864047== 
==864047== All heap blocks were freed -- no leaks are possible
==864047== 
==864047== For lists of detected and suppressed errors, rerun with: -s
==864047== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==864048== 
==864048== FILE DESCRIPTORS: 1 open (0 std) at exit.
==864048== Open file descriptor 3: /home/apolleux/CLionProjects/minishell/out
==864048==    <inherited from parent>
==864048== 
==864048== 
==864048== HEAP SUMMARY:
==864048==     in use at exit: 0 bytes in 0 blocks
==864048==   total heap usage: 32 allocs, 32 frees, 798,707 bytes allocated
==864048== 
==864048== All heap blocks were freed -- no leaks are possible
==864048== 
==864048== For lists of detected and suppressed errors, rerun with: -s
==864048== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

# Exit

si overflow des longs, alors
=> ```return (2)```

```
return ((unsigned char)*value*)
```

```
minichevre: exit: too many arguments
minichevre$ echo $?
2
```

```
void	exec_built(t_data *data, t_cmd *cmd)
{
	int	save_in;
	int	save_out;

	save_in = -1;
	save_out = -1;
	if (cmd->input > -1)
	{
		save_in = dup(0);
		dup2(cmd->input, 0);
	}
	if (cmd->output > -1)
	{
		save_out = dup(1);
		dup2(cmd->output, 1);
	}
	built_parent(data, cmd);
	fflush(stdout);
	close_it(save_in, save_out, cmd);
}
```

```
minichevre$ powd
minishell: powd: command not found
==904946== 
==904946== FILE DESCRIPTORS: 3 open (3 std) at exit.
==904946== 
==904946== HEAP SUMMARY:
==904946==     in use at exit: 208,477 bytes in 227 blocks
==904946==   total heap usage: 2,033 allocs, 1,806 frees, 539,713 bytes allocated
==904946== 
==904946== 5 bytes in 1 blocks are indirectly lost in loss record 1 of 68
==904946==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==904946==    by 0x408C02: ft_substr (in /home/apolleux/CLionProjects/minishell/minishell)
==904946==    by 0x406092: token_new (tokeniser_utils.c:41)
==904946==    by 0x405B16: add_word (tokeniser.c:60)
==904946==    by 0x405D1D: tokeniser (tokeniser.c:111)
==904946==    by 0x4083F4: main_parser (main.c:32)
==904946==    by 0x4085AA: main_reading (main.c:71)
==904946==    by 0x40867C: main (main.c:94)
==904946== 
==904946== 37 (32 direct, 5 indirect) bytes in 1 blocks are definitely lost in loss record 15 of 68
==904946==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==904946==    by 0x408A3C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==904946==    by 0x406067: token_new (tokeniser_utils.c:38)
==904946==    by 0x405B16: add_word (tokeniser.c:60)
==904946==    by 0x405D1D: tokeniser (tokeniser.c:111)
==904946==    by 0x4083F4: main_parser (main.c:32)
==904946==    by 0x4085AA: main_reading (main.c:71)
==904946==    by 0x40867C: main (main.c:94)
==904946== 
==904946== LEAK SUMMARY:
==904946==    definitely lost: 32 bytes in 1 blocks
==904946==    indirectly lost: 5 bytes in 1 blocks
==904946==      possibly lost: 0 bytes in 0 blocks
==904946==    still reachable: 0 bytes in 0 blocks
==904946==         suppressed: 208,440 bytes in 225 blocks
==904946== 
==904946== For lists of detected and suppressed errors, rerun with: -s
==904946== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

```
minishell: ./cat: command not found
==919789== 
==919789== FILE DESCRIPTORS: 3 open (3 std) at exit.
==919789== 
==919789== HEAP SUMMARY:
==919789==     in use at exit: 208,183 bytes in 222 blocks
==919789==   total heap usage: 1,018 allocs, 796 frees, 343,164 bytes allocated
==919789== 
==919789== LEAK SUMMARY:
==919789==    definitely lost: 0 bytes in 0 blocks
==919789==    indirectly lost: 0 bytes in 0 blocks
==919789==      possibly lost: 0 bytes in 0 blocks
==919789==    still reachable: 0 bytes in 0 blocks
==919789==         suppressed: 208,183 bytes in 222 blocks
==919789== 
==919789== For lists of detected and suppressed errors, rerun with: -s
==919789== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
minichevre$ unset PATH
minichevre$ ./cat Makefile 
minishell: ./cat: command not found
==921141== 
==921141== FILE DESCRIPTORS: 3 open (3 std) at exit.
==921141== 
==921141== HEAP SUMMARY:
==921141==     in use at exit: 208,183 bytes in 222 blocks
==921141==   total heap usage: 1,166 allocs, 944 frees, 443,691 bytes allocated
==921141== 
==921141== LEAK SUMMARY:
==921141==    definitely lost: 0 bytes in 0 blocks
==921141==    indirectly lost: 0 bytes in 0 blocks
==921141==      possibly lost: 0 bytes in 0 blocks
==921141==    still reachable: 0 bytes in 0 blocks
==921141==         suppressed: 208,183 bytes in 222 blocks
==921141== 
==921141== For lists of detected and suppressed errors, rerun with: -s
==921141== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
minichevre$ echo $?
127
```

```
❯ ./minishell
minichevre$ echo bite > $HOME
minichevre$ ls
'""'	  bios	   check.md	       e	     Makefile	 minishell_tester   src
'=='	  bite	   compile_flags.txt   ft_strlen.c   mewen.txt	 readline.supp	    tkt
'$HOME'   builds   coucou	       includes      minishell	 README.md
```

```
❯ ./minishell
minichevre$ test
minichevre$ test '
minichevre: every quotes must be closed
```

```
minichevre$ echo caca | cat << $PATH
> echo
> ls
> $USER
>
==299910==  ^C
==299910== Process terminating with default action of signal 2 (SIGINT)
==299910==    at 0x490E75B: kill (syscall-template.S:120)
==299910==    by 0x48ABF39: _rl_signal_handler (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48ACBEC: rl_getc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48AC460: rl_read_key (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x4890C86: readline_internal_char (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x4899D14: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x405096: read_heredoc (here_doc_manage.c:86)
==299910==    by 0x4051D8: heredoc_child (here_doc_manage.c:113)
==299910==    by 0x4052C1: init_heredoc (here_doc_manage.c:173)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== FILE DESCRIPTORS: 4 open (3 std) at exit.
==299910== Open file descriptor 4:
==299910==    at 0x49E10FD: pipe (pipe.c:29)
==299910==    by 0x40524F: init_heredoc (here_doc_manage.c:163)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910==
==299910== HEAP SUMMARY:
==299910==     in use at exit: 226,873 bytes in 557 blocks
==299910==   total heap usage: 786 allocs, 229 frees, 242,038 bytes allocated
==299910==
==299910== 5 bytes in 2 blocks are still reachable in loss record 3 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408A52: ft_substr (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x405F92: token_new (tokeniser_utils.c:41)
==299910==    by 0x405B09: add_all (tokeniser.c:83)
==299910==    by 0x405BEE: tokeniser (tokeniser.c:108)
==299910==    by 0x408274: main_parser (main.c:32)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 6 bytes in 1 blocks are still reachable in loss record 4 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40891E: ft_strdup (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x40522B: init_heredoc (here_doc_manage.c:160)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 14 bytes in 3 blocks are still reachable in loss record 14 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40891E: ft_strdup (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x407D42: tok_to_cmd (make_command.c:59)
==299910==    by 0x407E3B: parsing_commands (make_command.c:85)
==299910==    by 0x4082D3: main_parser (main.c:41)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 20 bytes in 4 blocks are still reachable in loss record 19 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408A52: ft_substr (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x405F92: token_new (tokeniser_utils.c:41)
==299910==    by 0x405A16: add_word (tokeniser.c:60)
==299910==    by 0x405C1D: tokeniser (tokeniser.c:111)
==299910==    by 0x408274: main_parser (main.c:32)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 24 bytes in 1 blocks are still reachable in loss record 23 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x48B1BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48A8B1D: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48AAF65: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x4083F4: main_reading (main.c:67)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 24 bytes in 1 blocks are still reachable in loss record 24 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x4079D5: new_redirection (make_cmd_utils.c:78)
==299910==    by 0x407C01: parse_redir (make_command.c:38)
==299910==    by 0x407E89: parsing_commands (make_command.c:88)
==299910==    by 0x4082D3: main_parser (main.c:41)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 25 bytes in 1 blocks are still reachable in loss record 26 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x48B1BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48A8B39: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48AAF65: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x4083F4: main_reading (main.c:67)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 40 bytes in 1 blocks are still reachable in loss record 30 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408B00: ft_strjoin (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x404E03: history_heredoc (here_doc_utils.c:27)
==299910==    by 0x4050C7: read_heredoc (here_doc_manage.c:92)
==299910==    by 0x4051D8: heredoc_child (here_doc_manage.c:113)
==299910==    by 0x4052C1: init_heredoc (here_doc_manage.c:173)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 40 bytes in 2 blocks are still reachable in loss record 31 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x407CB2: tok_to_cmd (make_command.c:50)
==299910==    by 0x407E3B: parsing_commands (make_command.c:85)
==299910==    by 0x4082D3: main_parser (main.c:41)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 64 bytes in 1 blocks are still reachable in loss record 35 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x407004: init_built (init.c:35)
==299910==    by 0x40848E: main (main.c:86)
==299910==
==299910== 64 bytes in 1 blocks are still reachable in loss record 36 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x4078CA: new_cmd_node (make_cmd_utils.c:44)
==299910==    by 0x407DE8: parsing_commands (make_command.c:77)
==299910==    by 0x4082D3: main_parser (main.c:41)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 64 bytes in 1 blocks are still reachable in loss record 37 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x4078CA: new_cmd_node (make_cmd_utils.c:44)
==299910==    by 0x407B3A: new_cmd (make_command.c:25)
==299910==    by 0x407EB9: parsing_commands (make_command.c:90)
==299910==    by 0x4082D3: main_parser (main.c:41)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 64 bytes in 2 blocks are still reachable in loss record 38 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x405F67: token_new (tokeniser_utils.c:38)
==299910==    by 0x405B09: add_all (tokeniser.c:83)
==299910==    by 0x405BEE: tokeniser (tokeniser.c:108)
==299910==    by 0x408274: main_parser (main.c:32)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 72 bytes in 3 blocks are still reachable in loss record 39 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x48B1BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48A8B1D: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48AAF65: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x404E53: history_heredoc (here_doc_utils.c:35)
==299910==    by 0x4050C7: read_heredoc (here_doc_manage.c:92)
==299910==    by 0x4051D8: heredoc_child (here_doc_manage.c:113)
==299910==    by 0x4052C1: init_heredoc (here_doc_manage.c:173)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 104 bytes in 1 blocks are still reachable in loss record 44 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x4072CD: init_data (init.c:107)
==299910==    by 0x408485: main (main.c:85)
==299910==
==299910== 105 bytes in 3 blocks are still reachable in loss record 45 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x48B1BAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48A8B39: alloc_history_entry (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x48AAF65: add_history (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==299910==    by 0x404E53: history_heredoc (here_doc_utils.c:35)
==299910==    by 0x4050C7: read_heredoc (here_doc_manage.c:92)
==299910==    by 0x4051D8: heredoc_child (here_doc_manage.c:113)
==299910==    by 0x4052C1: init_heredoc (here_doc_manage.c:173)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 128 bytes in 4 blocks are still reachable in loss record 47 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x405F67: token_new (tokeniser_utils.c:38)
==299910==    by 0x405A16: add_word (tokeniser.c:60)
==299910==    by 0x405C1D: tokeniser (tokeniser.c:111)
==299910==    by 0x408274: main_parser (main.c:32)
==299910==    by 0x4083FD: main_reading (main.c:68)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 238 bytes in 1 blocks are still reachable in loss record 53 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408B00: ft_strjoin (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x40678C: ft_strjoin_upd (fnc_gen4.c:19)
==299910==    by 0x403E26: get_dollar (expand_utils1.c:33)
==299910==    by 0x404FCD: new_delimiter (here_doc_manage.c:31)
==299910==    by 0x4051AC: heredoc_child (here_doc_manage.c:111)
==299910==    by 0x4052C1: init_heredoc (here_doc_manage.c:173)
==299910==    by 0x4053E7: heredoc_manage (here_doc_manage.c:212)
==299910==    by 0x403C4C: exec (executor.c:90)
==299910==    by 0x40843B: main_reading (main.c:75)
==299910==    by 0x4084CC: main (main.c:91)
==299910==
==299910== 869 bytes in 68 blocks are still reachable in loss record 59 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408A52: ft_substr (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x406A5B: init_champ_env (fnc_gen5.c:26)
==299910==    by 0x40723A: init_env (init.c:94)
==299910==    by 0x4084C3: main (main.c:89)
==299910==
==299910== 3,191 bytes in 68 blocks are still reachable in loss record 74 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x408A52: ft_substr (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x406A04: init_champ_env (fnc_gen5.c:20)
==299910==    by 0x40723A: init_env (init.c:94)
==299910==    by 0x4084C3: main (main.c:89)
==299910==
==299910== 3,264 bytes in 68 blocks are still reachable in loss record 75 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40888C: ft_calloc (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x406F75: new_env (init.c:19)
==299910==    by 0x40726E: init_env (init.c:96)
==299910==    by 0x4084C3: main (main.c:89)
==299910==
==299910== 4,060 bytes in 68 blocks are still reachable in loss record 80 of 102
==299910==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==299910==    by 0x40891E: ft_strdup (in /home/apolleux/CLionProjects/minishell/minishell)
==299910==    by 0x4069B4: init_champ_env (fnc_gen5.c:17)
==299910==    by 0x40723A: init_env (init.c:94)
==299910==    by 0x4084C3: main (main.c:89)
==299910==
==299910== LEAK SUMMARY:
==299910==    definitely lost: 0 bytes in 0 blocks
==299910==    indirectly lost: 0 bytes in 0 blocks
==299910==      possibly lost: 0 bytes in 0 blocks
==299910==    still reachable: 12,485 bytes in 305 blocks
==299910==         suppressed: 214,388 bytes in 252 blocks
==299910==
==299910== For lists of detected and suppressed errors, rerun with: -s
==299910== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==298872== Warning: invalid file descriptor -2 in syscall close()


```

Verifier headers "pas de include inutiles"
check 42 headers
Mettre fichiers, et retirer wildcards du Makefile
retirer fsanitize et -g
check Norme
cleaner header file
checker nom executable
checker avec valgrind tous les tests
retirer fichiers inutiles (.junie, .idea etc...)
verifier que toutes les fonctions sxont autorisées
checker norme libft
mettre de côté le readline.supp pour valgrind
retirer cette check-list
retirer toute mention de 'Junie'