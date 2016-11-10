/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_onelvl_escape_backslash.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 07:21:13 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 07:33:32 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	count_backslash_to_remove(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			++j;
			++i;
		}
		if (str[i] != '\0')
			++i;
	}
	return (j);
}

static void	realloc_string(int j, char **str)
{
	char	*tmp;
	int		i;

	tmp = s_memalloc(sizeof(char) * (ft_strlen(*str) - j + 1), __FILE__);
	i = 0;
	j = 0;
	while ((*str)[j] != '\0')
	{
		if ((*str)[j] == '\\')
			++j;
		if ((*str)[j] != '\0')
		{
			tmp[i] = (*str)[j];
			++i;
			++j;
		}
	}
	ft_strdel(str);
	*str = tmp;
}

/*
**	supprime les characteres d'echapement (\) pour la sous-commande
*/

void		remove_onelvl_escape_backslash(char **str)
{
	int		j;

	j = count_backslash_to_remove(*str);
	if (j > 0)
		realloc_string(j, str);
}
