/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:54:11 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:54:12 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

static int		match_bracket_types2(char *pattern, int c)
{
	if (!ft_strncmp("alnum:]", pattern, 7))
		return (ft_isalnum(c));
	else if (!ft_strncmp("alpha:]", pattern, 7))
		return (ft_isalpha(c));
	else if (!ft_strncmp("blank:]", pattern, 7))
		return (ft_isblank(c));
	else if (!ft_strncmp("cntrl:]", pattern, 7))
		return (ft_iscntrl(c));
	else if (!ft_strncmp("digit:]", pattern, 7))
		return (ft_isdigit(c));
	else if (!ft_strncmp("graph:]", pattern, 7))
		return (ft_isgraph(c));
	else if (!ft_strncmp("lower:]", pattern, 7))
		return (ft_islower(c));
	else if (!ft_strncmp("print:]", pattern, 7))
		return (ft_isprint(c));
	else if (!ft_strncmp("punct:]", pattern, 7))
		return (ft_ispunct(c));
	else if (!ft_strncmp("space:]", pattern, 7))
		return (ft_isspace(c));
	else if (!ft_strncmp("upper:]", pattern, 7))
		return (ft_isupper(c));
	return (-1);
}

static int		match_bracket_types(char **pattern, int c)
{
	int		ret;
	int		ok;

	*pattern += 2;
	ok = match_bracket_types2(*pattern, c);
	ret = 1;
	if (ok == -1 &&
		!ft_strncmp("xdigit:]", *pattern, 8))
	{
		ret = ft_isxdigit(c);
		(*pattern)++;
	}
	else
		ret = ok;
	if (ret)
		*pattern += 7;
	return (ret);
}

int				match_bracket(t_globinfo *g, char *s, char *pattern,
				t_list **results)
{
	int		sign;
	int		ret;

	ret = 0;
	sign = (*pattern == '!' || *pattern == '^');
	pattern += sign;
	while (*pattern != ']' && *pattern)
	{
		if (!ret)
		{
			if (*(pattern + 1) == '-' && *(pattern + 2) != ']')
			{
				ret = (*pattern <= *s && *(pattern + 2) >= *s) != sign;
				pattern += 2;
			}
			else if (*pattern == '[' && *(pattern + 1) == ':')
				ret = (match_bracket_types(&pattern, *s) != sign);
			else if ((*pattern == *s) != sign)
				ret = 1;
		}
		pattern++;
	}
	pattern += !!*pattern;
	return (ret && glob__match(g, s + 1, pattern, results));
}
