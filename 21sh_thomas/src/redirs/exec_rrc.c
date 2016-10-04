/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rrc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:39:16 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/25 06:22:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		redir_file_rrc(t_list *elem, t_save_fd *save)
{
	int		fd;
	int		fd_tmp;

	fd = -1;
	fd_tmp = -1;
	fd = open(elem->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (error_name(elem->content, elem->content));
	fd_tmp = fcntl(fd, F_DUPFD, 10);
	close(fd);
	save->index_file++;
	save->fd_file[save->index_file] = fd_tmp;
	if (save->fd_parent == '&')
	{
		dup2(fd_tmp, STDOUT_FILENO);
		dup2(fd_tmp, STDERR_FILENO);
	}
	else
		dup2(fd_tmp, save->fd_parent);
	return (fd_tmp);
}

int		exec_rrc(t_list *elem, char ***env, t_list *prog, t_save_fd *save)
{
	t_vars_redirs	vars;

	redirs_init(&vars, elem, &prog);
	check_fd_parent(elem->content, save);
	if (elem->right->type == LEX_WORD)
	{
		if ((vars.fd_file = redir_file_rrc(elem->right, save)) != -1)
			vars.ret = exec_simple(prog, env, save);
	}
	else if ((vars.fd_file = redir_file_rrc(elem->right->left, save)) != -1)
	{
		if (is_a_redir(elem->right->type))
		{
			vars.ret = exec_redir_sub(elem->right, save, &vars.current);
			if (vars.ret != -1 && vars.current->type != LEX_PIPE)
				vars.ret = exec_simple(prog, env, save);
		}
		else if (elem->right->type == LEX_PIPE)
			vars.ret = cmd_pipe(vars.current, env, prog, save);
	}
	if (elem->right->type != LEX_PIPE && vars.current->type == LEX_PIPE &&
										vars.fd_file != -1 && vars.ret != -1)
		vars.ret = cmd_pipe(vars.current, env, prog, save);
	return (check_return_redirs(&vars));
}
