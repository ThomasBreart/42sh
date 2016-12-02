/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 19:39:06 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 13:22:35 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	Parcours recursif de str pour verifier si elle comporte bien un nombre
**	de parentheses et de quotes pairs
**	Gere la priorite du quoting ([`] > ['] et ["] > [(], [{] et [[])
**	Gere l'echapement du backslash (\)
*/

int		cmd_is_open(char *str, int *end_backslash)
{
	while (*str != '\0')
	{
		if (*str == '\\')
		{
			++str;
			if (*str == '\0')
				*end_backslash = 1;
		}
		else if (*str == '(' || *str == '{' || *str == '[')
			str = goto_next_parenthesis(str);
		else if (*str == ')' || *str == '}' || *str == ']')
			return (cmd_is_open_error(*str));
		else if (*str == '"' || *str == '\'')
			str = goto_next_quote(str);
		else if (*str == '`')
			str = goto_next_backquote(str);
		if (*str == '\0')
			return (1);
		++str;
	}
	return (0);
}
