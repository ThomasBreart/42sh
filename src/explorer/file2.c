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

int				navig_input(int *page, int *y, int n)
{
	int	in;

	in = 0;
	read(0, &in, 4);
	if (in == KEY_UP)
	{
		write(1, "\033[2D  \033[2D", 10);
		(*y)--;
	}
	else if (in == KEY_DOWN)
	{
		write(1, "\033[2D  \033[2D", 10);
		(*y)++;
	}
	else if (in == KEY_LEFT)
		(*page)--;
	else if (in == KEY_RIGHT)
		(*page)++;
	if (*y >= n)
		*y = 0;
	else if (*y < 0)
		*y = n - 1;
	return (in);
}

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

t_file			*get_file(t_file *root, int n)
{
	while (root && n--)
		root = root->next;
	return (root);
}

void			print_at(int fd, int n)
{
	while (n--)
		write(fd, "\033[B", 3);
	write(fd, "|>", 2);
}
