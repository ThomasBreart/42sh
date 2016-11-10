/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_backquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:36:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 07:37:51 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	lit le contenu de la pipe et stocke ca dans une string, chaque mot est
**	separay par un espace
*/

static char	*format_cmd(int fd_pipe_exit)
{
	char	*buf;
	char	*tmp;
	char	*new_entry;
	int		ret = -1;

	new_entry = NULL;
	tmp = NULL;
	while ((ret = get_next_line(fd_pipe_exit, &buf)) >= 0)
	{
		if (ret == 0)
			break ;
		tmp = new_entry;
		if (new_entry == NULL)
			new_entry = s_strdup(buf, __FILE__);
		else
		{
			new_entry = s_strjoin(new_entry, " ", __FILE__);
			ft_strdel(&tmp);
			tmp = new_entry;
			new_entry = s_strjoin(new_entry, buf, __FILE__);
		}
		ft_strdel(&tmp);
		ft_strdel(&buf);
	}
	return (new_entry);
}

static void	backquotes_child(int pdes[2], char *str)
{
	char	*save;
	t_list	*root;

	close(pdes[PIPE_EXIT]);
	dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
	save = s_strdup(str, __FILE__);
	root = cmd_analysis(&save);
	free(save);
	exec_cmd(root->left, get_env());
	free_tree(root);
	exit(1);
}

/*
**	execute la sous-commande, son resultat est stockay dans une pipe
*/

int		exec_backquotes(char **str)
{
	int		pdes[2];
	int		child_pid;
	char	*new_entry;

	if (pipe(pdes) == -1)
		return (internal_error("exec_bacquotes", "create pipe", 0));
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_bacquotes", "fork", 0));
	if (child_pid == 0)
		backquotes_child(pdes, *str);
	else
	{
		waitpid(child_pid, NULL, 0);
		close(pdes[PIPE_ENTRY]);
		new_entry = format_cmd(pdes[PIPE_EXIT]);
		close(pdes[PIPE_EXIT]);
		ft_strdel(str);
		*str = new_entry;
	}
	return (1);
}
