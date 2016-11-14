/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

int		builtin_glob(char **argv)
{
	static int	flag = 0;

	if (!argv)
		return (flag);
	while (*argv)
	{
		if (**argv == '-')
		{
			(*argv)++;
			while (**argv)
			{
				if (**argv == 'c')
					flag |= GLOB_CASE;
				else if (**argv == 'h')
					flag |= GLOB_HIDE;
				else if (**argv == 'r')
					flag = 0;
				else
					return (0);
				(*argv)++;
			}
		}
		argv++;
	}
	return (flag);
}

int		can_continue(int flags, char *name, char *pattern)
{
	return ((flags & GLOB_HIDE) || (*name != '.' ||
	*pattern == '.'));
}
