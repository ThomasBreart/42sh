/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 19:57:49 by fjacquem          #+#    #+#             */
/*   Updated: 2016/05/16 19:57:50 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

int				get_nbfile(t_file *root)
{
	int	n;

	n = 0;
	while (root)
	{
		n++;
		root = root->next;
	}
	return (n);
}

t_file			*go_page(t_file *root, int n_page, int row)
{
	int			cur;
	int			page;

	cur = 0;
	page = 0;
	while (root && page < n_page)
	{
		if (cur >= row - 2)
		{
			cur = 0;
			page++;
		}
		printf("%s\n", root->p.name);
		root = root->next;
		cur++;
	}
	sleep(1);
	return (root);
}

t_file			*get_file(t_file *root, t_args *a, t_historic *t)
{
	int			cur;

	cur = a->y;
	root = go_page(root, a->page, t->ws.ws_row);
	while (root && cur--)
		root = root->next;
	return (root);
	(void)t;
}

void			print_at(int fd, int n)
{
	while (n--)
		write(fd, "\033[B", 3);
	write(fd, "|>", 2);
}
