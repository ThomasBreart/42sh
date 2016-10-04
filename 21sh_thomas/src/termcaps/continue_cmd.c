/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 07:39:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 17:34:27 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	find_second_quote(int *open, int *i, char *tmp)
{
	char	save;
	int		j;

	j = *i;
	*open = 1;
	save = tmp[j];
	++j;
	while (tmp[j] != '\0' && tmp[j] != save)
	{
		if (save == '"' && tmp[j] == '`')
		{
			++j;
			while (tmp[j] != '\0' && tmp[j] != '`')
				++j;
		}
		if (tmp[j] != '\0')
			++j;
	}
	if (tmp[j] == save)
		*open = 0;
	*i = j;
}

static char	*find_full_cmd(char *s, t_historic *termcaps)
{
	char	*tmp;
	char	*tmp2;

	if (s == NULL)
		tmp2 = s_strdup("\n", __FILE__);
	else
		tmp2 = s_strjoin(s, "\n", __FILE__);
	if (termcaps->bslash_split != NULL)
		tmp = s_strjoin(termcaps->bslash_split, tmp2, __FILE__);
	else
		tmp = s_strdup(tmp2, __FILE__);
	free(tmp2);
	return (tmp);
}

/*
** '' "" ``
*/

int			check_open_quotes(t_historic *termcaps, char *s)
{
	char	*tmp;
	int		i;
	int		open;

	open = 0;
	tmp = find_full_cmd(s, termcaps);
	if (tmp == NULL)
		return (0);
	i = 0;
	while (tmp[i] != '\0')
	{
		open = 0;
		if (tmp[i] == '`' || tmp[i] == '\'' || tmp[i] == '"')
			find_second_quote(&open, &i, tmp);
		if (tmp[i] != '\0')
			++i;
	}
	if (open == 1)
	{
		ft_strdel(&termcaps->bslash_split);
		termcaps->bslash_split = tmp;
	}
	else
		free(tmp);
	return (open);
}

static int	open_chars_error(t_historic *tcaps, char close)
{
	tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	ft_putstr_fd("Parse error near '", STDERR_FILENO);
	ft_putchar_fd(close, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	ft_putstr(tcaps->prompt);
	return (-1);
}

/*
** () {} []
*/

int			check_open_chars(t_historic *tcaps, char *s, char open, char close)
{
	char	*tmp;
	int		a;

	a = calculation_parenthesis(tcaps, s, open, close);
	if (a > 0)
	{
		if (s != NULL)
		{
			if (tcaps->bslash_split == NULL)
				tcaps->bslash_split = s_strdup(s, __FILE__);
			else
			{
				tmp = s_strjoin(tcaps->bslash_split, s, __FILE__);
				free(tcaps->bslash_split);
				tcaps->bslash_split = tmp;
			}
		}
		return (1);
	}
	if (a < 0)
		return (open_chars_error(tcaps, close));
	return (0);
}
