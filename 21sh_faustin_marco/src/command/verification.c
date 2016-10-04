/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:50:10 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 16:50:13 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

static int			print_error(char *err)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(RESET, 2);
	return (1);
}

static int			verification_redirection_list(t_list *lst)
{
	t_redirection	*r;

	while (lst)
	{
		r = (t_redirection*)lst->content;
		if (r->type != DCHEVRON_GAUCHE &&
			(!*r->filename || !ft_isprint(*r->filename)))
			return (print_error("Need a filename\n"));
		else if (r->fd == -1)
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd(r->filename, 2);
			write(2, ": No such file or directory\n", 28);
			ft_putstr_fd(RESET, 2);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int			verification_agregateur_list(t_list *lst)
{
	t_agregateur	*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (a->fd_2 == -1)
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd(a->filename, 2);
			write(2, ": No such file or directory\n", 28);
			ft_putstr_fd(RESET, 2);
			return (1);
		}
		else if (a->fd_2 >= MAX_AGR || a->fd_1 >= MAX_AGR)
		{
			ft_putstr_fd(RED, 2);
			ft_putnbr_fd((a->fd_1 >= MAX_AGR) ? a->fd_1 : a->fd_2, 2);
			write(2, ": Bad file descriptor\n", 22);
			ft_putstr_fd(RESET, 2);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int			verification_redirections(t_redirections *rs)
{
	if (verification_redirection_list(rs->normal) ||
		verification_agregateur_list(rs->agr))
		return (1);
	return (0);
}

int					verification_pipeline(t_list *pipeline)
{
	t_command		*c;

	while (pipeline)
	{
		c = pipeline->content;
		if (!c)
			return (print_error("Need a valide command\n"));
		if (!c->args)
			return (print_error("Need a valide command\n"));
		if (verification_redirections(&c->redirs))
			return (2);
		if (c->need_redir && !c->args)
			return (print_error("Need a valide command\n"));
		pipeline = pipeline->next;
	}
	return (0);
}
