/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 09:58:48 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/08 21:27:28 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	is_end_word(char *s)
{
	if (is_ope_coma(s) > 0)
		return (1);
	else if (is_ope_and(s) > 0)
		return (1);
	else if (is_ope_or(s) > 0)
		return (1);
	else if (is_ope_pipe(s) > 0)
		return (1);
	else if (is_ope_leftleft_redir(s) > 0)
		return (1);
	else if (is_ope_left_redir(s) > 0)
		return (1);
	else if (is_ope_rightright_redir(s) > 0)
		return (1);
	else if (is_ope_right_redir(s) > 0)
		return (1);
	return (0);
}

/*
**	penser a \
*/

int			is_a_word(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"')
				i++;
			if (s[i] == '\0' || s[++i] == '\0')
				return (i);
		}
		if (s[i] == ' ' && s[i + 1] != '\0' && is_end_word(s + i + 1))
			break ;
		else if (is_ope_and(s + i) > 0)
			break ;
		else if (s[i] == '<' || s[i] == ';' || s[i] == '|' || s[i] == '>')
			break ;
		else if (s[i] == '`')
			break ;
		i++;
	}
	return (i);
}
