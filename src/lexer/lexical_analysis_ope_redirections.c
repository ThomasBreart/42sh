/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_ope_redirections.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 13:23:57 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 20:13:20 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_ope_left_redir(char *s)
{
	if (s[0] == '<')
		return (1);
	if (ft_isdigit(s[0]) && s[1] == '<')
		return (2);
	if (s[0] == '&' && s[1] == '<')
		return (2);
	return (0);
}

int		is_ope_leftleft_redir(char *s)
{
	if (s[0] == '<' && s[1] == '<')
		return (2);
	if (ft_isdigit(s[0]) && s[1] == '<' && s[2] == '<')
		return (3);
	if (s[0] == '&' && s[1] == '<' && s[2] == '<')
		return (3);
	return (0);
}

int		is_ope_right_redir(char *s)
{
	if (s[0] == '>')
		return (1);
	if (ft_isdigit(s[0]) && s[1] == '>')
		return (2);
	if (s[0] == '&' && s[1] == '>')
		return (2);
	return (0);
}

int		is_ope_rightright_redir(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (2);
	else if (ft_isdigit(s[0]) && s[1] == '>' && s[2] == '>')
		return (3);
	else if (s[0] == '&' && s[1] == '>' && s[2] == '>')
		return (3);
	return (0);
}
