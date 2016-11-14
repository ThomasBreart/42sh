/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:56:02 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/07 18:33:25 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		bonus(char *s)
{
	if (ft_strcmp("explorer", s) == 0)
		return (1);
	else if (ft_strcmp("glob", s) == 0)
		return (1);
	return (0);
}

int				is_a_builtin(char *s)
{
	if (ft_strcmp("exit", s) == 0)
		return (1);
	else if (ft_strcmp("cd", s) == 0)
		return (1);
	else if (ft_strcmp("env", s) == 0)
		return (1);
	else if (ft_strcmp("setenv", s) == 0)
		return (1);
	else if (ft_strcmp("unsetenv", s) == 0)
		return (1);
	else if (ft_strcmp("bonus", s) == 0)
		return (1);
	else if (ft_strcmp("goto", s) == 0)
		return (1);
	else if (ft_strcmp("change_prompt", s) == 0)
		return (1);
	else if (ft_strcmp("history", s) == 0)
		return (1);
	else if (ft_strcmp("echo", s) == 0)
		return (1);
	else if (ft_strcmp("read", s) == 0)
		return (1);
	else
		return (bonus(s));
}
