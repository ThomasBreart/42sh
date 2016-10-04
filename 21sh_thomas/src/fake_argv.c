/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 21:51:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 22:52:54 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**fake_argv(char *s, char *s2)
{
	char	**taab;

	taab = (char**)s_memalloc(sizeof(char*) * 4, __FILE__);
	taab[0] = s_strdup("fake_tab", __FILE__);
	taab[1] = s_strdup(s, __FILE__);
	if (s2 != NULL)
		taab[2] = s_strdup(s2, __FILE__);
	else
		taab[2] = NULL;
	taab[3] = NULL;
	return (taab);
}
