/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strsplit_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:58:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/24 19:24:56 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static int		check_quote(char *s, int i, char stop)
{
	i++;
	while (s[i] != '\0' && s[i] != stop)
		i++;
	return (i);
}

static int		ft_get_word_with_quote(char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && is_quote(s[i])) || (is_quote(s[i]) && s[i - 1] == c))
		{
			i = check_quote(s, i, s[i]);
			j++;
		}
		else if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
		{
			j++;
			i = check_quote(s, i, c);
		}
		else if ((i != 0 && s[i] != c && is_quote(s[i - 1])))
		{
			j++;
			i = check_quote(s, i, c);
		}
		(s[i] != '\0') ? i++ : 1 == 1;
	}
	return (j);
}

static char		*ft_cpy_word_with_quote(char *s, char c, int *i,
														const char *filename)
{
	int		a;
	char	*tmp;
	char	*tmp2;
	char	type_quote;

	a = 0;
	tmp2 = s;
	s = s + *i;
	if (is_quote(s[a]))
	{
		type_quote = s[a];
		a++;
		while (s[a] != type_quote && s[a] != '\0')
			a++;
		tmp = s_strsub(s, 1, a - 1, filename);
		*i = check_quote(tmp2, *i, type_quote);
	}
	else
	{
		while (s[a] != c && s[a] != '\0')
			a++;
		tmp = s_strsub(s, 0, a, filename);
		*i = check_quote(tmp2, *i, c);
	}
	return (tmp);
}

/*
**	Aluuuur, en fait cette fonction elle fait le cafe:
**	strsplit normal sauf que ca gere les '"'
**	(tout ce qu il y a entre 2 '"' sera compte comme un seul mot)
**	SAUF SI T ES MONGOL:
**	SI la premiere '"' est dans un mot deja (ex: 'bla"bla les" gens')
**	-> considere les '"' comme des caracteres normaux
*/

char			**s_strsplit_with_quote(char *s, char c, const char *filename)
{
	int		i;
	int		j;
	char	**str;
	int		t;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	t = ft_get_word_with_quote(s, c);
	str = (char**)s_memalloc(sizeof(char*) * t + sizeof(char*), filename);
	while (s[i] != '\0')
	{
		if ((i == 0 && is_quote(s[i])) || (is_quote(s[i]) && s[i - 1] == c))
			str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
		else if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
		else if ((i != 0 && s[i] != c && is_quote(s[i - 1])))
			str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
		if (s[i] != '\0')
			i++;
	}
	str[j] = NULL;
	return (str);
}
