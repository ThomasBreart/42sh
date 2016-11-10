/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strcremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 19:26:47 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 19:26:49 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	malloc une string et copie str sans les chars "del"
*/

char	*s_strcremove(char *str, char del, const char *filename)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	tmp = str;
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
		if (tmp[i++] != del)
			++j;
	tmp2 = s_strnew(j, filename);
	i = 0;
	j = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] != del)
			tmp2[j++] = tmp[i];
		++i;
	}
	return (tmp2);
}
