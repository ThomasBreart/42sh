/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 14:27:41 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/22 14:28:47 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			check_backslash(t_historic *tcaps, char *entry)
{
	char	*tmp;

	if (entry == NULL)
		return (0);
	if (entry[ft_strlen(entry) - 1] == '\\')
	{
		if (tcaps->bslash_split == NULL)
		{
			tcaps->bslash_split = s_strnew(ft_strlen(entry) - 1, __FILE__);
			tcaps->bslash_split = ft_strncpy(tcaps->bslash_split, entry,
														ft_strlen(entry) - 1);
		}
		else
		{
			tmp = s_strnew(ft_strlen(tcaps->bslash_split) +
												ft_strlen(entry) - 1, __FILE__);
			ft_strcat(tmp, tcaps->bslash_split);
			ft_strncat(tmp, entry, (ft_strlen(entry) - 1));
			free(tcaps->bslash_split);
			tcaps->bslash_split = tmp;
		}
		return (1);
	}
	return (0);
}
