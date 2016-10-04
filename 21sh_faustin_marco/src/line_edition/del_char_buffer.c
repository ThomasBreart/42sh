/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:19:25 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/22 13:19:27 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void			init_tmp(char **tmp, char **tmp2, t_it *it)
{
	*tmp2 = ft_memalloc(sizeof(char) * it->len);
	*tmp = ft_memalloc(sizeof(char) * it->len);
}

static void			copy_line(int i, char *tmp, char *line)
{
	int		j;

	j = 0;
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
}

void				del_char_buffer(t_it *it, int current)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;
	int		temp;

	init_tmp(&tmp, &tmp2, it);
	i = it->i - current;
	copy_line(i, tmp, it->line);
	j = 0;
	i++;
	temp = it->len;
	while (it->line[i] && i < temp)
	{
		tmp2[j] = it->line[i];
		i++;
		j++;
	}
	tmp2[j] = '\0';
	ft_memdel((void**)&it->line);
	if (!tmp)
		return ;
	it->line = ft_strjoin(tmp, tmp2);
	free_elements(tmp, tmp2, NULL, NULL);
}
