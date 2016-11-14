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

void	first_of_all(t_args *arg, int n)
{
	arg->typemap = NULL;
	arg->colormap = NULL;
	arg->ret = 0;
	arg->path = malloc(sizeof(char*) * (n));
	ft_memset(arg->path, 0, sizeof(char*) * (n));
	ft_memset(arg->offset, 0, sizeof(int) * 6);
}

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

t_file	*reset_values(t_args *arg, t_historic *t, char **path, char *n_path)
{
	int		fd;
	t_file	*f;

	fd = 1;
	f = NULL;
	if ((f = ft_open(arg, n_path)))
	{
		if ((arg->n = get_nbfile(f)))
		{
			arg->page = 0;
			arg->pages = arg->n / (t->ws.ws_row - 2);
			arg->new_page = 0;
			arg->y = 0;
			free(*path);
			*path = n_path;
			write(fd, "\033c\033[s", 5);
			parcours(fd, &t->ws, arg, f);
		}
		else
		{
			del(&f);
			f = NULL;
		}
	}
	return (f);
}

t_file	*do_input(t_historic *t, t_file *f, t_args *arg, char **path)
{
	char	*n_path;
	int		y;
	int		in;
	t_file	*keep;

	in = arg->in;
	y = arg->y;
	if (in == '\n' &&
	(S_IFDIR == (get_file(f, y)->s.st_mode & S_IFMT) ||
	S_IFLNK == (get_file(f, y)->s.st_mode & S_IFMT)))
		n_path = set_filename(*path, get_file(f, y)->p.name, 1);
	else if (in == 127)
		n_path = set_filename(*path, "..", 1);
	else
		n_path = NULL;
	if (n_path)
	{
		keep = f;
		if ((f = reset_values(arg, t, path, n_path)))
			del(&keep);
	}
	return (f);
}

int		reset_pages(int y, t_historic *t, t_args *arg)
{
	if (y >= (t->ws.ws_row - 2))
	{
		arg->page++;
		arg->y = 0;
	}
	if (arg->page >= arg->pages)
		arg->page = 0;
	else if (arg->page < 0)
		arg->page = arg->pages - 1;
	return (y);
}
