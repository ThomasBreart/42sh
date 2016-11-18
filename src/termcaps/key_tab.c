/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 16:42:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:44:48 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Cherche le mot en cours a partir de la position du curseur
**	Puis cherche si le mot en cours est un bin ou un fichier
**	bin = 1er mot de la cmd OU 1er mot suivant une pipe / ; / || / &&
**	fichier = le reste
**	ret 0 -> rien a completer
**	ret 1 -> word est de type bin
**	ret 2 -> word est de type file
*/

static int	find_type_word(t_historic *termcaps, char **entry, char **word)
{
	int		cur_x;
	int		start_word;

	cur_x = termcaps->cur_x;
	if (cur_x == 0)
		return (0);
	start_word = cur_x;
	while (start_word > 0 && (*entry)[start_word - 1] != ' '
			&& (*entry)[start_word - 1] != '|'
			&& (*entry)[start_word - 1] != '&'
			&& (*entry)[start_word - 1] != ';'
			&& (*entry)[start_word - 1] != '>'
			&& (*entry)[start_word - 1] != '<')
	{
		start_word--;
	}
	*word = s_strsub(*entry, start_word, cur_x - start_word, __FILE__);
	while (start_word > 0 && (*entry)[start_word - 1] == ' ')
		start_word--;
	if (start_word == 0)
		return (1);
	if ((*entry)[start_word - 1] == '|' || (*entry)[start_word - 1] == '&'
										|| (*entry)[start_word - 1] == ';')
		return (1);
	return (2);
}

/*
**	Ret = taille du mot qui est deja presente sur la commande (entry) -> l'auto
**	completion commence apres cette taille
*/

static int	check_files(char **word, char **part_match)
{
	DIR		*dir;
	char	*dir_path;
	char	*word_cut;
	int		len;

	dir_path = NULL;
	find_dir_to_open(word, &dir_path, &word_cut);
	dir = opendir(dir_path);
	free(dir_path);
	if (dir == NULL)
		return (-1);
	if (word_cut == NULL)
	{
		return (check_just_one_file_in_dir(dir, part_match));
	}
	else
		part_match_files(dir, word_cut, part_match);
	len = ft_strlen(word_cut);
	free(word_cut);
	closedir(dir);
	return (len);
}

static int	check_bins_or_path(char **word, char **part_match)
{
	DIR			*dir;
	char		**tab_path;
	char		**tmp;

	if (ft_strchr(*word, '/') != NULL)
		return (check_files(word, part_match));
	else
	{
		if ((tab_path = check_dir_path(*get_env())) == NULL)
			return (-1);
		tmp = tab_path;
		while (*tab_path != NULL)
		{
			if ((dir = opendir(*tab_path)) != NULL)
			{
				part_match_files(dir, *word, part_match);
				closedir(dir);
			}
			tab_path++;
		}
		free_double_tab(tmp);
	}
	return (ft_strlen(*word));
}

int			ft_key_tab(t_historic *termcaps, char **entry)
{
	char	*part_match;
	int		i;
	char	*word;
	int		type_word;

	part_match = NULL;
	if (*entry == NULL)
		return (1);
	if ((type_word = find_type_word(termcaps, entry, &word)) == 0)
		return (1);
	check_tild(&word);
	if (type_word == 1)
		i = check_bins_or_path(&word, &part_match);
	else
		i = check_files(&word, &part_match);
	if (part_match != NULL)
		while (part_match[i] != '\0')
		{
			termcaps->buff = part_match[i];
			cmd_add_char(termcaps, entry);
			i++;
		}
	free(word);
	ft_strdel(&part_match);
	return (1);
}
