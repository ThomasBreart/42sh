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

int				setoutput(int fd, int x_max, char *path, t_file *f)
{
	int			in;
	int			cur;

	cur = 1;
	in = 0;
	write(fd, "\033[u", 3);
	print_at(fd, x_max);
	write(fd, "\033[s", 3);
	while (in != '\n' && in != '\e' && read(0, &in, 4))
	{
		cur += (in == KEY_RIGHT || in == KEY_LEFT);
		if (in != '\n' && in != '\e')
			in = 0;
	}
	if (in == '\n')
	{
		write(fd, "\033c", 2);
		write(fd, path, ft_strlen(path));
		write(fd, f->p.name, f->p.len_name);
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

t_file			*navigation(t_historic *t, char **path, t_args *arg, t_file *f)
{
	int		in;
	int		fd;

	fd = 1;
	while ((in = navig_input(&arg->page, &arg->y, arg->n)) != '\e')
	{
		arg->y = reset_pages(arg->y, t, arg);
		arg->in = in;
		if (in == '\n' || in == 127)
			f = do_input(t, f, arg, path);
		else if (in == ' ')
		{
			if (setoutput(fd, t->ws.ws_row - 1, *path, get_file(f, arg->y)))
			{
				del(&f);
				ft_memdel((void**)path);
				return (NULL);
			}
			arg->new_page = -1;
		}
		no_name(fd, arg, t, f);
	}
	return (f);
}

int				ls(t_historic *t, t_args *arg)
{
	char	*path;
	char	*new_path;
	t_file	*root;
	int		fd;

	fd = 1;
	path = ft_strdup(arg->path);
	new_path = set_filename("\0", path, 1);
	root = ft_open(arg, new_path);
	write(fd, "\033c", 2);
	write(fd, "\033[s", 3);
	arg->page = 0;
	arg->n = get_nbfile(root);
	arg->pages = arg->n / (t->ws.ws_row - 2);
	parcours(fd, &t->ws, arg, root);
	write(fd, "\033[u", 3);
	print_at(fd, 1);
	arg->new_page = 0;
	root = navigation(t, &new_path, arg, root);
	del(&root);
	free(path);
	free(new_path);
	write(fd, "\033c", 2);
	return (0);
}
