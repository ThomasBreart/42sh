/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_historic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:56:39 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 13:13:18 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	check_max_history_list(t_historic *termcaps)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = termcaps->head;
	while (tmp != NULL)
	{
		++i;
		tmp = tmp->next;
	}
	if (i >= 500)
	{
		if (termcaps->cur == termcaps->head)
			termcaps->cur = termcaps->cur->next;
		tmp = termcaps->head;
		termcaps->head = termcaps->head->next;
		free(tmp->content);
		free(tmp);
	}
}

void		add_historic(t_historic *termcaps, char **entry, int check_max)
{
	t_list	*tmp;
	char	*cmd;

	if (*entry == NULL)
		return ;
	if (check_max == 1)
		check_max_history_list(termcaps);
	cmd = s_strcremove(*entry, '\n', __FILE__);
	tmp = s_lstnew(cmd, __FILE__);
	free(cmd);
	if (termcaps->cur != NULL)
		while (termcaps->cur->next != NULL)
			termcaps->cur = termcaps->cur->next;
	ft_lst_add_end(termcaps->cur, tmp);
	if (termcaps->head == NULL)
		termcaps->head = tmp;
	termcaps->end = tmp;
	termcaps->cur = tmp;
	termcaps->hist = 0;
}

void		save_historic_file(t_historic *termcaps)
{
	int		fd;
	t_list	*tmp;

	if (termcaps->path_historic_file == NULL)
		return ;
	fd = open(termcaps->path_historic_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	tmp = termcaps->head;
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->content) < 500)
			ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
	close(fd);
}
