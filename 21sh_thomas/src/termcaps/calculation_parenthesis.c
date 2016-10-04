/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 21:48:50 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 22:52:00 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	check_quote(char c, int *pquote)
{
	if (c == '"')
	{
		(*pquote)++;
		return (1);
	}
	if (c == '\'')
	{
		pquote++;
		(*pquote)++;
		return (1);
	}
	if (c == '`')
	{
		pquote++;
		pquote++;
		(*pquote)++;
		return (1);
	}
	return (0);
}

static int	quotes_closed(int *quotes)
{
	if (*quotes % 2 == 0 && *(quotes + 1) % 2 == 0 && *(quotes + 2) % 2 == 0)
		return (1);
	return (0);
}

static int	count_parenthesis(char *str, char open, char close, int *pquote)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (str[i] != '\0')
	{
		if (check_quote(str[i], pquote))
			;
		else if (str[i] == open && quotes_closed(pquote))
			a++;
		else if (str[i] == close && quotes_closed(pquote))
			a--;
		i++;
	}
	return (a);
}

/*
**	quote[3] = " ' `
*/

int			calculation_parenthesis(t_historic *tcaps, char *s, char open,
																	char close)
{
	int		i;
	int		a;
	int		quote[3];
	int		*pquote;

	a = 0;
	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	pquote = &quote[0];
	if (tcaps->bslash_split != NULL)
		a = count_parenthesis(tcaps->bslash_split, open, close, pquote);
	i = 0;
	if (s != NULL)
		while (s[i] != '\0' && a >= 0)
		{
			if (check_quote(s[i], pquote))
				;
			else if (s[i] == open && quotes_closed(quote))
				a++;
			else if (s[i] == close && quotes_closed(quote))
				a--;
			i++;
		}
	return (a);
}
