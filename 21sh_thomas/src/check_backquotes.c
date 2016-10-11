/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 05:09:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 20:09:02 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	modifie le maillon avec le resultat de la sous commande
*/

void	update_elem(t_list *elem)
{
	char	**tmp;

	ft_strdel(&elem->content);
	elem->content = s_strdup(elem->argv[0], __FILE__);
	ft_strdel(&elem->fullcontent);
	elem->fullcontent = ft_implode(elem->argv);
	tmp = s_strsplit_with_quote(elem->fullcontent, ' ', __FILE__);
	free_double_tab(elem->argv);
	elem->argv = tmp;
}

/*
**	lit le contenu de la pipe et stocke ca dans une string, chaque mot est
**	separay par un espace
*/

char	*format_cmd(int fd_pipe_exit)
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

/*
**	execute la sous-commande, son resultat est stockay dans une pipe
*/

int		exec_bacquotes(char **str)
{
	int		pdes[2];
	int		child_pid;
	t_list *root;
	char	*new_entry;
	char	*save;

	if (pipe(pdes) == -1)
		return (internal_error("exec_bacquotes", "create pipe", 0));
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_bacquotes", "fork", 0));
	if (child_pid == 0)
	{
		close(pdes[PIPE_EXIT]);
		dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
		save = s_strdup(*str, __FILE__);
		root = cmd_analysis(&save);
		free(save);
		exec_cmd(root->left, get_env());
		exit(1);
	}
	else
	{
		waitpid(child_pid, NULL, 0);
		close(pdes[PIPE_ENTRY]);
		new_entry = format_cmd(pdes[PIPE_EXIT]);
		ft_strdel(str);
		*str = new_entry;
	}
	return (1);
}

/*
**	supprime les characteres d'echapement (\) pour la sous-commande
**	oui, je l'emmerde la norme
*/

void	del_backslash(char **str)
{
	int		i;
	int		j;
	char	*tmp;
	int		flag;

	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
		{
			++j;
			++i;
		}
		if ((*str)[i] != '\0')
			++i;
	}
	if (j > 0)
	{
		tmp = s_memalloc(sizeof(char) * (ft_strlen(*str) - j + 1), __FILE__);
		i = 0;
		j = 0;
		flag = 0;
		while ((*str)[j] != '\0')
		{
			if ((*str)[j] == '\\' && flag == 0)
			{
				++j;
				flag = 1;
			}
			else
			{
				tmp[i] = (*str)[j];
				++i;
				++j;
				flag = 0;
			}
		}
		ft_strdel(str);
		*str = tmp;
	}
}

/*
**	supprime les backquotes de la sous-commande en cours (donc le premier et le
**	dernier charactere)
*/

void	del_backquote_char(char **str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(*str);
	new_str= s_strndup(*str + 1, (len - 2), __FILE__);
	ft_strdel(str);
	*str = new_str;
}

int		backquotes_here(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\\')
			++str;
		else if (*str == '`')
			return (1);
		if (*str != '\0')
			++str;
	}
	return (0);
}

/*
**	cherche et execute les sous-commandes entre backquotes
*/

void	check_backquotes(t_list **first)
{
	t_list		*elem;
	int			i;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD)
		{
			i = 0;
			while (elem->argv[i] != NULL)
			{
				if (backquotes_here(elem->argv[i]) == 1)
				{
					del_backquote_char(&elem->argv[i]);
//fprintf(stderr, "new_str1: %s\n", elem->argv[i]);
					del_backslash(&elem->argv[i]);
//fprintf(stderr, "new_str2: %s\n", elem->argv[i]);
					if (ft_strlen(elem->argv[i]) != 0)
						exec_bacquotes(&elem->argv[i]);
				}
				update_elem(elem);
				++i;
			}
		}
		elem = elem->next;
	}
}
