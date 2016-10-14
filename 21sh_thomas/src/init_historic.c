/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_historic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 18:44:26 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 16:22:55 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	recover_historic_file_error(char ***taab)
{
	ft_putendl_fd("Can't open historic file, you do shit with it...",
																STDERR_FILENO);
	free_double_tab(*taab);
	*taab = NULL;
}

char		**recover_historic_file(t_historic *termcaps)
{
	int		fd;
	char	**taab;
	char	*entry;
	int		i;

	if ((fd = open(termcaps->path_historic_file, O_RDONLY)) == -1)
		return (NULL);
	taab = (char**)s_memalloc(sizeof(char *) * 501, __FILE__);
	i = 0;
	while (i < 501)
		taab[i++] = NULL;
	i = 0;
	while (get_next_line(fd, &entry) != 0)
	{
		if (taab[i] != NULL)
			free(taab[i]);
		taab[i++] = entry;
		if (i == 501)
			break ;
	}
	ft_strdel(&entry);
	if (i == 501)
		recover_historic_file_error(&taab);
	close(fd);
	ft_putstr("YOLO\n");
	return (taab);
}

void		create_historic_list(t_historic *termcaps, char **taab)
{
	char	**tmp_taab;

	tmp_taab = taab;
	while (*tmp_taab != NULL)
	{
		add_historic(termcaps, tmp_taab, 0);
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
	file_name = s_strdup("/.21sh_historic", __FILE__);
	path = s_strnew(ft_strlen(home) + ft_strlen(file_name), __FILE__);
	path = ft_strcat(path, home);
	path = ft_strcat(path, file_name);
	free(home);
	free(file_name);
	termcaps->path_historic_file = path;
}
