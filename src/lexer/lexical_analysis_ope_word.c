/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 09:58:48 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 16:17:15 by tbreart          ###   ########.fr       */
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
//	int		i;
	char	*start;

//	i = 0;
	start = s;
	while (*s != '\0' && is_end_word(s) == 0)
	{
		if (*s == '\\')
			++s;
		else if (*s == '"' || *s == '\'')
			s = goto_next_quote(s);
		if (*s != '\0')
			++s;
	}

/*
		if (s[i] == '\"')// pas beau ca
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
		else if (s[i] == '(')
			break ;
		i++;
	}*/
	return (s - start);
}
