#include <ft_glob.h>

static int		match_bracket_types(char **pattern, int c)
{
	int		ret;
	int		ok;

	ok = 1;
	*pattern += 2;
	if (!ft_strncmp("alnum:]", *pattern, 7))
		ret = ft_isalnum(c);
	else if (!ft_strncmp("alpha:]", *pattern, 7))
		ret = ft_isalpha(c);
	else if (!ft_strncmp("blank:]", *pattern, 7))
		ret = ft_isblank(c);
	else if (!ft_strncmp("cntrl:]", *pattern, 7))
		ret = ft_iscntrl(c);
	else if (!ft_strncmp("digit:]", *pattern, 7))
		ret = ft_isdigit(c);
	else if (!ft_strncmp("graph:]", *pattern, 7))
		ret = ft_isgraph(c);
	else if (!ft_strncmp("lower:]", *pattern, 7))
		ret = ft_islower(c);
	else if (!ft_strncmp("print:]", *pattern, 7))
		ret = ft_isprint(c);
	else if (!ft_strncmp("punct:]", *pattern, 7))
		ret = ft_ispunct(c);
	else if (!ft_strncmp("space:]", *pattern, 7))
		ret = ft_isspace(c);
	else if (!ft_strncmp("upper:]", *pattern, 7))
		ret = ft_isupper(c);
	else if (!ft_strncmp("xdigit:]", *pattern, 8))
	{
		ret = ft_isxdigit(c);
		(*pattern)++;
	}
	else
	{
		ret = 0;
		ok = 0;
	}
	*pattern += (!!ok) * 7;
	return (ret);
}

static int		match_bracket(t_globinfo *g, char *s, char *pattern, t_list **results)
{
	int		sign;
	int		ret;

	sign = 0;
	ret = 0;
	pattern++;
	if (*pattern == '!' || *pattern == '^')
	{
		sign = 1;
		pattern++;
	}
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

static int		match_wildcard(t_globinfo *g, char *s, char *pattern, t_list **results)
{
	char	*tmp;
	char	*occur;
	int		ret;
	int		ok;

	ok = 0;
	if (!*s)
		return (1);
	while (*pattern == '*')
		pattern++;
	if (!*pattern)
		return (1);
	ret = 0;
	tmp = (char*)s;
	if (*pattern == '/')
	{
		glob__open_directory(*g, pattern + 1, results);
		return (0);
	}
	else if (*pattern != '[' && *pattern != ']' && *pattern != '?')
	{
		while ((occur = strchr(tmp, *pattern)))
		{
			ok = 1;
			ret = glob__match(g, occur, pattern, results);
			if (ret)
				return (1);
			tmp = occur + 1;
		}
		if (!ok)
			return (0);
		return (ret);
	}
	else
		return (glob__match(g, s + 1, pattern, results) ||
				glob__match(g, s, pattern, results));
}

int					glob__match(t_globinfo *g, char *s, char *pattern, t_list **results)
{
	#ifdef DEBUG
		//printf("local = %s, s = %s, pattern = %s\n", g->local, s, pattern);
	#endif	

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
		return (match_bracket(g, s, pattern, results));
	return (0);
}
