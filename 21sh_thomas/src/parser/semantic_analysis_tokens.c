/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analysis_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 13:37:16 by tbreart           #+#    #+#             */
/*   Updated: 2016/05/19 07:22:09 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		lex_is_cmd(t_list *firstcpy)
{
	if (firstcpy->type == LEX_WORD)
		return (1);
	return (0);
}

int		lex_is_ope_pipe_or_redir(t_list *firstcpy)
{
	if (firstcpy != NULL && firstcpy->type >= 4 && firstcpy->type <= 8)
		return (1);
	return (0);
}

int		lex_is_ope_coma(t_list *firstcpy)
{
	if (firstcpy != NULL && firstcpy->type == LEX_COMA)
		return (1);
	return (0);
}

int		lex_is_ope_or_and(t_list *firstcpy)
{
	if (firstcpy != NULL && (firstcpy->type == LEX_OR ||
												firstcpy->type == LEX_AND))
		return (1);
	return (0);
}

void	eat_token(t_list **firstcpy)
{
	if (*firstcpy != NULL)
		*firstcpy = (*firstcpy)->next;
}
