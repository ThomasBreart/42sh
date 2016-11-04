/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:55:50 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/04 15:22:00 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			read_usage(void)
{
	ft_putstr_fd("read: usage: read [-r] [name ...]\n", 2);
	return (1);
}

static int			append_flag(char **args, int *flag)
{
	(*args) += 1;
	while (**args && **args != ' ')
	{
		if (**args == 'r')
			*flag = 1;
		else
			return (read_usage());
		(*args) += 1;
	}
	return (0);
}

static int	stop_flag(char **args)
{
	if ((*(*args + 2) == ' ' || *(*args + 2) == '\0'))
	{
		*(args) += 2;
		while (**args == ' ')
			*(args) += 1;
		return (0);
	}
	else
		return (read_usage());
}

int	parse_flag(char **args, int *flag)
{
	while (**args)
	{
		if (**args == '-' && *(*args + 1) == '-')
      return (stop_flag(args));
		else if (**args == '-')
    {
      if (append_flag(args, flag))
        return (1);
    }
		if (**args != ' ')
			break ;
		*(args) += 1;
	}
	return (0);
}
