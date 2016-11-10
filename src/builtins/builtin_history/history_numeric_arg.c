/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_numeric_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 15:39:58 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 11:15:33 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_too_many(char *argv)
{
	while (*argv)
	{
		if (*argv != ' ')
		{
			ft_putstr_fd("42sh: history: too many arguments\n", 2);
			return (1);
		}
		argv++;
	}
	return (0);
}

static int	check_errors(char *argv, int index)
{
	if (*argv != ' ' && *argv != '\0')
		return (numeric_argument_error(argv - index));
	return (check_too_many(argv));
}

/*
** On récupère et renvoie la valeure numérique pour la commande "history [n]"
*/

static int	get_numeric_value(char *argv)
{
	char	*cpy;
	int		index;

	index = 0;
	cpy = argv;
	while (ft_isnumber(*argv))
	{
		index++;
		argv++;
	}
	if (check_errors(argv, index))
		return (0);
	return (get_value(cpy, index));
}

/*
** "history [n]" pour afficher les 'n' derniers résultats.
** Si il y a un argument, mais qu'il ne commence pas par un tiret "-",
** c'est que l'on ne cherche pas une option, mais une valeure numérique.
** Si l'argument n'est pas de type "int", c'est une erreur !
*/

int			check_numeric_arg(char *argv)
{
	int	value;

	while (*argv)
	{
		if (!ft_isnumber(*argv))
			return (numeric_argument_error(argv));
		else
		{
			if (!(value = get_numeric_value(argv)))
				return (1);
			print_history(value);
			break ;
		}
		argv++;
	}
	return (0);
}
