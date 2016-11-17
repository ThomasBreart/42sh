/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_backquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:36:17 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 00:21:34 by tbreart          ###   ########.fr       */
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

static void	launch_exec(int fd_buf, char *str)
{
	char		*save_str;
	t_list		*root;
	t_save_fd	save;

	save_fd(&save);
	dup2(fd_buf, STDOUT_FILENO);
	save_str = s_strdup(str, __FILE__);
	root = cmd_analysis(&save_str);
	free(save_str);
	exec_cmd(root->left, get_env());
	free_tree(root);
	restore_fd(&save);
	close_fd(&save);
}

static	int	error_open_buffer(char **str)
{
	internal_error("exec_backquotes", "fail open buf_backquotes", 0);
	ft_strdel(str);
	*str = s_strdup("", __FILE__);
	return (-1);
}

/*
**	execute la sous-commande, son resultat est stockay dans le fichier
**	buf_backquotes
*/

int			exec_backquotes(char **str)
{
	char		*new_entry;
	int			fd_buf;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if ((fd_buf = open("/tmp/.buf_backquotes", O_WRONLY | O_CREAT |
														O_TRUNC, 0644)) == -1)
		return (error_open_buffer(str));
	launch_exec(fd_buf, *str);
	close(fd_buf);
	if ((fd_buf = open("/tmp/.buf_backquotes", O_RDONLY, 0644)) == -1)
		return (error_open_buffer(str));
	new_entry = NULL;
	if (termcaps->child_end_sig != 1)
		new_entry = format_cmd(fd_buf);
	close(fd_buf);
	ft_strdel(str);
	if (new_entry == NULL)
		*str = s_strdup("", __FILE__);
	else
		*str = new_entry;
	return (1);
}
