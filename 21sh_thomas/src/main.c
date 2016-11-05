/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 01:38:32 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/05 09:08:34 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	free_memory(char **entry, t_historic *termcaps, t_list **root,
																	int prompt)
{
	if (*entry != NULL)
		free(*entry);
	*entry = NULL;
	if (*root != NULL)
		free_tree(*root);
	*root = NULL;
	if (termcaps->istty == 1 && prompt == 1)
		ft_putstr(termcaps->prompt);
}

int		only_chars_in_cmd(char *s)
{
	while (*s != '\0')
	{
		if (*s < 32 || *s > 126)
		{
			ft_putstr_fd("42sh: error cmd: ", STDERR_FILENO);
			ft_putendl_fd(s, STDERR_FILENO);
			return (-1);
		}
		++s;
	}
	return (1);
}

int		main(int ac, char **av_entry, char **env)
{
	char		*entry;
	t_historic	*termcaps;
	t_list		*root;
	int			ret;

	av_entry = NULL;
	if (ac != 1)
		errors(ERR_ARGV);
	init(&termcaps, &env, &entry);
	while (1)
	{
		root = NULL;
		if (termcaps->istty == 1)
			ret = get_command(termcaps, &entry);
		else
			ret = get_next_line(0, &entry);
		termcaps->in_getcmd = 0;
		if (only_chars_in_cmd(entry) == -1)
			break ;
		if ((root = cmd_analysis(&entry)) != NULL)
			exec_cmd(root->left, get_env());
		free_memory(&entry, termcaps, &root, 1);
		if (ret == 0)
			break ;
	}
	return (clean_exit((*get_env()), NULL));
}
