/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 08:55:06 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/13 08:55:35 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	realloc oldtab dans new_tab qui est deux fois plus grand
*/

char	**realloc_tab(char **oldtab, int *maxlen_tab, const char *filename)
{
	char	**new_tab;
	char	**tmp_oldtab;
	char	**tmp_newtab;

	*maxlen_tab *= 2;
	new_tab = (char**)s_memalloc((sizeof(char*) * (*maxlen_tab + 1)), filename);
	tmp_oldtab = oldtab;
	tmp_newtab = new_tab;
	while (*tmp_oldtab != NULL)
	{
		*tmp_newtab = s_strdup(*tmp_oldtab, __FILE__);
		++tmp_newtab;
		++tmp_oldtab;
	}
	*tmp_newtab = NULL;
	free_double_tab(oldtab);
	return (new_tab);
}
