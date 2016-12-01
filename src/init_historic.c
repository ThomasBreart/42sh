/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_historic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:44:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 12:47:30 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	recover_historic_file_error(char ***taab)
{
	ft_putendl_fd("Can't open historic file, you do shit with it...",
																STDERR_FILENO);
	free_double_tab(*taab);
	*taab = NULL;
}

static void	call_gnl(int fd, char **taab, t_historic *termcaps, int limit)
{
	char	*entry;
	int		i;

	i = 0;
	while ((get_next_line(fd, &entry) != 0) && i <= 501)
	{
		if (taab[i] != NULL)
			ft_memdel((void**)taab[i]);
		if (limit != -1)
		{
			if (limit >= termcaps->n_indice)
				taab[i++] = ft_strdup(entry);
			limit++;
		}
		else
		{
			taab[i++] = ft_strdup(entry);
			termcaps->n_indice++;
		}
		ft_strdel(&entry);
	}
	ft_strdel(&entry);
	if (i == 501)
		recover_historic_file_error(&taab);
}

/*
** Le int "limit" en paramètre de la fonction sert lorsque l'on
** utilise le "flag -n" avec la commande "history" et qu'il faut
** ajouter à l'historique actuel, uniquement les nouvelles
** commandes, ajoutés au fichier ".42sh_history" après le début
** de session.
*/

char		**recover_historic_file(t_historic *termcaps, int limit)
{
	int		fd;
	char	**taab;

	if ((fd = open(termcaps->path_historic_file, O_RDONLY)) == -1)
	{
		termcaps->block_flag_a = 1;
		return (NULL);
	}
	taab = (char**)s_memalloc(sizeof(char *) * 501, __FILE__);
	ft_bzero(taab, sizeof(taab) * 501);
	call_gnl(fd, taab, termcaps, limit);
	close(fd);
	if (limit == -1 && termcaps->n_indice == 0)
		termcaps->block_flag_a = 1;
	return (taab);
}

void		create_historic_list(t_historic *termcaps, char **taab)
{
	char	**tmp_taab;

	tmp_taab = taab;
	while (*tmp_taab != NULL)
	{
		add_historic(termcaps, tmp_taab, 0, 0);
		++tmp_taab;
	}
	free_double_tab(taab);
}

void		set_path_historic_file(t_historic *termcaps, char **env)
{
	char	*home;
	char	*file_name;
	char	*path;

	if ((home = ft_getenv("HOME", env)) == NULL)
	{
		termcaps->path_historic_file = NULL;
		return ;
	}
	file_name = s_strdup("/.42sh_historic", __FILE__);
	path = s_strnew(ft_strlen(home) + ft_strlen(file_name), __FILE__);
	path = ft_strcat(path, home);
	path = ft_strcat(path, file_name);
	free(home);
	free(file_name);
	termcaps->path_historic_file = path;
}
