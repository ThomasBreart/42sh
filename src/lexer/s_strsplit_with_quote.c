/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strsplit_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:58:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/13 08:58:27 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
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
*/

/*
**	strsplit qui gere le quoting
**	le caractere de separation (char c) n'est pas pris en compte entre deux
**	quotes identiques (cf [`], ['] ou ["]) NON echapees (cf [\])
**
**	recoit une string bien formatee au niveau des quotes (quotes par paire)
**	le tableau de retour contient les backslashs et les quotes
*/

char			**s_strsplit_with_quote(char *s, char c, const char *filename)
{
	int		index_tab;
	char	**new_tab;
	int		len;
	int		maxlen_tab;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	maxlen_tab = 10;
	new_tab = (char**)s_memalloc((sizeof(char*) * (maxlen_tab + 1)), filename);
	index_tab = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			tmp = goto_next_word(s, c);
			len = tmp - s;
			new_tab[index_tab++] = s_strsub(s, 0, len, filename);
			s = tmp;
		}
		if (*s != '\0')
			++s;
		if (index_tab >= maxlen_tab)
			new_tab = realloc_tab(new_tab, &maxlen_tab, filename);
	}
	new_tab[index_tab] = NULL;
//	ft_print_tab(taab);
	return (new_tab);
}
