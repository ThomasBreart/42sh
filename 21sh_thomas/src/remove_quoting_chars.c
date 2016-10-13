/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoting_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 09:08:28 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/13 11:32:09 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	" ' \
*/

void	remove_quoting_chars(t_list *elem)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*str;

	i = 0;
	while (elem->argv[i] != NULL)
	{
		j = 0;
		k = 0;
		str = elem->argv[i];
		while (str[j] != '\0')
		{
			if (str[j] == '\\')
			{
				++j;
				++k;
			}
			else if (str[j] == '\'' || str[j] == '"')
				++k;
			if (str[j] != '\0')
				++j;
		}
//			fprintf(stderr, "k: %d\n", k);
		if (k > 0)
		{
			tmp = ft_strnew(ft_strlen(str) - k);
			j = 0;
			k = 0;
			while (str[j] != '\0')
			{
				if (str[j] == '\\')
				{
					++j;
					if (str[j] != '\0')
						tmp[k++] = str[j++];
				}
				else if (str[j] != '\'' && str[j] != '"')
					tmp[k++] = str[j++];
				else if (str[j] != '\0')
					++j;
			}
			free(elem->argv[i]);
			elem->argv[i] = tmp;
		//	fprintf(stderr, "tmp: %s\n", tmp);
		}
		++i;
	}
	update_elem(elem);
}
