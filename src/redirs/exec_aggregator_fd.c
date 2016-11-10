/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aggregator_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 07:08:02 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 15:33:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	save_aggrfd_to_stdout(int fd_aggr, int fd_parent)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (fd_aggr == 1)
	{
		termcaps->tab_aggrfd[termcaps->index_tab_aggrfd] = fd_parent;
		termcaps->index_tab_aggrfd++;
	}
}

static int	close_fd_parent(int fd_parent)
{
	if (fd_parent == '&')
	{
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else
		close(fd_parent);
	return (1);
}

static void	aggrfd_stdout_change(int fd_aggr)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (fd_aggr != 1)
		termcaps->stdout_modified = 1;
	else
		termcaps->stdout_modified = 0;
}

int			exec_aggregator_fd(char *s, t_save_fd *save)
{
	int		fd_aggr;

	if (s[0] == '-')
		return (close_fd_parent(save->fd_parent));
	fd_aggr = ft_atoi_fd(s);
	if (fd_aggr >= 10)
		return (error_fd_aggr(fd_aggr));
	if (save->fd_parent == '&')
	{
		dup2(fd_aggr, STDOUT_FILENO);
		dup2(fd_aggr, STDERR_FILENO);
	}
	else
	{
		if (dup2(fd_aggr, save->fd_parent) == -1)
			return (error_fd_aggr(fd_aggr));
		if (fd_aggr == 1)
			save_aggrfd_to_stdout(fd_aggr, save->fd_parent);
		if (save->fd_parent == 1)
			aggrfd_stdout_change(fd_aggr);
	}
	return (1);
}
