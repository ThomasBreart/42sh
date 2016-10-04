/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analysis.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 13:43:38 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 20:19:18 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

/*
**semantic_analysis.c
*/
t_list	*semantic_analysis(t_list *first);

/*
**semantic_analysis_tokens.c
*/
int		lex_is_cmd(t_list *firstcpy);
int		lex_is_ope_pipe_or_redir(t_list *firstcpy);
int		lex_is_ope_coma(t_list *firstcpy);
int		lex_is_ope_or_and(t_list *firstcpy);
void	eat_token(t_list **firstcpy);

#endif
