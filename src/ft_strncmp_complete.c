/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_complete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/28 22:16:34 by tbreart           #+#    #+#             */
/*   Updated: 2015/11/27 06:26:03 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Strncmp normal + Check que s2 soit bien de taille n
**	ex:		strncmp("PWD", "PWDblablabla", 3) ==> match
**	strncmp_complete("PWD", "PWDblablabla", 3) ==> match PAS
*/

int		ft_strncmp_complete(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i + 1 < n)
		i++;
	if (s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (ft_strlen(s2) != n)
		return (42);
	return (0);
}
