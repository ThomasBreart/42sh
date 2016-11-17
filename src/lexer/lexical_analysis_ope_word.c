/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 09:58:48 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:37:46 by tbreart          ###   ########.fr       */
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
	else if (*s == '(')
		return (1);
	return (0);
}

/*
**	penser a \
*/

int			is_a_word(char *s)
{
	char	*start;

	start = s;
	while (*s != '\0' && is_end_word(s) == 0)
	{
		if (*s == '\\')
			++s;
		else if (*s == '"' || *s == '\'')
			s = goto_next_quote(s);
		else if (*s == '`')
			s = goto_next_backquote(s);
		if (*s != '\0')
			++s;
	}
	return (s - start);
}
