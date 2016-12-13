#include <ft_glob.h>

static char		*get_end(char *pattern)
{
	int				i;

	i = 1;
	while (*pattern && i)
	{
		if (*pattern == '{')
			i++;
		else if (*pattern == '}')
			i--;
		if (!i)
			break ;
		pattern++;
	}
	return (i ? NULL : pattern + 1);
}

static void		get_brackets(char **pattern, int *i)
{
	int			o;

	o = 0;
	while (**pattern)
	{
		if (**pattern == '{')
			o++;		
		else if (**pattern == '}')
			o--;
		(*i)++;
		(*pattern)++;
		if (!o)
			return ;
	}
}

static char		*_match_brackets_(char **format, int *err)
{
	char		*mat;
	char		*s;
	int			i;

	i = 0;
	mat = NULL;
	s = *format;
	while (**format && **format != ',' && **format != '}')
	{
		if (**format == '{')
			get_brackets(format, &i);
		else
		{
			i++;
			(*format)++;
		}
	}
	*err = !(*err == -1 && **format != ',');
	if (*err)
	{
		mat = ft_strnew(i + 2);
		ft_strncpy(mat, s, i);
	}
	return (mat);
}

int				get_patterns(t_list **patterns, char *pattern)
{
	char		*occur;
	char		*end;
	int			err;
	int			ret;
	char		*join;

	ret = 0;
	err = -1;
	if (!(end = get_end(pattern)))
		return (0);
	while ((occur = _match_brackets_(&pattern, &err))
			&& err && *pattern)
	{
//		printf("<occur> %s\n", occur);
		join = ft_strjoin(occur, end);
		ft_lstadd_end(patterns, ft_lstnew_noalloc(join, ft_strlen(join) + 1));
		free(occur);
		ret++;
		pattern++;
	}
	free(occur);
//	printf("<end> %s\n", end);
	if (!err)	
		return (-1);
	return (ret);
}
