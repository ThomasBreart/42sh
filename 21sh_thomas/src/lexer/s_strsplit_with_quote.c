/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strsplit_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:58:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/12 05:33:37 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		find_total_word_classic_quote(char *s, int i, char c, char quote_stop)
{
	int		len;

	len = i;
	i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (s[i] == quote_stop)
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

static int		find_total_word_backquote(char *s, int i)
{
	int		len;

	len = i;
	i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (s[i] == '`')
		{
				++i;
				break ;
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
//	i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			++i;
		else if (s[i] == '\'' || s[i] == '"' || s[i] == '`')
		{
			i += find_total_word_classic_quote(s, i, c, s[i]);
			//break ;
		}
		else if (s[i] == c/* || s[i] == '`'*/)
				break ;
		if (s[i] != '\0')
			i++;
	}
	return (i - len);
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

int			backquote_case(char *s, int i)
{
	if (s[i] == '`' && (char_is_escape(s, i) == 0))
		return (1);
	return (0);
}

int			quote_case(char *s, char c, int i)
{
	if (i == 0 && (s[i] == '\'' || s[i] == '"'))
		return (1);
	else if ((s[i] == '\'' || s[i] == '"') && s[i - 1] == c)
		return (1);
	return (0);
}
/*
int			normal_case(char *s, char c, int i)
{
	if (i == 0 && s[i] != c)
		return (1);
	else if (s[i] != c && (s[i - 1] == c || s[i - 1] == '`'))
		return (1);
	return (0);
}
*/
char	**realloc_tab(char **oldtab, int *maxlen_tab, const char *filename)
{
	char	**new_tab;
	char	**tmp_oldtab;
	char	**tmp_newtab;

	*maxlen_tab *= 2;
	new_tab = (char**)s_memalloc((sizeof(char*) * (*maxlen_tab + 1)), filename);
	tmp_oldtab = oldtab;
	tmp_newtab = new_tab;
	while (*tmp_oldtab != NULL)
	{
		*tmp_newtab = s_strdup(*tmp_oldtab, __FILE__);
		++tmp_newtab;
		++tmp_oldtab;
	}
	*tmp_newtab = NULL;
	free_double_tab(oldtab);
	return (new_tab);
}

int		only_quotes_here(char *s, int i, int len)
{
	int		j;

	j = 0;
	while (s[i] != '\0' && j < len)
	{
		if (s[i] != '\'' && s[i] != '"' && s[i] != '`')
			return (0);
		++i;
		++j;
	}
	return (1);
}

/*
**	strsplit qui gere le quoting
**	le caractere de separation n'est pas pris en compte entre deux
**	quotes identiques (cf [`], ['] ou ["]) NON echapees (cf [\])
**
**	recoit une string bien formatee au niveau des quotes (quotes par paire)
**	le tableau de retour contient les backslashs et
**	les quotes (SAUF si ces quotes sont vides)
*/

char			**s_strsplit_with_quote(char *s, char c, const char *filename) // Nope, toujours pas parfait hein
{
	int		i;
	int		index_tab;
	char	**new_tab;
	int		len;
	int		maxlen_tab;

	if (s == NULL)
		return (NULL);
	maxlen_tab = 10;
	new_tab = (char**)s_memalloc((sizeof(char*) * (maxlen_tab + 1)), filename);
	index_tab = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (backquote_case(s, i))
		{
			len = find_total_word_backquote(s, i);
			if (only_quotes_here(s, i, len) == 0)
				new_tab[index_tab++] = s_strsub(s, i, len, filename);
			i += len;
		}
		else if (quote_case(s, c, i))
		{
			len = find_total_word_classic_quote(s, i, c, s[i]);
		//	if (only_quotes_here(s, i, len) == 0)
				new_tab[index_tab++] = s_strsub(s, i, len, filename);
			i += len;
		}
		else if (s[i] != c)
		{
			len = find_total_word_normal(s, i, c);
			new_tab[index_tab++] = s_strsub(s, i, len, filename);
			i += len;
		}
		else if (s[i] != '\0')
			i++;
		if (index_tab >= maxlen_tab)
			new_tab = realloc_tab(new_tab, &maxlen_tab, filename);
	}
	new_tab[index_tab] = NULL;
//	ft_print_tab(taab);
	return (new_tab);
}
