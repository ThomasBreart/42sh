/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 20:56:02 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/12 01:51:37 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_a_builtin(char *s)
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
	else
		return (0);
}
