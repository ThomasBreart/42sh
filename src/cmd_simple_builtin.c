/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_simple_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 01:05:02 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 12:47:29 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			is_a_builtin(char *s)
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
	else if (ft_strcmp("history", s) == 0)
		return (1);
	else if (ft_strcmp("echo", s) == 0)
		return (1);
	else if (ft_strcmp("read", s) == 0)
		return (1);
	else if (ft_strcmp("explorer", s) == 0)
		return (1);
	else if (ft_strcmp("glob", s) == 0)
		return (1);
	return (0);
}

static int	cmd_simple_builtin2(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = 42;
	if (ft_strcmp("echo", elem->content) == 0)
		ret = builtin_echo(elem->argv);
	else if (ft_strcmp("read", elem->content) == 0)
		ret = builtin_read(elem->argv, save, env);
	else if (ft_strcmp("glob", elem->content) == 0)
		ret = builtin_glob(elem->argv);
	else if (ft_strcmp("explorer", elem->content) == 0)
		ret = builtin_explorer(get_termcaps(), env);
	else
		return (-1);
	return (ret);
}

int			cmd_simple_builtin(t_list *elem, char ***env, t_save_fd *save)
{
	int			ret;

	ret = 42;
	if (ft_strcmp("exit", elem->content) == 0)
		ret = builtin_exit(elem, *env, save);
	else if (ft_strcmp("cd", elem->content) == 0)
		ret = builtin_cd(elem->argv, env);
	else if (ft_strcmp("env", elem->content) == 0)
		ret = builtin_env(elem->argv, *env);
	else if (ft_strcmp("setenv", elem->content) == 0)
		ret = builtin_setenv(elem->argv, env, 0);
	else if (ft_strcmp("unsetenv", elem->content) == 0)
		ret = builtin_unsetenv(elem->argv, env);
	else if (ft_strcmp("history", elem->content) == 0)
		ret = builtin_history(elem->argv);
	else
		ret = cmd_simple_builtin2(elem, env, save);
	return (ret);
}
