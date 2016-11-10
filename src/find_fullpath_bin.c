/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fullpath_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:35:31 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/24 14:55:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Cree le parametre filename pour preparer execve :
**	cmd = commande demandee (ex: ls)
**	filename = pointeur sur le dossier contenant le binaire de cmd (ex: /bin)
**	retourne le chemin complet du binaire voulu (ex: /bin/ls)
*/

char	*create_filename(char *cmd, char *filename)
{
	int		i;
	int		j;
	char	*s;

	if (filename == NULL)
		return (NULL);
	i = ft_strlen(filename);
	j = ft_strlen(cmd);
	s = s_strnew(i + j + 2, __FILE__);
	ft_strcat(s, filename);
	ft_strcat(s, "/");
	ft_strcat(s, cmd);
	return (s);
}

/*
**	Verifie si la commande demandee existe :
**	Check chacun des dossiers de la variable PATH (qui est dans env) pour voir
**	si un des binaires (ou script) porte le meme nom que la commande demandee
**	cmd = commande demandee (ex: ls)
**	tab_path = tableau contenant tous les noms des dossiers
**	retourne NULL si la commande n'existe pas
**	ou
**	un pointeur sur le dossier contenant le binaire de la commande (ex: /bin)
**	si la commande existe
*/

char	*check_cmd_exist(char *cmd, char **tab_path)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*dir_path;

	dir_path = NULL;
	if (tab_path == NULL)
		return (NULL);
	while (*tab_path != NULL)
	{
		dir = opendir(*tab_path);
		if (dir != NULL)
		{
			while ((sd = readdir(dir)) != NULL)
				if (ft_strcmp(sd->d_name, cmd) == 0)
				{
					dir_path = *tab_path;
					break ;
				}
			closedir(dir);
			if (dir_path != NULL)
				break ;
		}
		tab_path++;
	}
	return (dir_path);
}

/*
**	Cree un tableau contenant tous les dossiers de la variable PATH de l'env
**	(Dossiers qui contiennent les binaires des commandes du shell)
*/

char	**check_dir_path(char **env)
{
	char	**tab_path;

	tab_path = NULL;
	while (*env != NULL)
	{
		if (ft_strncmp_complete(*env, "PATH",
							len_before_thischar(*env, '=')) == 0)
		{
			tab_path = s_strsplit(*env + 5, ':', __FILE__);
			break ;
		}
		env++;
	}
	return (tab_path);
}

char	*create_fullpath(char *s, char **env)
{
	char		**tab_path;
	char		*filename;

	if ((tab_path = check_dir_path(env)) == NULL)
		return (NULL);
	filename = check_cmd_exist(s, tab_path);
	filename = create_filename(s, filename);
	if (tab_path != NULL)
		free_double_tab(tab_path);
	if (filename != NULL)
		add_bin_to_hashtable(s, filename);
	return (filename);
}

void	find_fullpath_bin(t_list *elem, char **env)
{
	char	*fullpath;

	if (ft_strchr(elem->content, '/') == NULL)
	{
		if ((fullpath = check_hashtable(elem->content, env)) == NULL)
			fullpath = create_fullpath(elem->content, env);
		if (elem->content != NULL)
			free(elem->content);
		elem->content = fullpath;
	}
}
