/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_full_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 01:39:08 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:39:22 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char	*find_full_cmd(char *s, t_historic *termcaps)
{
	char	*tmp;
	char	*tmp2;

	if (s == NULL)
		tmp2 = s_strdup("", __FILE__);
	else
		tmp2 = s_strjoin(s, "", __FILE__);
	if (termcaps->bslash_split != NULL)
		tmp = s_strjoin(termcaps->bslash_split, tmp2, __FILE__);
	else
		tmp = s_strdup(tmp2, __FILE__);
	free(tmp2);
	return (tmp);
}
