/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregateur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:48:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 16:48:16 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

void		do__agr_close(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (a->close)
			close(a->fd_1);
		lst = lst->next;
	}
}

void		do__agr_dup(t_list *lst)
{
	t_agregateur		*a;

	while (lst)
	{
		a = (t_agregateur*)lst->content;
		if (!a->close)
			dup2(a->fd_2, a->fd_1);
		lst = lst->next;
	}
}
