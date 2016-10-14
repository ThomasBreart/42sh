/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_others.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:39:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 08:06:38 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_ope_subshell(char *s)
{
	char	*tmp;

	if (*s == '(')// etre sur que ce char ne peut pas etre echapay
		tmp = goto_next_parenthesis(s);
	else
		return (0);
	if (*tmp != '\0')
		++tmp;
	return (tmp - s);
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
