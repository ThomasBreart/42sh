#include <ft_glob.h>

static char		*_match_brackets_(t_glob *g, char **format, int *err)
{
	char		*mat;
	char		*s;
	int			i;

	i = 0;
	mat = NULL;
	s = *format;
	while (**format && **format != ',' && **format != '}')
	{
		i++;
		(*format)++;
	}
	if (*err == -1 && **format != ',')
		*err = 0;
	else
		*err = 1;
	if (i)
	{
		mat = ft_strnew(i);
		ft_strncpy(mat, s, i);
	}
	else
	{
		mat = ft_strnew(i);
		ft_strncpy(mat, s, i);
	}
	return (mat);
}

static int		match_brackets(t_glob *g, char *format, char *s, t_list **results)
{
	char		*occur;
	char		*end;
	int			err;
	char		*join;
	int			i;

	err = -1;
	i = 0;
	end = ft_strchr(end, '}');
	if (!end)
		return (0);
	end++;
	while ((occur = _match_brackets_(g, &format, &err)) && err)
	{
		join = ft_strjoin(occur, end);
		i |= glob__match(g, s, join, results);
		free(join);
		format++;
	}
	return (i);
}

static int		match_bracket_types(char **format, char s)
{
	int		ret;
	int		ok;

	ok = 1;
	*format += 2;
	if (!ft_strncmp("alnum:]", *format, 7))
		ret = ft_isalnum(s);
	else if (!ft_strncmp("alpha:]", *format, 7))
		ret = ft_isalpha(s);
	else if (!ft_strncmp("blank:]", *format, 7))
		ret = ft_isblank(s);
	else if (!ft_strncmp("cntrl:]", *format, 7))
		ret = ft_iscntrl(s);
	else if (!ft_strncmp("digit:]", *format, 7))
		ret = ft_isdigit(s);
	else if (!ft_strncmp("graph:]", *format, 7))
		ret = ft_isgraph(s);
	else if (!ft_strncmp("lower:]", *format, 7))
		ret = ft_islower(s);
	else if (!ft_strncmp("print:]", *format, 7))
		ret = ft_isprint(s);
	else if (!ft_strncmp("punct:]", *format, 7))
		ret = ft_ispunct(s);
	else if (!ft_strncmp("space:]", *format, 7))
		ret = ft_isspace(s);
	else if (!ft_strncmp("upper:]", *format, 7))
		ret = ft_isupper(s);
	else if (!ft_strncmp("xdigit:]", *format, 8))
	{
		ret = ft_isxdigit(s);
		(*format)++;
	}
	else
	{
		ret = 0;
		ok = 0;
	}
	*format += (!!ok) * 7;
	return (ret);
}

static int		match_bracket(t_glob *g, char *s, char *format, t_list **results)
{
	int		sign;
	int		ret;

	sign = 0;
	ret = 0;
	format++;
	if (*format == '!' || *format == '^')
	{
		sign = 1;
		format++;
	}
	while (*format != ']' && *format)
	{
		if (!ret)
		{
			if (*(format + 1) == '-' && *(format + 2) != ']')
			{
				ret = (*format <= *s && *(format + 2) >= *s) != sign;
				format += 2;
			}
			else if (*format == '[' && *(format + 1) == ':')
				ret = (match_bracket_types(&format, *s) != sign);
			else if ((*format == *s) != sign)
				ret = 1;
		}
		format++;
	}
	format += !!*format;
	return (ret && glob__match(g, s + 1, format, results));
}

static int		match_wildcard(t_glob *g, char *s, char *format, t_list **results)
{
	char	*tmp;
	char	*occur;
	int		ret;
	int		ok;

	ok = 0;
	if (!*s)
		return (1);
	while (*format == '*')
		format++;
	if (!*format)
		return (1);
	ret = 0;
	tmp = (char*)s;
	if (*format == '/')
	{
		glob__open_directory(*g, format + 1, results);
		return (0);
	}
	else if (*format != '[' && *format != ']' && *format != '?')
	{
		while ((occur = strchr(tmp, *format)))
		{
			ok = 1;
			ret = glob__match(g, occur, format, results);
			if (ret)
				return (1);
			tmp = occur + 1;
		}
		if (!ok)
			return (0);
		return (ret);
	}
	else
		return (glob__match(g, s + 1, format, results) ||
				glob__match(g, s, format, results));
}

int					glob__match(t_glob *g, char *s, char *format, t_list **results)
{
	#ifdef DEBUG
		//printf("local = %s, s = %s, format = %s\n", g->local, s, format);
	#endif	

	if (!*s && !*format)
		return (1);
	else if (*format == '*')
		return (match_wildcard(g, s, format, results));
	else if (!*s || !*format)
		return (0);
	else if (*format == '{')
		return (match_brackets(g, format, s, results));
	else if (*format == '/')
		glob__open_directory(*g, format + 1, results);
	else if (*format == '\\' && *(format + 1) == *s)
		return (glob__match(g, s + 1, format + 2, results));
	else if (*s == *format)
		return (glob__match(g, s + 1, format + 1, results));
	else if (*format == '?')
		return (glob__match(g, s + 1, format + 1, results));
	else if (*format == '[')
		return (match_bracket(g, s, format, results));
	return (0);
}
