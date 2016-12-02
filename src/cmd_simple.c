/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 04:30:42 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 15:36:51 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	cmd_simple_prog_child(t_historic *termcaps, t_list *elem,
												char **env, t_save_fd *save)
{
	signals_reset();
	if (termcaps->istty == 1 && set_termios(&termcaps->save, save) == -1)
		internal_error("cmd_simple_prog_child", "set_termcaps", 1);
	execve(elem->content, elem->argv, env);
	error_name(elem->content, elem->argv[0]);
	exit(EXIT_FAILURE);
}

int			cmd_simple_prog(t_list *elem, char **env, t_save_fd *save)
{
	int			ret;
	t_historic	*termcaps;
	int			father;

	termcaps = get_termcaps();
	ret = 42;
	termcaps->in_child = 1;
	if (termcaps->wordnofork == 0)
	{
		father = fork();
		if (father == -1)
			return (internal_error("cmd_simple_prog", "fork", 0));
		else if (father == 0)
			cmd_simple_prog_child(termcaps, elem, env, save);
		save_pid(father);
		waitpid(father, &ret, 0);
		if (termcaps->istty == 1 && set_termios(&termcaps->term, save) == -1)
			return (internal_error("cmd_simple_prog", "set_termcaps", 1));
		termcaps->in_child = 0;
		if (WEXITSTATUS(ret) == EXIT_FAILURE || WIFSIGNALED(ret))
			return (sig_child_func(ret));
	}
	else
		cmd_simple_prog_child(termcaps, elem, env, save);
	return (1);
}

void		stock_ret_val_in_env(int ret, char ***env)
{
	char		**varenv;
	char		*tmp;
	int			ret_val;

	ret_val = (ret == 1) ? 0 : 1;
	tmp = ft_itoa(ret_val);
	varenv = fake_argv("?", tmp);
	builtin_setenv(varenv, env, 1);
	ft_strdel(&tmp);
	free_double_tab(varenv);
}

int			exec_simple(t_list *elem, char ***env, t_save_fd *save)
{
	int			ret;
	t_historic	*termcaps;

	ret = 42;
	termcaps = get_termcaps();
	if (convert_metacharacters(elem, *env) == 0)
		return (1);
	remove_quoting_chars(elem);
	if (is_a_builtin(elem->content))
	{
		termcaps->in_builtin = 1;
		ret = cmd_simple_builtin(elem, env, save);
		termcaps->in_builtin = 0;
	}
	else
	{
		find_fullpath_bin(elem, *env);
		ret = cmd_simple_prog(elem, *env, save);
	}
	stock_ret_val_in_env(ret, env);
	return (ret);
}
