/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strsplit_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:58:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/09 09:56:27 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		is_quote(char c)
{
	if (c == '\'' || c == '"' || c == '`')
		return (1);
	return (0);
}

int			char_is_escape(char *str, int index)
{
	int		is_escape;

	if (index == 0)
		return (0);
	is_escape = 0;
	--index;
	while (index > 0 && str[index] == '\\')
	{
		if (is_escape == 0)
			is_escape = 1;
		else
			is_escape = 0;
		--index;
	}
	return (is_escape);
}
/*
static int		find_total_word_backquote(char *s, int i, char c, char quote_stop)
{
	int		len;

	len = i;
	i++;
	while (s[i] != '\0')
	{
//		if (s[i] == '\\' && s[i + 1] != '\0')
//			++i;
		if (s[i] == quote_stop && s[i - 1] != '\\')
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				++i;
				break ;
			}
		}
		if (s[i] != '\0')
			i++;
	}
	return (i - len);
}
*/
static int		find_total_word_quote(char *s, int i, char c, char quote_stop)
{
	int		len;

	len = i;
	i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (s[i] == quote_stop/* && char_is_escape(s, i) == 0*/)
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				++i;
				break ;
			}
		}
		if (s[i] != '\0')
			i++;
	}
	return (i - len);
}

static int		find_total_word_normal(char *s, int i, char c)
{
	int		len;

	len = i;
	i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (is_quote(s[i]))
		{
			i += find_total_word_quote(s, i, c, s[i]);/// remettre + clair ?
			break ;
		}
		else if (s[i] == c)
				break ;
		if (s[i] != '\0')
			i++;
	}
	return (i - len);
}

int			quote_case(char *s, char c, int i)
{
	if (i == 0 && is_quote(s[i])) ///
		return (1);
	else if (is_quote(s[i]) && s[i - 1] == c)// check si c est pas echapay
		return (1);
	return (0);
}

int			normal_case(char *s, char c, int i)
{
	if (i == 0 && s[i] != c)
		return (1);
	else if (s[i] != c && s[i - 1] == c)
		return (1);
	return (0);
}

static int		ft_get_word_with_quote(char *s, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (quote_case(s, c, i))
		{
		//	if (s[i] == '`')
		//		len = find_total_word_backquote(s, i, c, s[i]);
		//	else
				len = find_total_word_quote(s, i, c, s[i]);
			i += len;
			j++;
		}
		else if (normal_case(s, c, i))
		{
			len = find_total_word_normal(s, i, c);
			i += len;
			j++;
		}
		/*else if ((i != 0 && s[i] != c && is_quote(s[i - 1])))// cas ls "a b c"d ? pas a faire normalement
		{
			j++;
			i = check_quote(s, i, c);
		}*/
		if (s[i] != '\0')
			i++;
	}
	return (j);
}
/*
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
		{
			if (s[a] == '\\' && s[a + 1] != '\0')
				++a;
			a++;
		}
		tmp = s_strsub(s, 0, a + 1, filename); ///
		*i = check_quote(tmp2, *i, type_quote);
	}
	else
	{
		while (s[a] != c && s[a] != '\0')
		{
			if (s[a] == '\\' && s[a + 1] != '\0')
				++a;
			a++;
		}
		tmp = s_strsub(s, 0, a, filename);
		*i = check_quote(tmp2, *i, c);
	}
	return (tmp);
}
*/
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
	char	**taab;
	int		t;
	int		len;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	t = ft_get_word_with_quote(s, c);
//	printf("t: %d\n", t);
	taab = (char**)s_memalloc(sizeof(char*) * t + sizeof(char*), filename);
	while (s[i] != '\0')
	{
		if (quote_case(s, c, i))
		{
			//str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
			len = find_total_word_quote(s, i, c, s[i]);
//			printf("len: %d\n", len);
			taab[j++] = s_strsub(s, i, len, filename);
			i += len;
			
		}
		else if (normal_case(s, c, i))
		{
		//	str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
			len = find_total_word_normal(s, i, c);
//			printf("len: %d\n", len);
			taab[j++] = s_strsub(s, i, len, filename);
			i += len;
		}
	//	else if ((i != 0 && s[i] != c && is_quote(s[i - 1])))
	//		str[j++] = ft_cpy_word_with_quote(s, c, &i, filename);
		if (s[i] != '\0')
			i++;
	}
	taab[j] = NULL;
//	ft_print_tab(taab);
	return (taab);
}
