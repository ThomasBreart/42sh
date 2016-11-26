/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 20:03:52 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 20:03:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

int		skip_pages(struct winsize *ws, int *cur, t_file **ptr, t_args *a)
{
	int		page;
	t_file	*f;

	page = 0;
	f = *ptr;
	while (f && page < a->page)
	{
		if (*cur >= ws->ws_row - 2)
		{
			*cur = 0;
			page++;
		}
		f = f->next;
		(*cur)++;
	}
	*ptr = f;
	return (page);
}
