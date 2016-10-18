/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:34:04 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/18 14:42:24 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	exit_check_errors(char **argv)
{
	int		i;

	i = 0;
	if (ft_tablen(argv) > 2)
	{
		ft_putendl_fd("exit: Expression Syntax.", STDERR_FILENO);
		return (-1);
	}
	if (ft_tablen(argv) == 2)
		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == '-' && i != 0)
			{
				ft_putendl_fd("exit: Badly formed number.", STDERR_FILENO);
				return (-1);
			}
			else if (ft_isdigit(argv[1][i]) == 0)
			{
				ft_putendl_fd("exit: Expression Syntax.", STDERR_FILENO);
				return (-1);
			}
			i++;
		}
	return (1);
}

void			free_historic(t_historic *termcaps)
{
	t_list		*tmp;
	t_list		*tmp2;

	tmp = termcaps->head;
	while (tmp != NULL)
	{
		tmp2 = tmp;
		free(tmp->content);
		tmp = tmp->next;
		free(tmp2);
	}
}

static void	free_hash(t_historic *termcaps)
{
	int			i;
	t_hash		*elem;
	t_hash		*tmp;

	i = 0;
	while (i < 100)
	{
		elem = termcaps->hashtable[i];
		if (elem != NULL)
		{
			while (elem != NULL)
			{
				tmp = elem;
				elem = elem->next;
				free(tmp->name_bin);
				free(tmp->fullpath_bin);
				free(tmp);
			}
		}
		i++;
	}
}

int			clean_exit(char **env, t_save_fd *save)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (env != NULL)
		free_double_tab(env);
	save_historic_file(termcaps);
	free_historic(termcaps);
	free_hash(termcaps);
	ft_memdel((void**)termcaps->entry);
	ft_memdel((void**)&termcaps->name_term);
	ft_memdel((void**)&termcaps->cmd_inprogress);
	ft_memdel((void**)&termcaps->buff_paste);
	ft_memdel((void**)&termcaps->bslash_split);
	ft_memdel((void**)&termcaps->prompt);
	ft_memdel((void**)&termcaps->prompt_open);
	ft_memdel((void**)&termcaps->prompt_in_llr);
	ft_memdel((void**)&termcaps->path_historic_file);
	if (save != NULL)
		close_fd(save);
	if (termcaps->istty == 1 && set_termios(&termcaps->save, save) == -1)
		return (internal_error("clean_exit", "set_termcaps", 1));
	return (1);
}

/*
**	exit sur un unsigned char
**	return un int pour savoir si ca c ést bien passee pour gerer les && et ||
*/

int			builtin_exit(t_list *elem, char **env, t_save_fd *save)
{
	int		x;

	if (elem != NULL && exit_check_errors(elem->argv) == -1)
		return (-1);
	if (elem != NULL)
		ft_putendl("exit");
	else
		ft_putchar('\n');
	if (clean_exit(env, save) == 1)
	{
		if (elem == NULL || elem->argv[1] == NULL)
			exit(0);
		else
		{
			x = ft_atoi(elem->argv[1]);
			exit((char)x);
		}
	}
	else
		exit(-1);
	return (-1);
}
