/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:58:02 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/06 15:19:04 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void		ft_remove_usless_slash(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str && i > 0 && str[i] == '/')
	{
		str[i] = '\0';
		i--;
	}
}

static int		ft_replace_dots(char *path, char *str, int *i)
{
	int	ret;

	ret = 1;
	if (*path == '.' && (!path[1] || path[1] == '.' || path[1] == '/'))
	{
		if (!path[1] || path[1] == '/')
			*i = *i - 1;
		else if (path[1] == '.')
		{
			ret = 2;
			*i = *i - 2;
		}
		while (*i > 0 && str[*i] != '/')
			*i = *i - 1;
		if (*i < 0)
			*i = 0;
		return (ret);
	}
	else
		return (0);
}

static char		*ft_processpath(char *path)
{
	char	*str;
	int		i;

	str = (char *)s_memalloc(ft_strlen(path) + 1, __FILE__);
	i = 0;
	while (*path)
	{
		if (ft_replace_dots(path, str, &i))
		{
			if (path[1] == '.')
				path++;
		}
		else
		{
			str[i] = *path;
			i++;
			str[i] = '\0';
		}
		path += !!*path;
	}
	if (i >= 0)
		str[i] = '\0';
	if (!*str)
		str = ft_strcpy(str, "/");
	return (str);
}

static char		*ft_create_path(char **paths)
{
	char *tmp;
	char *tmp2;

	if (paths[1][0] != '/')
	{
		if (ft_strlen(paths[0]) &&
				paths[0][ft_strlen(paths[0]) - 1] != '/')
			tmp = s_strjoin(paths[0], "/", __FILE__);
		else
			tmp = s_strdup(paths[0], __FILE__);
		tmp2 = s_strjoin(tmp, paths[1], __FILE__);
		ft_strdel(&tmp);
	}
	else
		tmp2 = s_strdup(paths[1], __FILE__);
	ft_remove_usless_slash(tmp2);
	tmp = ft_processpath(tmp2);
	ft_strdel(&tmp2);
	return (tmp);
}

char			*get_symbolink_path(char ***env, char *path)
{
	char	*ret;
	char	*ar[3];
	int		del;

	del = 1;
	ret = NULL;
	ar[0] = ft_getenv("PWD", *env);
	if (!ar[0])
	{
		if ((ar[0] = getcwd(NULL, 0)) == NULL)
			ar[0] = s_strdup(".", __FILE__);
		del = 0;
	}
	ar[1] = path;
	ar[2] = NULL;
	if (ar[0] && ar[1])
		ret = ft_create_path(ar);
	if (del)
		ft_memdel((void**)&ar[0]);
	return (ret);
}
