# Comments
-[ ] Remove all your comments
  - //
  - /* */

# Norminette
-[ ] Except 'minichevre', check that all the names used in this project are really english
  - Variables
  - Functions


# Errors
- Lorsque l'on execute /usr/bin/env -i ./minishell , lorsque cd est execute dans minish il n'y a pas de OLDPWD et PWD, il faut les rajouter 

- rajouter export+= (check si le contenu est NULL, ne pas segfault)
- ```cd ~``` --> ne marche pas

- ```
  minichevre$ << EOF
  > $VAR
  > EOF
  dup: Bad file descriptor
```
  
- ``` 
  minichevre$ << EOF
  > fdsdjfdsf
  > sdfds
  > fds
  > fds
  > dsf
  >
  dup: Bad file descriptor
```

- ```
  minichevre$ << $VAR
  > ls
  > ls
  > s;ls\\fds
  > \dsf
  > fsd
  >
  > fds
  > Test
  > $VAR
  > $VAR
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