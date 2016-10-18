/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:43:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 15:43:46 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** On récupère l'argument qui à causé l'erreur pour pouvoir l'afficher
*/

static char	*get_tokenn(char *argv)
{
	char	*cpy;
	char	*ret;
	int		index;

	index = 0;
	cpy = argv;
	while (*argv && *argv != ' ')
	{
		index++;
		argv++;
	}
	ret = ft_strnew(index + 1);
	if (index)
		ret = ft_strncpy(ret, cpy, index);
	return (ret);
}

int			out_of_range(char *argv)
{
	char	*ret;

	ret = get_tokenn(argv);
	ft_putstr_fd("42sh: history: ", 2);
	if (ret)
		ft_putstr_fd(ret, 2);
	ft_putstr_fd(": history position out of range\n", 2);
	ft_memdel((void**)&ret);
	return (1);
}

int			numeric_argument_error(char *argv)
{
	char	*ret;

	ret = get_tokenn(argv);
	ft_putstr_fd("42sh: history: ", 2);
	if (ret)
		ft_putstr_fd(ret, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_memdel((void**)&ret);
	return (1);
}

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

int			check_errors(char *argv, int index)
{
	if (*argv != ' ' && *argv != '\0')
		return (numeric_argument_error(argv - index));
	return (check_too_many(argv));
}
