/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/24 01:26:12 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 21:57:20 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		len_before_thischar(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

int		len_after_thischar(char *tmp, char c)
{
	int		i;

	i = 0;
	while (tmp[i] != '\0' && tmp[i] != c)
		i++;
	if (tmp[i] != '\0')
		i++;
	return (i);
}

int		len_at_thischar(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	i++;
	return (i);
}

int		there_are_no_equal(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
