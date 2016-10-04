/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_others.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 10:39:20 by tbreart           #+#    #+#             */
/*   Updated: 2016/03/25 13:29:38 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_ope_and(char *s)
{
	if (s[0] == '&' && s[1] == '&')
		return (2);
	return (0);
}

int		is_ope_or(char *s)
{
	if (s[0] == '|' && s[1] == '|')
		return (2);
	return (0);
}

int		is_ope_pipe(char *s)
{
	if (s[0] == '|')
		return (1);
	return (0);
}

int		is_ope_coma(char *s)
{
	if (s[0] == ';')
		return (1);
	return (0);
}
