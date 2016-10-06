Pro:

- historique enregistre dans un fichier
- gestion au niveau des termcaps des quotes : '' ; "" ; () ; [] ; {} et du backslash : \
- gestion des quotes au niveau des arguments ('salut a toi' == 1 argv)
- gestion cd - ; env -i -u
- Lexer / parser en arbre binaire qui tient la route
- Pas de 'cas particuliers' pour l'execution de la commande -> on en revient toujours  a la fonction cmd\_simple
- shell s'adapte au resize de la fenetre du terminal

Cons:

- Encore quelques bugs (segv sur /dev/null ; < file bin ; echo plop >&2 | qwerty ; edition de ligne + ctrl C)
- Pas de builtin echo
- l'historique remet les commandes multilignes sur une seule ligne
- quelques limites arbitraires (maxi 100 bins et 100 aggregateurs fd a lancer en une commande)
- simple quotes a gerer (echo '$PATH' != echo "$PATH")
- Code assez peu lisible au niveau des redirections / pipe
- Un peu de redondances parfois

Bonus:

- Operateurs logiques (&& ; ||)
- touche delete
- gestion metacharactere '~' et '$'
- possibilitay de changer le prompt via builtin 'change\_prompt'
- SHLVL lol
- table de hash
- recherche histo simple via Ctrl R + 'goto n'
- autocompletion