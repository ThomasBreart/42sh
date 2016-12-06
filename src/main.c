/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 01:38:32 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/06 10:37:21 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

int		get_entry(t_historic *termcaps, char **entry)
{
	int ret;

	if (termcaps->istty)
		ret = get_command(termcaps, entry);
	else
		ret = get_next_line(STDIN_FILENO, entry);
	termcaps->in_getcmd = 0;
	return (ret);
}

int		main(int ac, char **av_entry, char **env)
{
	char		*entry;
	t_historic	*termcaps;
	t_list		*root;
	int			ret;

	if (ac != 1)
		errors(ERR_ARGV);
	init(&termcaps, &env, &entry);
	while (1)
	{
		ret = get_entry(termcaps, &entry);
		if (entry)
		{
			if (only_chars_in_cmd(entry) == -1)
				break ;
			if ((root = cmd_analysis(&entry)) != NULL)
				exec_cmd(root->left, get_env());
			free_memory(&entry, termcaps, &root, 1);
		}
		if (ret == 0)
			break ;
	}
	return (clean_exit((*get_env()), NULL));
	(void)av_entry;
}
