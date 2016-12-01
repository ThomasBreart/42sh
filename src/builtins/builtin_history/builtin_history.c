/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 16:49:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/07 18:36:34 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** On rempli notre structure pour savoir quelles options ont été activées.
** Si on tombe sur une option non supportée ou sur le flag 'd', on
** arrête le parsing.
*/

int			append_flag(char **args, t_flags *flags)
{
	(*args) += 1;
	while (**args && **args != ' ')
	{
		if (**args == 'c')
			flags->flag_c = 1;
		else if (**args == 'd')
			return (put_flag_d(flags, args));
		else if (**args == 'a')
			flags->flag_a = 1;
		else if (**args == 'n')
			flags->flag_n = 1;
		else if (**args == 'r')
			flags->flag_r = 1;
		else if (**args == 'w')
			flags->flag_w = 1;
		else if (**args == 'p')
			flags->flag_p = 1;
		else if (**args == 's')
			flags->flag_s = 1;
		else
			return (history_usage());
		(*args) += 1;
	}
	return (0);
}

/*
** Si l'on trouve "--" dans les paramètres, c'est qu'on arrete de
** parser les options.
** Si l'on trouve "--" avec autre chose qu'un espace ou un '\0' derrière,
** c'est une erreur.
*/

static int	check_stop_flags(char **args)
{
	if ((*(*args + 2) == ' ' || *(*args + 2) == '\0'))
	{
		*(args) += 2;
		while (**args == ' ')
			*(args) += 1;
		return (0);
	}
	else
		return (history_usage());
}

/*
** Boucle principale pour parser les options.
** Si on tombe sur un paramètre qui ne commence
** pas par un tiret '-', ou sur "--", c'est la fin du parsing
** des options.
*/

static int	parse_flags(char **args, t_flags *flags)
{
	while (**args)
	{
		if (**args == '-' && *(*args + 1) == '-')
			return (check_stop_flags(args));
		else if (**args == '-')
		{
			if (ft_isalpha(*(*args + 1)))
			{
				if (append_flag(args, flags))
					return (1);
			}
			else
				return (history_usage());
		}
		if (**args != ' ')
			break ;
		*(args) += 1;
	}
	return (0);
}

/*
** Si il n'y a pas d'arguments, on affiche l'historique en entier.
** S'il y a des arguments, on renvoie soit dans "check_numeric_arg" qui va
** récupérer l'indice de la commande.
** Soit dans "parse_flags" qui va parser la ligne de commande et remlir la
** structure "t_flags".
*/

int			builtin_history(char **ar)
{
	t_flags		flags;
	char		*begin;
	char		*argv;
	int			ret;

	ret = 0;
	argv = reverse_split(ar, 1);
	begin = argv;
	ft_bzero(&flags, sizeof(t_flags));
	if (*argv == '\0')
		print_history(0);
	else if (*argv != '-')
		ret = check_numeric_arg(argv);
	else
	{
		if (!(ret = parse_flags(&argv, &flags)))
			ret = check_history_flags(argv, flags, ar);
	}
	ft_memdel((void**)&begin);
	ret = (ret == 1) ? -1 : 1;
	return (ret);
}
