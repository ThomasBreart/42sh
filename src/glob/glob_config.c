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
	int			i;
	int			j;

	i = 1;
	if (!argv)
		return (flag);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'c')
					flag |= GLOB_CASE;
				else if (argv[i][j] == 'h')
					flag |= GLOB_HIDE;
				else if (argv[i][j] == 'r')
					flag = 0;
				else
					return (0);
				j++;
			}
		}
		i++;
	}
	return (flag);
}

int		can_continue(int flags, char *name, char *pattern)
{
	return ((flags & GLOB_HIDE) || (*name != '.' ||
	*pattern == '.'));
}
