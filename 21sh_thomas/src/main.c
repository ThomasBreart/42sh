/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/17 01:38:32 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/08 20:10:37 by tbreart          ###   ########.fr       */
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

int		main(int ac, char **av_entry, char **env)
{
	char		*entry;
	t_historic	*termcaps;
	t_list		*root;
	int			ret;
//	char		buf[101];

//	ft_putendl_fd("launch shell !", STDERR_FILENO);
//	ft_putendl_fd("test read stdin:", STDERR_FILENO);
//	ft_bzero(buf, 101);
//	read(STDIN_FILENO, &buf, 100);
//	ft_putendl_fd(buf, STDERR_FILENO);
	av_entry = NULL;
	if (ac != 1)
		errors(ERR_ARGV);
	init(&termcaps, &env, &entry);
	while (1)
	{
		root = NULL;
		if (termcaps->istty == 1)
			ret = get_command(termcaps, &entry);
//		else
//			ret = get_next_line(STDIN_FILENO, &entry);
		termcaps->in_getcmd = 0;
		if ((root = cmd_analysis(&entry)) != NULL) // msg err si ret = -1
			exec_cmd(root->left, get_env());
		else
			printf("cmd_analysis: error\n");
		free_memory(&entry, termcaps, &root, 1);
		if (ret == 0)
			break ;
	}
	return (clean_exit((*get_env()), NULL));
}
