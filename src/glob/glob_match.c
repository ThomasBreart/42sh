/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:54:16 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:54:18 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

static int		match_wildcard2(char **s, char **pattern, char **tmp)
{
	if (!**s)
		return (1);
	while (**pattern == '*')
		(*pattern)++;
	if (!**pattern)
		return (1);
	*tmp = (char*)s;
	return (0);
}

static int		match_wildcard(t_globinfo *g, char *s, char *pattern,
				t_list **results)
{
	char	*tmp;
	char	*occur;

	if (match_wildcard2(&s, &pattern, &tmp))
		return (1);
	if (*pattern == '/')
		return (glob__open_directory(*g, pattern + 1, results));
	else if (*pattern != '[' && *pattern != ']' && *pattern != '?')
	{
		while ((occur = strchr(tmp, *pattern)))
		{
			if (glob__match(g, occur, pattern, results))
				return (1);
			tmp = occur + 1;
		}
		return (0);
	}
	else
		return (glob__match(g, s + 1, pattern, results) ||
				glob__match(g, s, pattern, results));
}

int				glob__match(t_globinfo *g, char *s, char *pattern,
				t_list **results)
{
	if (!*s && !*pattern)
		return (1);
	else if (*pattern == '*')
		return (match_wildcard(g, s, pattern, results));
	else if (!*s || !*pattern)
		return (0);
	else if (*pattern == '/')
		glob__open_directory(*g, pattern + 1, results);
	else if (*pattern == '\\' && *(pattern + 1) == *s)
		return (glob__match(g, s + 1, pattern + 2, results));
	else if (*s == *pattern)
		return (glob__match(g, s + 1, pattern + 1, results));
	else if (*pattern == '?')
		return (glob__match(g, s + 1, pattern + 1, results));
	else if (*pattern == '[')
		return (match_bracket(g, s, pattern + 1, results));
	return (0);
}
