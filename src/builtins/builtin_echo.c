/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:51:30 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/25 13:51:18 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	remove_flag(char **av, int indice)
{
	char		*tmp;

	tmp = av[indice];
	while (av[indice])
	{
		av[indice] = av[indice + 1];
		indice++;
	}
	ft_memdel((void**)&tmp);
}

static void	print_string(char **av, int delta, int flag)
{
	int				i;
	int				ok;

	ok = 0;
	i = delta;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (*av[i])
			ok = 1;
		if (ok && av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
}

static int	check_flags(char **av, int *flag)
{
	int			j;
	int			i;

	i = 1;
	if (av[i] && ft_strncmp(av[i], "-", 1))
		return (i);
	while (av[i])
	{
		j = 2;
		if (av[i] && ft_strncmp(av[i], "-n", 2) &&
			(!ft_strcmp(av[i], "--") || av[i][0] != ' '))
			return (i);
		if (av[i] && !ft_strncmp(av[i], "-n", 2))
		{
			while (av[i][j] && av[i][j] == 'n')
				j++;
			if (av[i][j] && av[i][j] != ' ' && av[i][j] != '\0')
				return (i);
			remove_flag(av, i);
			*flag = 1;
			i--;
		}
		i++;
	}
	return (i);
}

int			builtin_echo(char **av)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!av[1])
	{
		ft_putchar('\n');
		return (1);
	}
	else
		i = check_flags(av, &flag);
	if (flag && !av[i])
		return (1);
	else if (flag && av[i])
		print_string(av, i, flag);
	else
		print_string(av, 1, flag);
	return (1);
}
