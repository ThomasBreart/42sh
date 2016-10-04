/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:47:35 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 16:47:38 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**append_slash(char **env, char **environ)
{
	char		*path;
	int			i;
	char		*tmp;

	i = 0;
	path = ft_strsub(env[0], 5, ft_strlen(environ[0]));
	env[0] = ft_strdup(path);
	while (env[i])
	{
		tmp = ft_strjoin(env[i], "/");
		env[i] = ft_strdup(tmp);
		i++;
	}
	ft_memdel((void**)&path);
	ft_memdel((void**)&tmp);
	return (env);
}

static char	*check_path(char **path_env, char *cmd)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	tmp = NULL;
	while (path_env[i] != NULL)
	{
		tmp = ft_strjoin(path_env[i], cmd);
		path_env[i] = ft_strdup(tmp);
		if ((access(path_env[i], F_OK)) != -1)
		{
			ret = ft_strdup(path_env[i]);
			ft_memdel((void**)&tmp);
			return (ret);
		}
		i++;
	}
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&ret);
	return (NULL);
}

char		*append_path(char *environ, char *av)
{
	char	**path_env;
	char	*ret;

	if (!environ)
		return (av);
	ret = NULL;
	path_env = ft_strsplit(environ, ':');
	path_env = append_slash(path_env, &environ);
	ret = check_path(path_env, av);
	if (ret)
		av = ft_strdup(ret);
	free_double_array(path_env);
	ft_memdel((void**)&ret);
	return (av);
}

int			check_env(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "PATH", 4))
			return (i);
		i++;
	}
	return (-1);
}
