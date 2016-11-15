/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 10:48:06 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/15 15:28:03 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEXER_H
# define FT_LEXER_H

/*
**	formatting_cmd_aggr_fd.c
*/
int		find_aggregator_fd(t_list *elem);

/*
**	formatting_cmd_general.c
*/
int		is_a_redir(int type);
int		formatting_cmd_general(t_list **first);

/*
**	formatting_cmd_swap_argv.c
*/
int		swap_argv_with_redir(t_list **first);

/*
**	lexical_analysis_general.c
*/
int		lexical_analysis(char *cmd, t_list **first);

/*
**	is_token.c
*/
int		is_token_llr(t_list *elem);

/*
**lexical_analysis_ope_others.c
*/
int		is_ope_subshell(char *s);
int		is_ope_and(char *s);
int		is_ope_or(char *s);
int		is_ope_pipe(char *s);
int		is_ope_coma(char *s);

/*
**lexical_analysis_ope_redirections.c
*/
int		is_ope_left_redir(char *s);
int		is_ope_leftleft_redir(char *s);
int		is_ope_right_redir(char *s);
int		is_ope_rightright_redir(char *s);

/*
**lexical_analysis_ope_word.c
*/
int		is_a_word(char *s);

/*
**lexical_analysis_ope_debug.c
*/
void	show_analyse_lex(t_list *first);

#endif
