/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:53:44 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:53:46 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		get_braces(char **pattern, int *i)
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

static char		*match_braces(char **format, int *err)
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
			get_braces(format, &i);
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
	while ((occur = match_braces(&pattern, &err))
			&& err && *pattern)
	{
		join = ft_strjoin(occur, end);
		ft_lstadd_end(patterns, ft_lstnew_noalloc(join, ft_strlen(join) + 1));
		free(occur);
		ret++;
		pattern++;
	}
	free(occur);
	if (!err)
		return (-1);
	return (ret);
}
