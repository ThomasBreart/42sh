/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_llc_read_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 01:33:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:34:36 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		redir_llc_read_loop_gnl(t_historic *termcaps, t_list *elem, int fd)
{
	char	*s;
	int		ret;

	ret = -1;
	while ((ret = get_next_line(STDIN_FILENO, &s)) != 0)
	{
		if (termcaps->llr_eof == 1 || ret == -1)
			break ;
		if (s != NULL && ft_strcmp(s, elem->content) == 0)
		{
			free(s);
			break ;
		}
		if (s != NULL)
		{
			ft_putendl_fd(s, fd);
			free(s);
		}
		else
			ft_putchar_fd('\n', fd);
	}
	return (ret);
}

int		redir_llc_read_loop_tty(t_historic *termcaps, t_list *elem, int fd)
{
	char	*s;
	int		ret;

	ret = -1;
	termcaps->prompt_current = termcaps->prompt_in_llr;
	ft_putstr(termcaps->prompt_in_llr);
	while ((ret = get_command(termcaps, &s)) != 0)
	{
		if (termcaps->llr_eof == 1 || ret == -1)
			break ;
		if (s != NULL && ft_strcmp(s, elem->content) == 0)
		{
			free(s);
			break ;
		}
		if (s != NULL)
		{
			ft_putendl_fd(s, fd);
			free(s);
		}
		else
			ft_putchar_fd('\n', fd);
		ft_putstr(termcaps->prompt_in_llr);
	}
	return (ret);
}
