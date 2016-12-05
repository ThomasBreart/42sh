/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_check_shellvar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 21:43:10 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/05 19:57:22 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			convert_shell_var(char *linecur, int i, char **entry, char **env)
{
	int		j;
	char	*key;
	char	*value;
	char	*tmp;

	tmp = linecur;
	j = i + 1;
	while (tmp[j] != '\0' && tmp[j] != ' ' && tmp[j] != '$' && tmp[j] != '"'
						&& tmp[j] != '\'' && tmp[j] != '\\' && tmp[j] != '/')
		j++;
	key = s_strsub(tmp, i + 1, (j - (i + 1)), __FILE__);
	value = ft_getenv(key, env);
	edit_line_meta(entry, value, i, (j - i));
	if (value != NULL)
	{
		j = ft_strlen(value);
		free(value);
	}
	else
		j = 0;
	free(key);
	return (i + j);
}

static int	set_dquote_flag(int flag_dquote, int *i)
{
	++(*i);
	if (flag_dquote == 0)
		return (1);
	else
		return (0);
}

/*
**	$ seul -> normal $
**	$P (var inconnue) -> aff rien
**	$PWD$ -> normal + $ a la fin
**	$PWD$PWD -> 2 x normal attachay
*/

void		check_shell_variable(char **entry, char *tmp, char **env)
{
	int		i;
	char	*tmp2;
	int		flag_dquote;

	i = 0;
	flag_dquote = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\\')
			++i;
		else if (tmp[i] == '"')
			flag_dquote = set_dquote_flag(flag_dquote, &i);
		else if (tmp[i] == '\'' && flag_dquote == 0)
		{
			tmp2 = goto_next_quote(tmp + i);
			i = (tmp2 - tmp) + 1;
		}
		else if (tmp[i] == '$' && tmp[i + 1] != '\0' && tmp[i + 1] != ' ' &&
															tmp[i + 1] != '$')
		{
			i = convert_shell_var(tmp, i, entry, env);
			tmp = *entry;
		}
		else
			i += !!tmp[i];
	}
}
