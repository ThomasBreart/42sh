/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_parse_flag.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:57:36 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/02 18:29:26 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
		return (cd_usage(*args));
}

static int	append_flag_p(char **args, int *flag)
{
	(*args) += 1;
	while (**args && **args != ' ')
	{
		if (**args == 'P')
			*flag = 1;
		else if (**args != 'L')
			return (cd_usage(*args));
		(*args) += 1;
	}
	return (0);
}

int			cd_parse_flag(char **args, int *flag)
{
	while (**args)
	{
		if (**args == '-' && (*(*args + 1) == ' ' || *(*args + 1) == '\0'))
			return (0);
		else if (**args == '-' && *(*args + 1) == '-')
			return (stop_flag(args));
		else if (**args == '-')
		{
			if (append_flag_p(args, flag))
				return (1);
		}
		if (**args != ' ')
			break ;
		*(args) += 1;
	}
	return (0);
}
