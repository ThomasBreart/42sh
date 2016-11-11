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
	if (in == MSHELL_KEYUP)
	{
		write(get_fd(), "\033[2D  \033[2D", 10);
		(*y)--;
	}
	else if (in == MSHELL_KEYDOWN)
	{
		write(get_fd(), "\033[2D  \033[2D", 10);
		(*y)++;
	}
	else if (in == MSHELL_KEYLEFT)
		(*page)--;
	else if (in == MSHELL_KEYRIGHT)
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
	{
		root = root->next;
	}
	return (root);
}

void			print_at(int fd, int n)
{
	while (n--)
		write(fd, "\033[B", 3);
	write(fd, "|>", 2);
}

void			print_choose(int fd, int cur, int mode)
{
	write(fd, "\033[u", 3);
	if (S_IFDIR == (mode & S_IFMT) || S_IFLNK == (mode & S_IFMT))
	{
		if (cur % 2)
			write(fd, "\033[7m[list]\033[0m [out]", 20);
		else
			write(fd, "[list] \033[7m[out]\033[0m", 20);
	}
	else
	{
		if (cur % 2)
			write(fd, "\033[7m[read]\033[0m [out]", 20);
		else
			write(fd, "[read] \033[7m[out]\033[0m", 20);
	}
}
