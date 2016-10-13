/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 05:09:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/13 13:10:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

void	del_subcmd_indicator(char **str/*, int type*/)
{
	int		len;
	char	*new_str;

	new_str = NULL;
	len = ft_strlen(*str);
	if (/*type == SUBCMD_BACKQUOTE && */len > 2)
		new_str = s_strndup(*str + 1, (len - 2), __FILE__);
	//else if (type == SUBCMD_DOLLAR && len > 3)
	//	new_str = s_strndup(*str + 2, (len - 3), __FILE__);
	ft_strdel(str);
	*str = new_str;
}

int		extract_subcmd(char **str, int start_analysis, int *start_subcmd, char **sub_cmd)
{
	int		i;
	int		len_subcmd;
	char	*new_str;

	i = 0;
	*start_subcmd = -1;
	while ((*str)[i] != '\0' && i < start_analysis)
		++i;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
			++i;
		else if ((*str)[i] == '`')
		{
			if (*start_subcmd == -1)
				*start_subcmd = i;
			else
			{
				len_subcmd = i - *start_subcmd + 1;// prend en compte le 2e '`'
				*sub_cmd = s_strsub(*str, *start_subcmd, len_subcmd, __FILE__);
				new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
				ft_strncat(new_str, *str, *start_subcmd);
				ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
				ft_strdel(str);
				*str = new_str;
				return (1);
			}
		}
		if ((*str)[i] != '\0')
			++i;
	}
	return (0);
}

char	*add_str_in_str(char *dest, char *src, int position)
{
	char	*new_str;

	new_str = s_strnew(ft_strlen(dest) + ft_strlen(src), __FILE__);
	ft_strncat(new_str, dest, position);
	ft_strcat(new_str, src);
	ft_strcat(new_str, dest + position);
	return (new_str);
}

/*
**	cherche et execute les sous-commandes entre backquotes
*/

void	check_backquotes(t_list **first)
{
	t_list		*elem;
	int			i;
	char		*sub_cmd;
	int			start_subcmd;
	int			start_analysis;
	char	*tmp;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD)
		{
			i = 0;
			while (elem->argv[i] != NULL) // GERER AUSSI LES $() ET () !
			{
			//	len = 0;
				start_analysis = 0;
				start_subcmd = -1;
				sub_cmd = NULL;
				while (extract_subcmd(&elem->argv[i], start_analysis, &start_subcmd, &sub_cmd) == 1)
				{
//	fprintf(stderr, "start_subcmd1: %d\n", start_subcmd);
//	fprintf(stderr, "subcmd1: %s\n", sub_cmd);
					del_subcmd_indicator(&sub_cmd/*, type*/);///
//	fprintf(stderr, "subcmd2: %s\n", sub_cmd);
					if (sub_cmd != NULL)
					{
						del_backslash(&sub_cmd);///
//	fprintf(stderr, "subcmd3: %s\n", sub_cmd);
						if (ft_strlen(sub_cmd) != 0)// pas lieu d intervenir
							exec_bacquotes(&sub_cmd);
//	fprintf(stderr, "subcmd4: %s\n", sub_cmd);
					tmp = add_str_in_str(elem->argv[i], sub_cmd, start_subcmd);
//	fprintf(stderr, "tmp: %s\n", tmp);
					ft_strdel(&elem->argv[i]);
					elem->argv[i] = tmp;
					start_analysis = start_subcmd + ft_strlen(sub_cmd);
					ft_strdel(&sub_cmd);

					}
				}
				++i;
			}
			update_elem(elem, 1);
			//show_elem(elem);
		}
		elem = elem->next;
	}
}
