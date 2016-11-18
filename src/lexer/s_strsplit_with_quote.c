/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_strsplit_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:58:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/18 01:21:01 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static	void	copy_word(char **s, char c, char **new_tab, int *index_tab)
{
	char	*tmp;
	int		len;

	tmp = goto_next_word(*s, c);
	len = tmp - *s;
	new_tab[*index_tab] = s_strsub(*s, 0, len, __FILE__);
	(*index_tab)++;
	*s = tmp;
}

/*
**	strsplit qui gere le quoting
**	le caractere de separation (char c) n'est pas pris en compte entre deux
**	quotes identiques (cf [`], ['] ou ["]) NON echapees (cf [\])
**
**	recoit une string bien formatee au niveau des quotes (quotes par paire)
**	le tableau de retour contient les backslashs et les quotes
*/

char			**s_strsplit_with_quote(char *s, char c)
{
	int		index_tab;
	char	**new_tab;
	int		maxlen_tab;

	if (s == NULL)
		return (NULL);
	maxlen_tab = 10;
	new_tab = (char**)s_memalloc((sizeof(char*) * (maxlen_tab + 1)), __FILE__);
	index_tab = 0;
	if (*s == '\0')
		new_tab[index_tab++] = s_strdup("", __FILE__);
	while (*s != '\0')
	{
		if (*s != c)
			copy_word(&s, c, new_tab, &index_tab);
		if (*s != '\0')
			++s;
		if (index_tab >= maxlen_tab)
			new_tab = realloc_tab(new_tab, &maxlen_tab, __FILE__);
	}
	new_tab[index_tab] = NULL;
	return (new_tab);
}
