/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 03:26:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/03 18:35:28 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static	int	rc_file(t_list *elem, t_save_fd *save)
{
	int			fd;
	int			fd_tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	fd = open(elem->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	if (save->fd_parent == '&' || save->fd_parent == 1)
		termcaps->stdout_modified = 1;
	return (fd_tmp);
}

int			redir_file_rc(t_list *elem, t_save_fd *save, char **env)
{
	int		fd;

	fd = -1;
	if (elem->aggr_fd == 1)
		fd = exec_aggregator_fd(elem->argv[0], save);
	else
	{
		if (convert_metacharacters(elem, env) == 0)
		{
			ft_putendl_fd("42sh: ambiguous redirect", STDERR_FILENO);
			return (-1);
		}
		remove_quoting_chars(elem);
		fd = rc_file(elem, save);
	}
	return (fd);
}

/*
**	current =  pointeur de noeud qui va suivre le parcours de l arbre,
**	arrive a la fin si il est equivalent a un word
*/

int			exec_rc(t_list *elem, char ***env, t_list *prog, t_save_fd *save)
{
	t_vars_redirs	vars;

	redirs_init(&vars, elem, &prog);
	check_fd_parent(elem->content, save);
	if (elem->right->type == LEX_WORD)
	{
		if ((vars.fd_file = redir_file_rc(elem->right, save, *env)) != -1)
			exec_subsh_or_word(prog, env, save);
	}
	else if ((vars.fd_file = redir_file_rc(elem->right->left, save, *env))
																		!= -1)
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
	return (check_return_redirs(&vars, env));
}
