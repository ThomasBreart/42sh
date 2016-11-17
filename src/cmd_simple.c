/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 04:30:42 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:44:29 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	termcaps->child_end_sig = 0;
	termcaps->in_child = 1;
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
	if (WEXITSTATUS(ret) == EXIT_FAILURE)
		return (-1);
	if (WIFSIGNALED(ret))
		return (sig_child_func(ret));
	return (1);
}

/*
**	Return -1 si ya pas de builtin
*/

static int	cmd_simple_builtin(t_list *elem, char ***env, t_save_fd *save)
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
	else if (ft_strcmp("bonus", elem->content) == 0)
		ret = builtin_bonus();
	else if (ft_strcmp("goto", elem->content) == 0)
		ret = builtin_goto(elem, env);
	else if (ft_strcmp("change_prompt", elem->content) == 0)
		ret = builtin_change_prompt(elem);
	else if (ft_strcmp("history", elem->content) == 0)
		ret = builtin_history(elem->argv);
	else if (ft_strcmp("echo", elem->content) == 0)
		ret = builtin_echo(elem->argv);
	else if (ft_strcmp("read", elem->content) == 0)
		ret = builtin_read(elem->argv, save, env);
	else if (ft_strcmp("glob", elem->content) == 0)
		ret = builtin_glob(elem->argv);
	else if (ft_strcmp("explorer", elem->content) == 0)
		ret = builtin_explorer(get_termcaps());
	else
		return (-1);
	return (ret);
}

static void	stock_ret_val_in_env(int ret, char ***env)
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
