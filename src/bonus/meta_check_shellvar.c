/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_check_shellvar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 21:43:10 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:17:10 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		convert_shell_var(char *tmp, int i, char **entry, char **env)
{
	int		j;
	char	*key;
	char	*value;

	j = i + 1;
	while (tmp[j] != '\0' && tmp[j] != ' ' && tmp[j] != '$' && tmp[j] != '"')
		j++;
	key = s_strsub(tmp, i + 1, (j - (i + 1)), __FILE__);
	value = ft_getenv(key, env);
	edit_line_meta(entry, value, i, (j - i));
	tmp = *entry;
	i = 0;
	if (value != NULL)
		free(value);
	free(key);
	return (i);
}

/*
**	$ seul -> normal $
**	$P (var inconnue) -> aff rien
**	$PWD$ -> normal + $ a la fin
**	$PWD$PWD -> 2 x normal attachay
*/

void	check_shell_variable(char **entry, char *tmp, char **env)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\\')
			++i;
		else if (tmp[i] == '\'')
		{
			tmp2 = goto_next_quote(tmp + i);
			i += tmp2 - tmp;
		}
		else if (tmp[i] == '$' && tmp[i + 1] != '\0' && tmp[i + 1] != ' ' &&
															tmp[i + 1] != '$')
			i = convert_shell_var(tmp, i, entry, env);
		if (tmp[i] != '\0')
			++i;
	}
}
