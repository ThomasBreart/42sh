/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_listing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:54:30 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:54:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

static char			*create_fullpath2(char *local, char *name, int j)
{
	char			*path;
	char			*fullpath;

	path = ft_strnew(j + 1);
	ft_strncpy(path, name, j);
	ft_strcat(path, "/");
	fullpath = ft_strjoin(local, path);
	free(path);
	return (fullpath);
}

static char			*glob__get_path(char *local, char *name)
{
	int				i;
	char			*fullpath;
	int				j;

	i = 0;
	j = 0;
	while (name[i] && name[i] != '*' && name[i] != '[' && name[i] != '?')
	{
		if (name[i] == '/')
			j = i;
		i++;
	}
	if (!local)
	{
		if (!i)
		{
			name = ".";
			j = 1;
		}
		fullpath = ft_strnew(j + 1);
		ft_strncpy(fullpath, name, j);
		ft_strcat(fullpath, "/");
		return (fullpath);
	}
	return (create_fullpath2(local, name, j));
}

static void			glob__correct_pattern(char **name)
{
	char			*tmp;
	int				i;

	i = 0;
	tmp = *name;
	while (tmp[i] && tmp[i] != '*' &&
			tmp[i] != '[' && tmp[i] != '?')
	{
		if (tmp[i] == '/')
			*name = &tmp[i + 1];
		i++;
	}
}

static void			glob__process(char *name, t_list **matches, t_globinfo g, 
									char *pattern)
{
	g.name = ft_strjoin(g.path, name);
	g.local = g.name;
	if (can_continue(g.flags, name, pattern) &&
		glob__match(&g, name, pattern, matches))
		glob__list_adding(matches, g.name,
			!g.flags & GLOB_CASE ? &ft_strcmp : &ft_strcasecmp,
			g.origin_pattern);
	else
		free(g.name);
}

int					glob__open_directory(t_globinfo g, char *pattern,
					t_list **results)
{
	DIR				*rep;
	t_list			*matches;
	struct dirent	*entry;

	matches = NULL;
	g.origin_pattern = pattern;
	g.path = glob__get_path(g.local, pattern);
	glob__correct_pattern(&pattern);
	if ((rep = opendir(g.path)))
	{
		while ((entry = readdir(rep)))
			glob__process(entry->d_name, &matches, g, pattern);
		closedir(rep);
	}
	free(g.path);
	ft_lstadd_end(results, matches);
	return (0);
}
