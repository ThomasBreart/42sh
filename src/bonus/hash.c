/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 22:59:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/24 14:55:06 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*find_dir_in_env(char **dirs_path_env, char *dir_fullpath)
{
	while (*dirs_path_env != NULL)
	{
		if (ft_strcmp(*dirs_path_env, dir_fullpath) == 0)
			break ;
		dirs_path_env++;
	}
	return (*dirs_path_env);
}

/*
**	Si le bin a ete trouvay, check si le dir du bin est toujours present dans
**	la variable PATH de l'env, si le dir est plus present, ne retourne PAS
**	l'elem de la tale de hash
*/

static int	dir_path_dont_exist_anymore(char **env, char *fullpath_bin)
{
	char	*dir_fullpath;
	char	*tmp;
	char	**dirs_path_env;
	int		ret;

	ret = -1;
	dir_fullpath = s_strdup(fullpath_bin, __FILE__);
	tmp = ft_strrchr(dir_fullpath, '/');
	*tmp = '\0';
	dirs_path_env = check_dir_path(env);
	if (dirs_path_env == NULL)
	{
		free(dir_fullpath);
		return (-1);
	}
	tmp = find_dir_in_env(dirs_path_env, dir_fullpath);
	if (tmp != NULL)
		ret = 1;
	free_double_tab(dirs_path_env);
	free(dir_fullpath);
	return (ret);
}

/*
**	ft_printf("hash_value_modulo: %d\n", hash_value);
*/

int			hash_content(char *str)
{
	int		i;
	int		hash_value;

	i = 0;
	hash_value = 0;
	while (str[i] != '\0')
	{
		hash_value = hash_value + str[i];
		i++;
	}
	hash_value = hash_value % 100;
	return (hash_value);
}

char		*check_hashtable(char *bin, char **env)
{
	int				index;
	t_hash			*elem;
	t_historic		*termcaps;

	termcaps = get_termcaps();
	index = hash_content(bin);
	if (termcaps->hashtable[index] == NULL)
		return (NULL);
	else
	{
		elem = termcaps->hashtable[index];
		while (elem != NULL && ft_strcmp(bin, elem->name_bin) != 0)
			elem = elem->next;
		if (elem == NULL)
			return (NULL);
		if (dir_path_dont_exist_anymore(env, elem->fullpath_bin)
																		== -1)
			return (NULL);
		return (s_strdup(elem->fullpath_bin, __FILE__));
	}
}
