/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_others.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:39:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/08 18:12:14 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_ope_backquote(char *s)
{
	int		i;

	i = 0;
	if (s[i] != '`')
		return (0);
	++i;///
	while (s[i] != '`') // penser aux multiples bacquotes
	{
		++i;
	}
	++i;///
	return (i);
}

int		is_ope_and(char *s)
{
	if (s[0] == '&' && s[1] == '&')
		return (2);
	return (0);
}

int		is_ope_or(char *s)
{
	if (s[0] == '|' && s[1] == '|')
		return (2);
	return (0);
}

int		is_ope_pipe(char *s)
{
	if (s[0] == '|')
		return (1);
	return (0);
}

int		is_ope_coma(char *s)
{
	if (s[0] == ';')
		return (1);
	return (0);
}
