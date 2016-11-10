/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_tab_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 06:17:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/26 23:06:05 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	dir_path_current(char **dir_path, char **word, char **word_cut)
{
	*dir_path = s_strdup(".", __FILE__);
	*word_cut = s_strdup(*word, __FILE__);
}

void		find_dir_to_open(char **word, char **dir_path, char **word_cut)
{
	char	*tmp;

	if (ft_strchr(*word, '/') == NULL)
		dir_path_current(dir_path, word, word_cut);
	else if ((*word)[0] == '/' &&
				((*word)[1] == '\0' || ft_strchr(&(*word)[1], '/') == NULL))
	{
		*dir_path = s_strdup("/", __FILE__);
		if ((*word)[1] == '\0')
			*word_cut = NULL;
		else
			*word_cut = s_strdup(*word + 1, __FILE__);
	}
	else
	{
		*dir_path = s_strdup(*word, __FILE__);
		tmp = ft_strrchr(*dir_path, '/');
		if (tmp[1] == '\0')
			*word_cut = NULL;
		else
		{
			*tmp = '\0';
			*word_cut = s_strdup(tmp + 1, __FILE__);
		}
	}
}

int			check_just_one_file_in_dir(DIR *dir, char **part_match)
{
	struct dirent	*current;

	if ((current = readdir(dir)) != NULL)
		*part_match = s_strdup(current->d_name, __FILE__);
	else
	{
		closedir(dir);
		return (0);
	}
	if ((current = readdir(dir)) != NULL)
	{
		free(*part_match);
		*part_match = NULL;
	}
	closedir(dir);
	return (0);
}

void		part_match_files(DIR *dir, char *word_cut, char **part_match)
{
	int				i;
	struct dirent	*current;

	while ((current = readdir(dir)) != NULL)
	{
		if (ft_strncmp(word_cut, current->d_name, ft_strlen(word_cut)) == 0)
		{
			i = 0;
			if (*part_match == NULL)
				*part_match = s_strdup(current->d_name, __FILE__);
			else
			{
				while ((*part_match)[i] != '\0' && current->d_name[i] != '\0')
				{
					if ((*part_match)[i] != current->d_name[i])
						break ;
					i++;
				}
				free(*part_match);
				(*part_match) = s_strndup(current->d_name, i, __FILE__);
			}
		}
	}
}
