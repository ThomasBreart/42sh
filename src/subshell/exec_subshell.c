/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 09:06:09 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/04 16:48:13 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char		*del_parenthesis(char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = s_strndup((str + 1), (len - 2), __FILE__);
	return (new_str);
}

int				exec_cmd_subsh(t_list *first, char ***env, t_save_fd *save)
{
	int			ret;

	get_set_save_fd(save);
	ret = exec_token(first, env, save);
	return (ret);
}

static int		subshell_child(char *new_entry, t_save_fd *save)
{
	int		ret;
	t_list	*root;

	signals_reset();
	root = cmd_analysis(&new_entry);
	ret = exec_cmd_subsh(root->left, get_env(), save);
	exit(ret);
}

int				exec_subshell(t_list *elem, t_save_fd *save)
{
	char		*new_entry;
	int			ret;
	int			child_pid;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	new_entry = del_parenthesis(elem->content);
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_subshell", "fork", 0));
	termcaps->wordnofork = 1;
	if (child_pid == 0)
		subshell_child(new_entry, save);
	else
	{
		ft_strdel(&new_entry);
		waitpid(child_pid, &ret, 0);
		termcaps->wordnofork = 0;
		if (termcaps->istty == 1 && set_termios(&termcaps->term, save) == -1)
			return (internal_error("exec_subshell", "set_termcaps", 1));
		if (WEXITSTATUS(ret) == 1)
			return (1);
	}
	return (-1);
}
