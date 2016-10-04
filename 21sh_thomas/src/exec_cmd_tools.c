/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 13:43:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/14 13:44:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		check_return_redirs(t_vars_redirs *vars)
{
	if (vars->fd_file == -1)
		return (-1);
	return (vars->ret);
}

void	redirs_init(t_vars_redirs *vars, t_list *elem, t_list **prog)
{
	vars->ret = 42;
	vars->fd_file = 42;
	vars->current = elem->right;
	if (*prog == NULL)
		*prog = elem->left;
}

int		save_fd(t_save_fd *save)
{
	int		i;

	i = 0;
	save->save_stdin = fcntl(STDIN_FILENO, F_DUPFD, 10);
	save->save_stdout = fcntl(STDOUT_FILENO, F_DUPFD, 10);
	save->save_stderr = fcntl(STDERR_FILENO, F_DUPFD, 10);
	save->fd_parent = -1;
	while (i < 100)
	{
		save->fd_file[i] = -1;
		i++;
	}
	save->index_file = -1;
	return (1);
}

int		close_fd(t_save_fd *save)
{
	restore_fd(save);
	close(save->save_stdin);
	close(save->save_stdout);
	close(save->save_stderr);
	return (1);
}

int		restore_fd(t_save_fd *save)
{
	int		i;

	i = 0;
	while (i <= save->index_file)
	{
		close(save->fd_file[i]);
		save->fd_file[i] = -1;
		i++;
	}
	save->index_file = -1;
	i = 0;
	while (i < 10)
	{
		close(i);
		i++;
	}
	dup2(save->save_stdin, STDIN_FILENO);
	dup2(save->save_stdout, STDOUT_FILENO);
	dup2(save->save_stderr, STDERR_FILENO);
	return (1);
}
