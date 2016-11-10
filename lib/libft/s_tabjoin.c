/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tabjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 04:26:43 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 04:26:47 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	concat 2 tableaux
*/

char	**s_tabjoin(char **tab1, char **tab2, const char *filename)
{
	char	**new_tab;
	int		tab1_len;
	int		tab2_len;
	int		i;
	int		j;

	tab1_len = ft_tablen(tab1);
	tab2_len = ft_tablen(tab2);
	new_tab = (char**)s_memalloc(sizeof(char*) * (tab1_len + tab2_len + 1), filename);
	i = 0;
	while (i < tab1_len)
	{
		new_tab[i] = s_strdup(tab1[i], filename);
		++i;
	}
	j = 0;
	while (j < tab2_len)
	{
		new_tab[i + j] = s_strdup(tab2[j], filename);
		++j;
	}
	return (new_tab);
}
