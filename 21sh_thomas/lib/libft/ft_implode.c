/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 04:23:34 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 04:24:47 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	find_len_strings(char **tmp, int *len, int *i)
{
	while (*tmp != NULL)
	{
		*len += ft_strlen(*tmp);
		++*len;
		++tmp;
		++*i;
	}
}

/*
**	cf fonction implode de php
**	retourne une string contenant toutes les strings du tableau separees par
**	un espace
*/

char	*ft_implode(char **taab)
{
	char	*str;
	char	**tmp;
	int		len;
	int		i;

	if (taab == NULL || *taab == NULL)
		return (NULL);
	tmp = taab;
	len = -1;
	i = 0;
	find_len_strings(taab, &len, &i);
	str = s_strnew(len, __FILE__);
	tmp = taab;
	while (*tmp != NULL)
	{
		ft_strcat(str, *tmp);
		if (i > 1)
			ft_strcat(str, " ");
		++tmp;
		--i;
	}
	return (str);
}
