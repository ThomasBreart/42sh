/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_backquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:36:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/01 20:00:00 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	lit le contenu du fichier buffer des backquotes et stocke ca dans une
**	string, chaque mot est separay par un espace
*/

static char	*format_cmd(int fd_buf)
{
	char	*buf;
	char	*tmp;
	char	*new_entry;
	int		ret;

	new_entry = NULL;
	while ((ret = get_next_line(fd_buf, &buf)) >= 0)
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
	ft_strdel(&buf);
	return (new_entry);
}

static void		backquotes_child(int pdes[2], char *str)
{
	char	*save_str;
	t_list	*root;

	close(pdes[PIPE_EXIT]);
	dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
	signals_reset();
	save_str = s_strdup(str, __FILE__);
	root = cmd_analysis(&save_str);
	free(save_str);
	exec_cmd(root->left, get_env());
	free_tree(root);
	exit(1);
}

/*
**	execute la sous-commande, son resultat est stockay dans le fichier
**	buf_backquotes
*/

int			exec_backquotes(char **str)
{
	char		*new_entry;
	t_historic	*termcaps;
	int			pdes[2];
	int			child_pid;
	t_save_fd	save;
	int			ret;

	save_fd(&save);
	termcaps = get_termcaps();
	if (pipe(pdes) == -1)
		return (internal_error("exec_backquotes", "create pipe", 0));
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_backquotes", "fork", 0));
	termcaps->wordnofork = 1;
	if (child_pid == 0)
		backquotes_child(pdes, *str);
	else
	{
		waitpid(child_pid, &ret, 0);
		termcaps->wordnofork = 0;
		close(pdes[PIPE_ENTRY]);
		if (termcaps->istty == 1 && set_termios(&termcaps->term, &save) == -1)
			return (internal_error("exec_backquotes", "set_termcaps", 1));
		new_entry = NULL;
		if (!WIFSIGNALED(ret))
			new_entry = format_cmd(pdes[PIPE_EXIT]);
		close(pdes[PIPE_EXIT]);
		ft_strdel(str);
		if (new_entry == NULL)
			*str = s_strdup("", __FILE__);
		else
			*str = new_entry;
	}
	return (1);
}
