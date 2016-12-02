/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoting_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 09:08:28 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 16:10:06 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		count_char_to_del(char *str)
{
	int		k;

	k = 0;
	while (*str != '\0')
	{
		if (*str == '\\')
		{
			++str;
			++k;
		}
		else if (*str == '\'' || *str == '"')
		{
			str = goto_next_quote(str);
			k = k + 2;
		}
		if (*str != '\0')
			++str;
	}
	return (k);
}

static char		*copy_in_quote(char *str, char *newstr, int *k)
{
	char	*tmp;

	tmp = goto_next_quote(str);
	++str;
	while (str < tmp)
	{
		newstr[*k] = *str;
		(*k)++;
		++str;
	}
	return (str);
}

static void		str_without_quoting_chars(char *newstr, char *str, int k)
{
	while (*str != '\0')
	{
		if (*str == '\\')
		{
			++str;
			if (*str != '\0')
				newstr[k++] = *str;
		}
		else if (*str == '\'' || *str == '"')
			str = copy_in_quote(str, newstr, &k);
		else
			newstr[k++] = *str;
		if (*str != '\0')
			++str;
	}
}

/*
**	" ' \
*/

void			remove_quoting_chars(t_list *elem)
{
	int		i;
	int		k;
	char	*tmp;
	char	*str;

	i = 0;
	while (elem->argv[i] != NULL)
	{
		k = 0;
		str = elem->argv[i];
		k = count_char_to_del(str);
		if (k > 0)
		{
			tmp = ft_strnew(ft_strlen(str) - k);
			k = 0;
			str_without_quoting_chars(tmp, str, k);
			free(elem->argv[i]);
			elem->argv[i] = tmp;
		}
		++i;
	}
	update_elem(elem, 0);
}
