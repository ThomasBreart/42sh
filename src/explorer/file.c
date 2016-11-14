/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:02:05 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:02:07 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

t_file		*new_file(t_args *a, char *path, char *name)
{
	t_file	*file;
	char	*tmp;

	tmp = set_filename(path, name, 0);
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->next = NULL;
		lstat(tmp, &file->s);
		init_print(name, &file->s, a->mask, &file->p);
	}
	free(tmp);
	return (file);
}

void		del(t_file **f)
{
	t_file	*tmp;
	t_file	*l;
	t_print	*p;

	tmp = NULL;
	l = *f;
	while (l)
	{
		tmp = l->next;
		p = &l->p;
		free(p->name);
		delete_print(p);
		free(l);
		l = NULL;
		l = tmp;
	}
	*f = NULL;
}

t_file		*ft_open(t_args *a, char *dn)
{
	DIR		*d;
	t_dir	*e;
	t_file	*file;

	file = NULL;
	if ((d = opendir(dn)))
	{
		while ((e = readdir(d)))
			addfile(&file, new_file(a, dn, e->d_name), 1);
		closedir(d);
	}
	return (file);
}
