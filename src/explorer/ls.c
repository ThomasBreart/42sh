/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:46:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/08 16:20:11 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

static void			print_cursor(t_args *arg, struct winsize ws)
{
	int			n;

	if (!can_drawing(&ws))
		return ;
	n = 0;
	write(1, "\033[u", 3);
	write(1, "\033[B", 3);
	while (n < arg->y)
	{
		write(1, "  ", 2);
		write(1, "\033[B", 3);
		write(1, "\033[2D", 4);
		n++;
	}
	write(1, "(>", 2);
	write(1, "\033[B", 3);
	write(1, "\033[2D", 4);
	while (n < ws.ws_row)
	{
		write(1, "  ", 2);
		write(1, "\033[B", 3);
		write(1, "\033[2D", 4);
		n++;
	}
	write(1, "\033[u", 3);
}

static void			inputs(int in, t_historic *t, t_args *arg, t_file **root)
{
	if (in == KEY_DOWN)
		mykey_down(t, arg);
	else if (in == KEY_UP)
		mykey_up(t, arg);
	else if (in == 127 || in == '\n')
		mykey_cd(in, t, arg, root);
	else if (in == KEY_LEFT)
		mykey_left(arg);
	else if (in == KEY_RIGHT)
		mykey_right(arg);
}

static void			navigation(t_historic *t, t_args *arg, t_file *root)
{
	int			in;

	in = 0;
	while (t->in_explorer)
	{
		read(0, &in, 4);
		if (in == '\e')
			t->in_explorer = 0;
		if (can_drawing(&t->ws))
		{
			arg->n_pages = arg->n / (t->ws.ws_row - 2);
			if (arg->n_pages == 0)
				arg->n_pages = 1;
			inputs(in, t, arg, &root);
			print_files(1, &t->ws, arg, root);
			print_cursor(arg, t->ws);
		}
		in = 0;
	}
	del(&root);
}

int				ls(t_historic *t, t_args *arg)
{
	int		fd;
	t_file	*root;

	fd = 1;
	root = ft_open(arg, ".");
	if (!root)
		return (1);
	while (t->in_explorer && t->ws.ws_row <= 2)
	{
		can_drawing(&t->ws);
	}	
	set_args(root, arg, t);
	write(fd, "\033c", 2);
	write(fd, "\033[s", 3);
	print_files(fd, &t->ws, arg, root);
	print_cursor(arg, t->ws);
	navigation(t, arg, root);
	write(fd, "\033c", 2);
	return (0);
}
