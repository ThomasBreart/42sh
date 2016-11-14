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

static int		match_bracket(t_globinfo *g, char *s, char *pattern, t_list **results)
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

static int		match_wildcard(t_globinfo *g, char *s, char *pattern, t_list **results)
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

int					glob__match(t_globinfo *g, char *s, char *pattern, t_list **results)
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
