# HEREDOC
- [] Les redir n'ont pasl'air de marcher dans le heredoc (return bad fd), sauf que les fichiers sont qd meme crées, et ils sont vides
Le heredoc doit normalement créer les fichiers que lorsque la commande est valide
c```
cat << EOF > test
ls
test
EOF

bad fd
ls --> test
cat test
%
```



minichevre$ > test
AddressSanitizer:DEADLYSIGNAL
=================================================================
==266172==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0000004de35e bp 0x7ffd30dae230 sp 0x7ffd30dae1b0 T0)
==266172==The signal is caused by a READ memory access.
==266172==Hint: address points to the zero page.
    #0 0x4de35e in get_expand /home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/src/expanding/central_expand.c:130:2
    #1 0x4d9130 in exec /home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/src/executor/executor.c:93:3
    #2 0x4d2834 in main_reading /home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/src/main.c:76:3
    #3 0x4d291b in main /home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/src/main.c:92:2
    #4 0x7f0b2e2c8d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #5 0x7f0b2e2c8e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #6 0x41f3a4 in _start (/home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/minishell+0x41f3a4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/ethutin-/COMMON_TRUNK/CIRCLE3/Minishell/minishell_work/src/expanding/central_expand.c:130:2 in get_expand
==266172==ABORTING

