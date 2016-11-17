/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_next_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 08:58:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:16:07 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	find_opposite_parenthesis(char c)
{
	if (c == '(')
		return (')');
	else if (c == '{')
		return ('}');
	else if (c == '[')
		return (']');
	else
		return (0);
}

char		*goto_next_backquote(char *str)
{
	++str;
	while (*str != '\0' && *str != '`')
	{
		if (*str == '\\')
			++str;
		if (*str != '\0')
			++str;
	}
	return (str);
}

char		*goto_next_quote(char *str)
{
	char	quote;

	quote = *str;
	++str;
	while (*str != '\0' && *str != quote)
	{
		if (quote == '"' && *str == '\\')
			++str;
		else if (quote == '"' && *str == '`')
		{
			str = goto_next_backquote(str);
		}
		if (*str != '\0')
			++str;
	}
	return (str);
}

char		*goto_next_parenthesis(char *str)
{
	char	next_parenthesis;

	next_parenthesis = find_opposite_parenthesis(*str);
	++str;
	while (*str != '\0' && *str != next_parenthesis)
	{
		if (*str == '\\')
			++str;
		else if (*str == '(' || *str == '{' || *str == '[')
		{
			str = goto_next_parenthesis(str);
		}
		else if (*str == '"' || *str == '\'' || *str == '`')
		{
			str = goto_next_quote(str);
		}
		if (*str != '\0')
			++str;
	}
	return (str);
}

char		*goto_next_word(char *str, char c)
{
	while (*str != '\0' && *str != c)
	{
		if (*str == '\\')
			++str;
		else if (*str == '"' || *str == '\'' || *str == '`')
			str = goto_next_quote(str);
		if (*str != '\0')
			++str;
	}
	return (str);
}
