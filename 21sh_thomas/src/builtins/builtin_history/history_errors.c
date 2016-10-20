/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 15:43:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 11:24:35 by mfamilar         ###   ########.fr       */
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

int			history_usage(void)
{
	ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or ", 2);
	ft_putstr_fd("history -awrn [filename] or history -ps arg [arg...]\n", 2);
	return (1);
}
